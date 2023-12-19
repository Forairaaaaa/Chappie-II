#if 1
#include "App_FFT.h"
#include "../../../ChappieBsp/Chappie.h"


static std::string app_name = "FFT";
static CHAPPIE* device;


LV_IMG_DECLARE(ui_img_icon_fft_png);


/* ----------------------------------------------------------------------------------------- */
#include "arduinoFFT.h"

static arduinoFFT _FFT;
static LGFX_Sprite* _screen;

/*
These values can be changed in order to evaluate the functions
*/
const uint16_t  _samples = 256; //This value MUST ALWAYS be a power of 2
const double    _samplingFrequency = 48000;
/*
These are the input and output vectors
Input vectors receive computed results from FFT
*/
// static double vReal[samples];
// static double vImag[samples];
static double* _vReal;
static double* _vReal_old;
static double* _vImag;
static int16_t* _rawData;

static void _fft_init()
{
    /* Init screen sprite */
    _screen = new LGFX_Sprite(&device->Lcd);
    _screen->setRotation(2);
    _screen->setPsram(true);
    _screen->createSprite(device->Lcd.width(), device->Lcd.height());
    
    /* Alloc buffer */
    _vReal      = new double[_samples];
    _vReal_old  = new double[_samples]();
    _vImag      = new double[_samples];
    _rawData    = new int16_t[_samples];
    
}


static void _fft_update_data()
{
    /* Read mic */
    device->Mic.record(_rawData, _samples);
    while (device->Mic.isRecording());

    /* Copy data */
    for (int i = 0; i < _samples; i++) {
        _vReal[i] = (double)_rawData[i];
        _vImag[i] = 0.0;
    }

    /* FFT */
    _FFT = arduinoFFT(_vReal, _vImag, _samples, _samplingFrequency);
    _FFT.Windowing(FFT_WIN_TYP_HAMMING, FFT_FORWARD);
    _FFT.Compute(FFT_FORWARD);
    _FFT.ComplexToMagnitude();
}


static int _color_list[] = {
    TFT_YELLOW,
    TFT_ORANGE,
    TFT_GREENYELLOW,
    TFT_PINK,
    TFT_BROWN,
    TFT_GOLD,
    TFT_SILVER,
};

static void _fft_update_display()
{
    _screen->fillScreen(TFT_BLACK);

    uint8_t color_num = 0;

    /* Draw raw wave */
    for (int i = 0; i < _samples; i++) {
        _screen->drawPixel(i + 10, (_rawData[i] / 10) + 100, _color_list[color_num]);
        color_num++;
        if (color_num >= 7)
            color_num = 0;
    }
    
    double value = 0.0;
    for (int i = 4; i < (_samples / 4); i += 2) {
        /* Draw falling bricks */
        value = (_vReal_old[i] + _vReal_old[i+1]) / 2;
        _screen->fillRoundRect(8 * i - 24, 10 + value - 8, 8, 8, 2, _color_list[color_num]);

        /* Draw FFT */
        value = (_vReal[i] + _vReal[i+1]) / 2;
        value = value / 10;
        if (value > 220)
            value = 220;
        _screen->fillRoundRect(8 * i - 24, 10, 8, value, 2, _color_list[color_num]);

        color_num++;
        if (color_num >= 7)
            color_num = 0;
    }

    /* Update old buffer (falling bricks) */
    for (int i = 0; i < _samples; i++) {
        /* Fall */
        _vReal_old[i] -= 4;
        
        /* If higher hit */
        value = _vReal[i] / 10;
        if (value > 220)
            value = 220;
        if (value > _vReal_old[i])
            _vReal_old[i] = value;

    }

    

    _screen->pushSprite(0, 0);
}


static void _fft_deinit()
{
    _screen->deleteSprite();
    delete _screen;
    delete [] _vReal;
    delete [] _vImag;
    delete [] _rawData;
    delete [] _vReal_old;
}


/* ----------------------------------------------------------------------------------------- */



namespace App {

    /**
     * @brief Return the App name laucnher, which will be show on launcher App list
     * 
     * @return std::string 
     */
    std::string App_FFT_appName()
    {
        return app_name;
    }


    /**
     * @brief Return the App Icon laucnher, NULL for default
     * 
     * @return void* 
     */
    void* App_FFT_appIcon()
    {
        // return NULL;
        return (void*)&ui_img_icon_fft_png;
    }


    /**
     * @brief Called when App is on create
     * 
     */
    void App_FFT_onCreate()
    {
        UI_LOG("[%s] onCreate\n", App_FFT_appName().c_str());

        _fft_init();
        while (1) {
            _fft_update_data();
            _fft_update_display();
            if (device->Button.B.pressed()) 
                break;
        }
        lv_obj_t * label = lv_label_create(lv_scr_act());
        lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);
        lv_label_set_text(label, "Press B again to quit");
    }


    /**
     * @brief Called repeatedly, end this function ASAP! or the App management will be affected
     * If the thing you want to do takes time, try create a taak or lvgl timer to handle them.
     * Try use millis() instead of delay() here
     * 
     */
    void App_FFT_onLoop()
    {
    }


    /**
     * @brief Called when App is about to be destroy
     * Please remember to release the resourse like lvgl timers in this function
     * 
     */
    void App_FFT_onDestroy()
    {
        UI_LOG("[%s] onDestroy\n", App_FFT_appName().c_str());
        _fft_deinit();
    }


    /**
     * @brief Launcher will pass the BSP pointer through this function before onCreate
     * 
     */
    void App_FFT_getBsp(void* bsp)
    {
        device = (CHAPPIE*)bsp;
    }
    
}

#endif
