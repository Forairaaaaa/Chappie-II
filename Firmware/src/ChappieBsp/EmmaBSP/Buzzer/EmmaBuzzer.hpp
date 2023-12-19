/**
 * @file EmmaBuzzer.hpp
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-02-18
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once
#include "../../EmmaConfig.h"
#if EMMA_MODULE_BUZZER
#include <Arduino.h>
#include "Melody.h"


class EmmaBuzzer {
    private:
        uint8_t __buzzer_pin;

    public:
        EmmaBuzzer(): __buzzer_pin(EMMA_BUZZER_PIN) {}


        /* Wrap */
        inline void _setToneChannel(uint8_t channel = 0) { setToneChannel(channel); }
        inline void _tone(unsigned int frequency, unsigned long duration = 0) { tone(__buzzer_pin, frequency, duration); }
        inline void _noTone() { noTone(__buzzer_pin); }


        /**
         * @brief Play melody
         * 
         * @param melody Melody.h 
         */
        void play(Melody::Melody_t melody) { play(melody.melody, melody.size, melody.tempo); }
        void play(int* melody, size_t melodySize, int tempo = 100)
        {
            // notes of the moledy followed by the duration.
            // a 4 means a quarter note, 8 an eighteenth , 16 sixteenth, so on
            // !!negative numbers are used to represent dotted notes,
            // so -4 means a dotted quarter note, that is, a quarter plus an eighteenth!!

            // sizeof gives the number of bytes, each int value is composed of two bytes (16 bits)
            // there are two values per note (pitch and duration), so for each note there are four bytes
            int notes = melodySize / sizeof(melody[0]) / 2; 

            // this calculates the duration of a whole note in ms (60s/tempo)*4 beats
            int wholenote = (60000 * 4) / tempo;

            int divider = 0, noteDuration = 0;
            
            for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {

                // calculates the duration of each note
                divider = melody[thisNote + 1];
                if (divider > 0) {
                    // regular note, just proceed
                    noteDuration = (wholenote) / divider;
                } else if (divider < 0) {
                    // dotted notes are represented with negative durations!!
                    noteDuration = (wholenote) / abs(divider);
                    noteDuration *= 1.5; // increases the duration in half for dotted notes
                }

                // we only play the note for 90% of the duration, leaving 10% as a pause
                _tone(melody[thisNote], noteDuration * 0.9);

                // Wait for the specief duration before playing the next note.
                delay(noteDuration);

                // stop the waveform generation before the next note.
                _noTone();
            }
        }
};

#endif
