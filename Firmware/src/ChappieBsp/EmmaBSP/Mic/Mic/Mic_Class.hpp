// Copyright (c) M5Stack. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef __M5_Mic_Class_H__
#define __M5_Mic_Class_H__

#include <freertos/FreeRTOS.h>
#include <freertos/semphr.h>
#include <freertos/task.h>
#include <soc/i2s_struct.h>

#if __has_include(<driver/i2s_std.h>)
 #include <driver/i2s_std.h>
#else
 #include <driver/i2s.h>
#endif

#ifndef I2S_PIN_NO_CHANGE
#define I2S_PIN_NO_CHANGE (-1)
#endif

namespace m5
{
  class M5Unified;

  struct mic_config_t
  {
    /// i2s_data_in (for mic)
    int pin_data_in = -1;

    /// i2s_bclk
    int pin_bck = I2S_PIN_NO_CHANGE;

    /// i2s_mclk
    int pin_mck = I2S_PIN_NO_CHANGE;

    /// i2s_ws (lrck)
    int pin_ws = I2S_PIN_NO_CHANGE;

    /// input sampling rate (Hz)
    uint32_t sample_rate = 16000;

    /// use stereo output
    bool stereo = false;

    /// offset correction value of ADC input value
    int input_offset = 0;

    /// Sampling times of obtain the average value
    uint8_t over_sampling = 2;

    /// multiplier for input value
    uint8_t magnification = 16;

    /// Coefficient of the previous value, used for noise filtering.
    uint8_t noise_filter_level = 0;

    /// use analog input mic ( need only pin_data_in )
    bool use_adc = false;

    /// for I2S dma_buf_len
    size_t dma_buf_len = 64;

    /// for I2S dma_buf_count
    size_t dma_buf_count = 4;

    /// background task priority
    UBaseType_t task_priority = 2;

    /// background task pinned core
    BaseType_t task_pinned_core = -1;

    /// I2S port
    i2s_port_t i2s_port = i2s_port_t::I2S_NUM_0;
  };

  class Mic_Class
  {
//   friend M5Unified;

  public:

    mic_config_t config(void) const { return _cfg; }
    void config(const mic_config_t& cfg) { _cfg = cfg; }

    bool begin(void);

    void end(void);

    bool isRunning(void) const { return _task_running; }

    bool isEnabled(void) const { return _cfg.pin_data_in >= 0; }

    /// now in recording or not.
    /// @return 0=not recording / 1=recording (There's room in the queue) / 2=recording (There's no room in the queue.)
    size_t isRecording(void) const { return _is_recording ? ((bool)_rec_info[0].length) + ((bool)_rec_info[1].length) : 0; }

    /// set recording sampling rate.
    /// @param sample_rate the sampling rate (Hz)
    void setSampleRate(uint32_t sample_rate) { _cfg.sample_rate = sample_rate; }

    /// record raw sound wave data.
    /// @param rec_data Recording destination array.
    /// @param array_len Number of data array elements.
    /// @param sample_rate the sampling rate (Hz)
    bool record(uint8_t* rec_data, size_t array_len, uint32_t sample_rate)
    {
      return _rec_raw(rec_data, array_len, false, sample_rate);
    }

    /// record raw sound wave data.
    /// @param rec_data Recording destination array.
    /// @param array_len Number of data array elements.
    /// @param sample_rate the sampling rate (Hz)
    bool record(int16_t* rec_data, size_t array_len, uint32_t sample_rate)
    {
      return _rec_raw(rec_data, array_len,  true, sample_rate);
    }

    /// record raw sound wave data.
    /// @param rec_data Recording destination array.
    /// @param array_len Number of data array elements.
    bool record(uint8_t* rec_data, size_t array_len)
    {
      return _rec_raw(rec_data, array_len, false, _cfg.sample_rate);
    }

    /// record raw sound wave data.
    /// @param rec_data Recording destination array.
    /// @param array_len Number of data array elements.
    bool record(int16_t* rec_data, size_t array_len)
    {
      return _rec_raw(rec_data, array_len,  true, _cfg.sample_rate);
    }

  protected:

    void setCallback(void* args, bool(*func)(void*, bool)) { _cb_set_enabled = func; _cb_set_enabled_args = args; }

    struct recording_info_t
    {
      void* data = nullptr;
      size_t length = 0;
      bool is_16bit = false;
    };

    recording_info_t _rec_info[2];
    volatile bool _rec_flip = false;

    static void mic_task(void* args);

    uint32_t _calc_rec_rate(void) const;
    esp_err_t _setup_i2s(void);
    bool _rec_raw(void* recdata, size_t array_len, bool flg_16bit, uint32_t sample_rate);

    mic_config_t _cfg;
    uint32_t _rec_sample_rate = 0;

    bool (*_cb_set_enabled)(void* args, bool enabled) = nullptr;
    void* _cb_set_enabled_args = nullptr;

    TaskHandle_t _task_handle = nullptr;
    volatile bool _task_running = false;
    volatile bool _is_recording = false;
    volatile SemaphoreHandle_t _task_semaphore = nullptr;
  };
}

#endif
