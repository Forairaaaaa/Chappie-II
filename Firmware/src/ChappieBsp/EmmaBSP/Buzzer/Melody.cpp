/**
 * @file Melody.cpp
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-02-19
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "Melody.h"
#if EMMA_BUZZER_MELODY

/**
 * @brief Tool: https://musiclab.chromeexperiments.com/Song-Maker
 * 
 */
namespace Melody
{
    #if EMMA_BUZZER_MELODY_MSG
    

    int melody_StartUp[] = {
        NOTE_C7, 8, 
        NOTE_GS6, 12, NOTE_C7,12, NOTE_D7,12
    };
    Melody_Def(StartUp, 240);


    int melody_Message[] = {
        NOTE_GS6, 12, NOTE_C7, 12, NOTE_D7, 12,
        REST, 4,
        NOTE_GS7, 12
    };
    Melody_Def(Message, 240);


    int melody_Warring[]
    {
        NOTE_GS7, 12, NOTE_GS7, 12, NOTE_GS7, 12, NOTE_GS7, 12, NOTE_GS7, 12
    };
    Melody_Def(Warring, 240);


    #endif
    #if EMMA_BUZZER_MELODY_MUSIC


    int melody_ZeldaTheme[] = {
        //Based on the arrangement at https://www.flutetunes.com/tunes.php?id=169
        NOTE_AS4,-2,  NOTE_F4,8,  NOTE_F4,8,  NOTE_AS4,8,//1
        NOTE_GS4,16,  NOTE_FS4,16,  NOTE_GS4,-2,
        NOTE_AS4,-2,  NOTE_FS4,8,  NOTE_FS4,8,  NOTE_AS4,8,
        NOTE_A4,16,  NOTE_G4,16,  NOTE_A4,-2,
        REST,1, 

        NOTE_AS4,4,  NOTE_F4,-4,  NOTE_AS4,8,  NOTE_AS4,16,  NOTE_C5,16, NOTE_D5,16, NOTE_DS5,16,//7
        NOTE_F5,2,  NOTE_F5,8,  NOTE_F5,8,  NOTE_F5,8,  NOTE_FS5,16, NOTE_GS5,16,
        NOTE_AS5,-2,  NOTE_AS5,8,  NOTE_AS5,8,  NOTE_GS5,8,  NOTE_FS5,16,
        NOTE_GS5,-8,  NOTE_FS5,16,  NOTE_F5,2,  NOTE_F5,4, 

        NOTE_DS5,-8, NOTE_F5,16, NOTE_FS5,2, NOTE_F5,8, NOTE_DS5,8, //11
        NOTE_CS5,-8, NOTE_DS5,16, NOTE_F5,2, NOTE_DS5,8, NOTE_CS5,8,
        NOTE_C5,-8, NOTE_D5,16, NOTE_E5,2, NOTE_G5,8, 
        NOTE_F5,16, NOTE_F4,16, NOTE_F4,16, NOTE_F4,16,NOTE_F4,16,NOTE_F4,16,NOTE_F4,16,NOTE_F4,16,NOTE_F4,8, NOTE_F4,16,NOTE_F4,8,

        NOTE_AS4,4,  NOTE_F4,-4,  NOTE_AS4,8,  NOTE_AS4,16,  NOTE_C5,16, NOTE_D5,16, NOTE_DS5,16,//15
        NOTE_F5,2,  NOTE_F5,8,  NOTE_F5,8,  NOTE_F5,8,  NOTE_FS5,16, NOTE_GS5,16,
        NOTE_AS5,-2, NOTE_CS6,4,
        NOTE_C6,4, NOTE_A5,2, NOTE_F5,4,
        NOTE_FS5,-2, NOTE_AS5,4,
        NOTE_A5,4, NOTE_F5,2, NOTE_F5,4,

        NOTE_FS5,-2, NOTE_AS5,4,
        NOTE_A5,4, NOTE_F5,2, NOTE_D5,4,
        NOTE_DS5,-2, NOTE_FS5,4,
        NOTE_F5,4, NOTE_CS5,2, NOTE_AS4,4,
        NOTE_C5,-8, NOTE_D5,16, NOTE_E5,2, NOTE_G5,8, 
        NOTE_F5,16, NOTE_F4,16, NOTE_F4,16, NOTE_F4,16,NOTE_F4,16,NOTE_F4,16,NOTE_F4,16,NOTE_F4,16,NOTE_F4,8, NOTE_F4,16,NOTE_F4,8
    };
    Melody_Def(ZeldaTheme, 88);


    int melody_StarWarsTheme[] = {
        // Dart Vader theme (Imperial March) - Star wars 
        // Score available at https://musescore.com/user/202909/scores/1141521
        // The tenor saxophone part was used
        NOTE_AS4,8, NOTE_AS4,8, NOTE_AS4,8,//1
        NOTE_F5,2, NOTE_C6,2,
        NOTE_AS5,8, NOTE_A5,8, NOTE_G5,8, NOTE_F6,2, NOTE_C6,4,  
        NOTE_AS5,8, NOTE_A5,8, NOTE_G5,8, NOTE_F6,2, NOTE_C6,4,  
        NOTE_AS5,8, NOTE_A5,8, NOTE_AS5,8, NOTE_G5,2, NOTE_C5,8, NOTE_C5,8, NOTE_C5,8,
        NOTE_F5,2, NOTE_C6,2,
        NOTE_AS5,8, NOTE_A5,8, NOTE_G5,8, NOTE_F6,2, NOTE_C6,4,  
        
        NOTE_AS5,8, NOTE_A5,8, NOTE_G5,8, NOTE_F6,2, NOTE_C6,4, //8  
        NOTE_AS5,8, NOTE_A5,8, NOTE_AS5,8, NOTE_G5,2, NOTE_C5,-8, NOTE_C5,16, 
        NOTE_D5,-4, NOTE_D5,8, NOTE_AS5,8, NOTE_A5,8, NOTE_G5,8, NOTE_F5,8,
        NOTE_F5,8, NOTE_G5,8, NOTE_A5,8, NOTE_G5,4, NOTE_D5,8, NOTE_E5,4,NOTE_C5,-8, NOTE_C5,16,
        NOTE_D5,-4, NOTE_D5,8, NOTE_AS5,8, NOTE_A5,8, NOTE_G5,8, NOTE_F5,8,
        
        NOTE_C6,-8, NOTE_G5,16, NOTE_G5,2, REST,8, NOTE_C5,8,//13
        NOTE_D5,-4, NOTE_D5,8, NOTE_AS5,8, NOTE_A5,8, NOTE_G5,8, NOTE_F5,8,
        NOTE_F5,8, NOTE_G5,8, NOTE_A5,8, NOTE_G5,4, NOTE_D5,8, NOTE_E5,4,NOTE_C6,-8, NOTE_C6,16,
        NOTE_F6,4, NOTE_DS6,8, NOTE_CS6,4, NOTE_C6,8, NOTE_AS5,4, NOTE_GS5,8, NOTE_G5,4, NOTE_F5,8,
        NOTE_C6,1
    };
    Melody_Def(StarWarsTheme, 108);
    

    int melody_SuperMarioBros[] = {
        // Super Mario Bros theme
        // Score available at https://musescore.com/user/2123/scores/2145
        // Theme by Koji Kondo
        NOTE_E5,8, NOTE_E5,8, REST,8, NOTE_E5,8, REST,8, NOTE_C5,8, NOTE_E5,8, //1
        NOTE_G5,4, REST,4, NOTE_G4,8, REST,4, 
        NOTE_C5,-4, NOTE_G4,8, REST,4, NOTE_E4,-4, // 3
        NOTE_A4,4, NOTE_B4,4, NOTE_AS4,8, NOTE_A4,4,
        NOTE_G4,-8, NOTE_E5,-8, NOTE_G5,-8, NOTE_A5,4, NOTE_F5,8, NOTE_G5,8,
        REST,8, NOTE_E5,4,NOTE_C5,8, NOTE_D5,8, NOTE_B4,-4,
        NOTE_C5,-4, NOTE_G4,8, REST,4, NOTE_E4,-4, // repeats from 3
        NOTE_A4,4, NOTE_B4,4, NOTE_AS4,8, NOTE_A4,4,
        NOTE_G4,-8, NOTE_E5,-8, NOTE_G5,-8, NOTE_A5,4, NOTE_F5,8, NOTE_G5,8,
        REST,8, NOTE_E5,4,NOTE_C5,8, NOTE_D5,8, NOTE_B4,-4,

        REST,4, NOTE_G5,8, NOTE_FS5,8, NOTE_F5,8, NOTE_DS5,4, NOTE_E5,8,//7
        REST,8, NOTE_GS4,8, NOTE_A4,8, NOTE_C4,8, REST,8, NOTE_A4,8, NOTE_C5,8, NOTE_D5,8,
        REST,4, NOTE_DS5,4, REST,8, NOTE_D5,-4,
        NOTE_C5,2, REST,2,

        REST,4, NOTE_G5,8, NOTE_FS5,8, NOTE_F5,8, NOTE_DS5,4, NOTE_E5,8,//repeats from 7
        REST,8, NOTE_GS4,8, NOTE_A4,8, NOTE_C4,8, REST,8, NOTE_A4,8, NOTE_C5,8, NOTE_D5,8,
        REST,4, NOTE_DS5,4, REST,8, NOTE_D5,-4,
        NOTE_C5,2, REST,2,

        NOTE_C5,8, NOTE_C5,4, NOTE_C5,8, REST,8, NOTE_C5,8, NOTE_D5,4,//11
        NOTE_E5,8, NOTE_C5,4, NOTE_A4,8, NOTE_G4,2,

        NOTE_C5,8, NOTE_C5,4, NOTE_C5,8, REST,8, NOTE_C5,8, NOTE_D5,8, NOTE_E5,8,//13
        REST,1, 
        NOTE_C5,8, NOTE_C5,4, NOTE_C5,8, REST,8, NOTE_C5,8, NOTE_D5,4,
        NOTE_E5,8, NOTE_C5,4, NOTE_A4,8, NOTE_G4,2,
        NOTE_E5,8, NOTE_E5,8, REST,8, NOTE_E5,8, REST,8, NOTE_C5,8, NOTE_E5,4,
        NOTE_G5,4, REST,4, NOTE_G4,4, REST,4, 
        NOTE_C5,-4, NOTE_G4,8, REST,4, NOTE_E4,-4, // 19
        
        NOTE_A4,4, NOTE_B4,4, NOTE_AS4,8, NOTE_A4,4,
        NOTE_G4,-8, NOTE_E5,-8, NOTE_G5,-8, NOTE_A5,4, NOTE_F5,8, NOTE_G5,8,
        REST,8, NOTE_E5,4, NOTE_C5,8, NOTE_D5,8, NOTE_B4,-4,

        NOTE_C5,-4, NOTE_G4,8, REST,4, NOTE_E4,-4, // repeats from 19
        NOTE_A4,4, NOTE_B4,4, NOTE_AS4,8, NOTE_A4,4,
        NOTE_G4,-8, NOTE_E5,-8, NOTE_G5,-8, NOTE_A5,4, NOTE_F5,8, NOTE_G5,8,
        REST,8, NOTE_E5,4, NOTE_C5,8, NOTE_D5,8, NOTE_B4,-4,

        NOTE_E5,8, NOTE_C5,4, NOTE_G4,8, REST,4, NOTE_GS4,4,//23
        NOTE_A4,8, NOTE_F5,4, NOTE_F5,8, NOTE_A4,2,
        NOTE_D5,-8, NOTE_A5,-8, NOTE_A5,-8, NOTE_A5,-8, NOTE_G5,-8, NOTE_F5,-8,
        
        NOTE_E5,8, NOTE_C5,4, NOTE_A4,8, NOTE_G4,2, //26
        NOTE_E5,8, NOTE_C5,4, NOTE_G4,8, REST,4, NOTE_GS4,4,
        NOTE_A4,8, NOTE_F5,4, NOTE_F5,8, NOTE_A4,2,
        NOTE_B4,8, NOTE_F5,4, NOTE_F5,8, NOTE_F5,-8, NOTE_E5,-8, NOTE_D5,-8,
        NOTE_C5,8, NOTE_E4,4, NOTE_E4,8, NOTE_C4,2,

        NOTE_E5,8, NOTE_C5,4, NOTE_G4,8, REST,4, NOTE_GS4,4,//repeats from 23
        NOTE_A4,8, NOTE_F5,4, NOTE_F5,8, NOTE_A4,2,
        NOTE_D5,-8, NOTE_A5,-8, NOTE_A5,-8, NOTE_A5,-8, NOTE_G5,-8, NOTE_F5,-8,
        
        NOTE_E5,8, NOTE_C5,4, NOTE_A4,8, NOTE_G4,2, //26
        NOTE_E5,8, NOTE_C5,4, NOTE_G4,8, REST,4, NOTE_GS4,4,
        NOTE_A4,8, NOTE_F5,4, NOTE_F5,8, NOTE_A4,2,
        NOTE_B4,8, NOTE_F5,4, NOTE_F5,8, NOTE_F5,-8, NOTE_E5,-8, NOTE_D5,-8,
        NOTE_C5,8, NOTE_E4,4, NOTE_E4,8, NOTE_C4,2,
        NOTE_C5,8, NOTE_C5,4, NOTE_C5,8, REST,8, NOTE_C5,8, NOTE_D5,8, NOTE_E5,8,
        REST,1,

        NOTE_C5,8, NOTE_C5,4, NOTE_C5,8, REST,8, NOTE_C5,8, NOTE_D5,4, //33
        NOTE_E5,8, NOTE_C5,4, NOTE_A4,8, NOTE_G4,2,
        NOTE_E5,8, NOTE_E5,8, REST,8, NOTE_E5,8, REST,8, NOTE_C5,8, NOTE_E5,4,
        NOTE_G5,4, REST,4, NOTE_G4,4, REST,4, 
        NOTE_E5,8, NOTE_C5,4, NOTE_G4,8, REST,4, NOTE_GS4,4,
        NOTE_A4,8, NOTE_F5,4, NOTE_F5,8, NOTE_A4,2,
        NOTE_D5,-8, NOTE_A5,-8, NOTE_A5,-8, NOTE_A5,-8, NOTE_G5,-8, NOTE_F5,-8,
        
        NOTE_E5,8, NOTE_C5,4, NOTE_A4,8, NOTE_G4,2, //40
        NOTE_E5,8, NOTE_C5,4, NOTE_G4,8, REST,4, NOTE_GS4,4,
        NOTE_A4,8, NOTE_F5,4, NOTE_F5,8, NOTE_A4,2,
        NOTE_B4,8, NOTE_F5,4, NOTE_F5,8, NOTE_F5,-8, NOTE_E5,-8, NOTE_D5,-8,
        NOTE_C5,8, NOTE_E4,4, NOTE_E4,8, NOTE_C4,2,
        
        //game over sound
        NOTE_C5,-4, NOTE_G4,-4, NOTE_E4,4, //45
        NOTE_A4,-8, NOTE_B4,-8, NOTE_A4,-8, NOTE_GS4,-8, NOTE_AS4,-8, NOTE_GS4,-8,
        NOTE_G4,8, NOTE_D4,8, NOTE_E4,-2,  
    };
    Melody_Def(SuperMarioBros, 200);


    int melody_HedwigsTheme[] = {
        // Hedwig's theme fromn the Harry Potter Movies
        // Socre from https://musescore.com/user/3811306/scores/4906610
        REST, 2, NOTE_D4, 4,
        NOTE_G4, -4, NOTE_AS4, 8, NOTE_A4, 4,
        NOTE_G4, 2, NOTE_D5, 4,
        NOTE_C5, -2, 
        NOTE_A4, -2,
        NOTE_G4, -4, NOTE_AS4, 8, NOTE_A4, 4,
        NOTE_F4, 2, NOTE_GS4, 4,
        NOTE_D4, -1, 
        NOTE_D4, 4,

        NOTE_G4, -4, NOTE_AS4, 8, NOTE_A4, 4, //10
        NOTE_G4, 2, NOTE_D5, 4,
        NOTE_F5, 2, NOTE_E5, 4,
        NOTE_DS5, 2, NOTE_B4, 4,
        NOTE_DS5, -4, NOTE_D5, 8, NOTE_CS5, 4,
        NOTE_CS4, 2, NOTE_B4, 4,
        NOTE_G4, -1,
        NOTE_AS4, 4,
            
        NOTE_D5, 2, NOTE_AS4, 4,//18
        NOTE_D5, 2, NOTE_AS4, 4,
        NOTE_DS5, 2, NOTE_D5, 4,
        NOTE_CS5, 2, NOTE_A4, 4,
        NOTE_AS4, -4, NOTE_D5, 8, NOTE_CS5, 4,
        NOTE_CS4, 2, NOTE_D4, 4,
        NOTE_D5, -1, 
        REST,4, NOTE_AS4,4,  

        NOTE_D5, 2, NOTE_AS4, 4,//26
        NOTE_D5, 2, NOTE_AS4, 4,
        NOTE_F5, 2, NOTE_E5, 4,
        NOTE_DS5, 2, NOTE_B4, 4,
        NOTE_DS5, -4, NOTE_D5, 8, NOTE_CS5, 4,
        NOTE_CS4, 2, NOTE_AS4, 4,
        NOTE_G4, -1, 
    };
    Melody_Def(HedwigsTheme, 144);


    int melody_NokiaTune[] = {
        // Nokia Ringtone 
        // Score available at https://musescore.com/user/29944637/scores/5266155  
        NOTE_E5, 8, NOTE_D5, 8, NOTE_FS4, 4, NOTE_GS4, 4, 
        NOTE_CS5, 8, NOTE_B4, 8, NOTE_D4, 4, NOTE_E4, 4, 
        NOTE_B4, 8, NOTE_A4, 8, NOTE_CS4, 4, NOTE_E4, 4,
        NOTE_A4, 2, 
    };
    Melody_Def(NokiaTune, 180);


    int melody_CannonInD[] = {
        // Cannon in D - Pachelbel
        // Score available at https://musescore.com/user/4710311/scores/1975521
        // C F
        NOTE_FS4,2, NOTE_E4,2,
        NOTE_D4,2, NOTE_CS4,2,
        NOTE_B3,2, NOTE_A3,2,
        NOTE_B3,2, NOTE_CS4,2,
        NOTE_FS4,2, NOTE_E4,2,
        NOTE_D4,2, NOTE_CS4,2,
        NOTE_B3,2, NOTE_A3,2,
        NOTE_B3,2, NOTE_CS4,2,
        NOTE_D4,2, NOTE_CS4,2,
        NOTE_B3,2, NOTE_A3,2,
        NOTE_G3,2, NOTE_FS3,2,
        NOTE_G3,2, NOTE_A3,2,

        NOTE_D4,4, NOTE_FS4,8, NOTE_G4,8, NOTE_A4,4, NOTE_FS4,8, NOTE_G4,8, 
        NOTE_A4,4, NOTE_B3,8, NOTE_CS4,8, NOTE_D4,8, NOTE_E4,8, NOTE_FS4,8, NOTE_G4,8, 
        NOTE_FS4,4, NOTE_D4,8, NOTE_E4,8, NOTE_FS4,4, NOTE_FS3,8, NOTE_G3,8,
        NOTE_A3,8, NOTE_G3,8, NOTE_FS3,8, NOTE_G3,8, NOTE_A3,2,
        NOTE_G3,4, NOTE_B3,8, NOTE_A3,8, NOTE_G3,4, NOTE_FS3,8, NOTE_E3,8, 
        NOTE_FS3,4, NOTE_D3,8, NOTE_E3,8, NOTE_FS3,8, NOTE_G3,8, NOTE_A3,8, NOTE_B3,8,

        NOTE_G3,4, NOTE_B3,8, NOTE_A3,8, NOTE_B3,4, NOTE_CS4,8, NOTE_D4,8,
        NOTE_A3,8, NOTE_B3,8, NOTE_CS4,8, NOTE_D4,8, NOTE_E4,8, NOTE_FS4,8, NOTE_G4,8, NOTE_A4,2,
        NOTE_A4,4, NOTE_FS4,8, NOTE_G4,8, NOTE_A4,4,
        NOTE_FS4,8, NOTE_G4,8, NOTE_A4,8, NOTE_A3,8, NOTE_B3,8, NOTE_CS4,8,
        NOTE_D4,8, NOTE_E4,8, NOTE_FS4,8, NOTE_G4,8, NOTE_FS4,4, NOTE_D4,8, NOTE_E4,8,
        NOTE_FS4,8, NOTE_CS4,8, NOTE_A3,8, NOTE_A3,8,

        NOTE_CS4,4, NOTE_B3,4, NOTE_D4,8, NOTE_CS4,8, NOTE_B3,4,
        NOTE_A3,8, NOTE_G3,8, NOTE_A3,4, NOTE_D3,8, NOTE_E3,8, NOTE_FS3,8, NOTE_G3,8,
        NOTE_A3,8, NOTE_B3,4, NOTE_G3,4, NOTE_B3,8, NOTE_A3,8, NOTE_B3,4,
        NOTE_CS4,8, NOTE_D4,8, NOTE_A3,8, NOTE_B3,8, NOTE_CS4,8, NOTE_D4,8, NOTE_E4,8,
        NOTE_FS4,8, NOTE_G4,8, NOTE_A4,2,  
    };
    Melody_Def(CannonInD, 100);


    #endif
}

#endif

