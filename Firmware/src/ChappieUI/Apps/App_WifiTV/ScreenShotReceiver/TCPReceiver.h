#ifndef _TCPRECEIVER_H_
#define _TCPRECEIVER_H_

#pragma GCC optimize ("O3")

#ifndef LOVYANGFX_HPP_
#define LGFX_USE_V1
#define LGFX_AUTODETECT
#include <LovyanGFX.hpp>  // https://github.com/lovyan03/LovyanGFX/
#endif

#include <WiFi.h>
#include <WiFiServer.h>
#include <esp_heap_caps.h>
#include "tjpgdClass.h"

class TCPReceiver
{
public:
  bool setup(LovyanGFX* lcd)
  {
    _lcd = lcd;
    _lcd->startWrite();
    Serial.println("TCPReceiver setup.");

    _lcd_width = lcd->width();
    _lcd_height = lcd->height();
    _bytesize = lcd->getColorConverter()->bytes;
    Serial.printf("display byte per pixel:%d\n", _bytesize);

    Serial.printf("color depth: %02x \n", lcd->getColorDepth());

    switch (lcd->getColorDepth())
    {
    default:
    case lgfx::color_depth_t::rgb565_2Byte:
      _fp_write = write565;
      break;
    case lgfx::color_depth_t::rgb888_3Byte:
      _fp_write = write888;
      break;
    case lgfx::color_depth_t::rgb332_1Byte:
      _fp_write = write332;
      break;
    case lgfx::color_depth_t::grayscale_8bit:
      _fp_write = writeGray;
      break;
    }
    for (int i = 0; i < 2; ++i) { _dmabufs[i] = (uint8_t*)heap_caps_malloc(_lcd_width * (_rowskip + 1) * 16 * _bytesize, MALLOC_CAP_DMA); }

    _dmabuf = _dmabufs[0];

    _tcp.setNoDelay(true);
    _tcp.begin(63333);

    _jdec.multitask_begin();

    Serial.println("TCPReceiver setup done.");
    return true;
  }

  bool loop()
  {
    static uint32_t waitCount = 0;

    if (SENDER_PREFIX_SIZE <= _client.available()
     && SENDER_PREFIX_SIZE == _client.read(_tcpBuf, SENDER_PREFIX_SIZE)) {
      waitCount = 0;
      _recv_requested = false;
      if (_tcpBuf[0] == 'J'
       && _tcpBuf[1] == 'P'
       && _tcpBuf[2] == 'G') {
        _recv_remain = _tcpBuf[3] | _tcpBuf[4] << 8 | _tcpBuf[5] << 16 | _tcpBuf[6] << 24;
        if (_recv_remain > 600) {
          if (drawJpg()) {
            ++_drawCount;
          }
        } else {
          Serial.println("jpg too short");
        }
        if (0 < _recv_remain) {
          Serial.printf("clear remain data:%d\r\n", _recv_remain);
          int r;
          for (uint32_t retry = 1000; retry; --retry) {
            r = _client.read(_tcpBuf, _recv_remain < TCP_BUF_LEN ? _recv_remain : TCP_BUF_LEN);
            if (r > 0) {
              _recv_remain -= r;
              if (!_recv_remain) break;
            } else {
              delay(1);
              ++_delayCount;
            }
          }
        }
      } else {
        Serial.printf("broken data: %02x %02x %02x %02x %02x %02x %02x %02x \n", _tcpBuf[0], _tcpBuf[1], _tcpBuf[2], _tcpBuf[3], _tcpBuf[4], _tcpBuf[5], _tcpBuf[6], _tcpBuf[7]);
        do { delay(8); } while (0 < _client.read(_tcpBuf, TCP_BUF_LEN));
      }
    } else
    if (!_client.connected()) {
      _client = _tcp.available();
      _recv_requested = false;
      waitCount = 0;
    } else {
      if (++waitCount > 1000) {
        _recv_requested = false;
      } else {
        delay(1);
        ++_delayCount;
      }
      if (!_recv_requested)   {
        while (0 < _client.read(_tcpBuf, TCP_BUF_LEN));
        _recv_requested = true;
        waitCount = 0;
        Serial.println("data request");
        _client.print("JPG\n");
      }
    }

    if (_sec != millis() / 1000) {
      _sec = millis() / 1000;
      Serial.printf("%2d fps", _drawCount);
      if (_delayCount) Serial.printf(" / delay%3d", _delayCount);
      Serial.print("\r\n");
      _drawCount = 0;
      _delayCount = 0;
    }

    return true;
  }
private:
  static constexpr int TCP_BUF_LEN = 512;
  static constexpr int SENDER_PREFIX_SIZE = 7;
  static constexpr uint32_t _rowskip = 2;

  LovyanGFX* _lcd;
  uint_fast8_t _bytesize;
  uint8_t* _dmabufs[2];
  uint8_t* _dmabuf;

  WiFiServer _tcp;
  WiFiClient _client;
  TJpgD _jdec;
  int32_t _recv_remain = 0;
  uint32_t _sec = 0;
  int32_t _lcd_width;
  int32_t _lcd_height;
  int32_t _out_width;
  int32_t _out_height;
  int32_t _off_x;
  int32_t _off_y;
  int32_t _jpg_x;
  int32_t _jpg_y;
  uint32_t _drawCount = 0;
  uint32_t _delayCount = 0;
  uint8_t _tcpBuf[TCP_BUF_LEN];
  bool _recv_requested = false;

  static uint32_t jpgRead(TJpgD *jdec, uint8_t *buf, uint32_t len) {
    TCPReceiver* me = (TCPReceiver*)jdec->device;
    WiFiClient* client = &me->_client;
    uint32_t retry;

    if (len > me->_recv_remain) {
      len = me->_recv_remain;
    } else if (len == TJPGD_SZBUF) {
      if (me->_recv_remain < TJPGD_SZBUF * 2 && TJPGD_SZBUF < me->_recv_remain) { // dataend read tweak
        len = me->_recv_remain - len;
      }
    } else if (client->available() < len) {
      for (retry = 1000; client->available() < len && retry; --retry) {
        delay(1);
        ++me->_delayCount;
      }
    }

    int l = client->read(buf ? buf : me->_tcpBuf, len);
    if (l <= 0) {
      for (retry = 1000; retry; --retry) {
        delay(1);
        ++me->_delayCount;
        l = client->read(buf ? buf : me->_tcpBuf, len);
        if (l > 0) break;
      }
    }
    if (l <= 0) {
      Serial.printf("jpgRead error:%d:%d:%d\r\n", l, len, client->available());
      return 0;
    }
    me->_recv_remain -= l;
    if (!me->_recv_requested && me->_recv_remain <= client->available()) {
      me->_recv_requested = true;
      client->print("JPG\n"); // request the next image from the client
    }
    return l;
  }

  static uint32_t jpgWrite(TJpgD *jdec, void *bitmap, TJpgD::JRECT *rect) {
    TCPReceiver* me = (TCPReceiver*)jdec->device;

    auto dst = me->_dmabuf;

    uint_fast16_t x = rect->left;
    uint_fast16_t y = rect->top;
    uint_fast16_t w = rect->right + 1 - x;
    uint_fast16_t h = rect->bottom + 1 - y;
    uint_fast16_t outWidth = me->_out_width;
    uint_fast16_t outHeight = me->_out_height;
    uint8_t *src = (uint8_t*)bitmap;
    uint_fast16_t oL = 0, oR = 0;

    if (rect->right < me->_off_x)      return 1;
    if (x >= (me->_off_x + outWidth))  return 1;
    if (rect->bottom < me->_off_y)     return 1;
    if (y >= (me->_off_y + outHeight)) return 1;

    int32_t src_idx = 0;
    int32_t dst_idx = 0;

    uint_fast16_t tmpy = y % ((1 + _rowskip) * jdec->msy << 3);
    if (me->_off_y > y) {
      uint_fast16_t linesToSkip = me->_off_y - y;
      src_idx += linesToSkip * w;
      h -= linesToSkip;
      dst_idx -= tmpy * outWidth;
    } else 
    if (me->_off_y > (y - tmpy)) {
      uint_fast16_t linesToSkip = me->_off_y - (y - tmpy);
      dst_idx -= linesToSkip * outWidth;
    }

    if (me->_off_x > x) {
      oL = me->_off_x - x;
    }
    if (rect->right >= (me->_off_x + outWidth)) {
      oR = (rect->right + 1) - (me->_off_x + outWidth);
    }

    int_fast16_t line = (w - ( oL + oR ));
    dst_idx += oL + x - me->_off_x + outWidth * tmpy;
    src_idx += oL;

    me->_fp_write(&dst[dst_idx * me->_bytesize], &src[src_idx * 3], line, outWidth, w, h);

    return 1;
  }

  static void write888(uint8_t* dst, const uint8_t* src, uint32_t line, uint32_t outWidth, uint32_t w, uint32_t h)
  {
    line *= 3;
    outWidth *= 3;
    w *= 3;
    do {
      memcpy(dst, src, line);
      src += w;
      dst += outWidth;
    } while (--h);
  }

  static void write565(uint8_t* dst, const uint8_t* src, uint32_t line, uint32_t outWidth, uint32_t w, uint32_t h)
  {
    do {
      auto s = src;
      auto d = dst;
      uint32_t l = line;
      while (l--) {
        uint32_t r = s[0];
        uint32_t g = s[1];
        uint32_t b = s[2];
        s += 3;
        g = g >> 2;
        r = (r >> 3) & 0x1F;
        r = (r << 3) + (g >> 3);
        b = (b >> 3) + (g << 5);
        d[0] = r;
        d[1] = b;
        d += 2;
      }
      dst += outWidth * 2;
      src += w * 3;
    } while (--h);
  }

  static void write332(uint8_t* dst, const uint8_t* src, uint32_t line, uint32_t outWidth, uint32_t w, uint32_t h)
  {
    do {
      auto s = src;
      auto d = dst;
      uint32_t l = line;
      while (l--) {
        uint32_t r = s[0];
        uint32_t g = s[1];
        uint32_t b = s[2];
        s += 3;
        r >>= 5;
        g >>= 5;
        b >>= 6;
        g += r << 3;
        b += g << 2;
        d[0] = b;
        ++d;
      }
      dst += outWidth;
      src += w * 3;
    } while (--h);
  }

  static void writeGray(uint8_t* dst, const uint8_t* src, uint32_t line, uint32_t outWidth, uint32_t w, uint32_t h)
  {
    --dst;
    do {
      auto s = src;
      auto d = dst;
      uint32_t l = line;
      while (l--) {
        uint32_t r = s[0];
        uint32_t g = s[1];
        uint32_t b = s[2];
        s += 3;
        ++d;
        r += (g << 1);
        r += b;
        d[0] = r >> 2;
      }
      dst += outWidth;
      src += w * 3;
    } while (--h);
  }

  static uint32_t jpgWriteRow(TJpgD *jdec, uint32_t y, uint32_t h) {
    static int flip = 0;
    TCPReceiver* me = (TCPReceiver*)jdec->device;

    if (y == 0) {
      me->_lcd->setAddrWindow(me->_jpg_x, me->_jpg_y, me->_out_width, me->_out_height);

      // while (me->_lcd->getScanLine() > 64) { taskYIELD(); }
    }

    int16_t outY = y - me->_off_y;
    if (outY < 0) {
      if (h <= - outY) return 1;
      h += outY;
      outY = 0;
    }
    if (me->_lcd_height <= me->_jpg_y + outY) return 1;
    if (me->_lcd_height < me->_jpg_y + outY + h) {
      h = me->_lcd_height - (me->_jpg_y + outY);
    }

    switch (me->_lcd->getColorDepth())
    {
    default:
    case lgfx::color_depth_t::rgb565_2Byte:   me->_lcd->pushPixelsDMA((lgfx::swap565_t*  )(me->_dmabuf), me->_out_width * h);  break;
    case lgfx::color_depth_t::rgb888_3Byte:   me->_lcd->pushPixelsDMA((lgfx::bgr888_t*   )(me->_dmabuf), me->_out_width * h);  break;
    case lgfx::color_depth_t::rgb332_1Byte:   me->_lcd->pushPixelsDMA((lgfx::rgb332_t*   )(me->_dmabuf), me->_out_width * h);  break;
    case lgfx::color_depth_t::grayscale_8bit: me->_lcd->pushPixelsDMA((lgfx::grayscale_t*)(me->_dmabuf), me->_out_width * h);  break;
    }

    flip = !flip;
    me->_dmabuf = me->_dmabufs[flip];
    return 1;
  }

  bool drawJpg(void) {
    TJpgD::JRESULT jres = _jdec.prepare(jpgRead, this);
    if (jres != TJpgD::JDR_OK) {
      Serial.printf("prepare failed! %d\r\n", jres);
      return false;
    }
    _out_width = _jdec.width < _lcd_width ? _jdec.width : _lcd_width;
    _jpg_x = (_lcd_width - _jdec.width) >> 1;
    if (0 > _jpg_x) {
      _off_x = - _jpg_x;
      _jpg_x = 0;
    } else {
      _off_x = 0;
    }
    _out_height = _jdec.height < _lcd_height ? _jdec.height : _lcd_height;
    _jpg_y = (_lcd_height- _jdec.height) >> 1;
    if (0 > _jpg_y) {
      _off_y = - _jpg_y;
      _jpg_y = 0;
    } else {
      _off_y = 0;
    }

    jres = _jdec.decomp_multitask(jpgWrite, jpgWriteRow, _rowskip);
    if (jres != TJpgD::JDR_OK) {
      Serial.printf("decomp failed! %d\r\n", jres);
      return false;
    }

    return true;
  }

  void (*_fp_write)(uint8_t* dst, const uint8_t* src, uint32_t line, uint32_t outWidth, uint32_t w, uint32_t h);
};

#endif