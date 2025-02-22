#ifndef AUDIO_HPP
#define AUDIO_HPP

#include <iostream>
#include "miniaudio.h"

struct Audio {
    ma_result result;
    ma_engine engine;

    std::string music_file_name;

    Audio(std::string music_file_name_) : music_file_name(music_file_name_) {
        result = ma_engine_init(NULL, &engine);
        if(result != MA_SUCCESS) {
            std::cout << "Error: Miniaudio failed to load" << std::endl;
        }
        ma_engine_set_volume(&engine, 0.15f);
    }

    void play_hitsound() {
        ma_engine_play_sound(&engine, "normal-hitclap.wav", NULL);
    }

    void play_music() {
        ma_engine_play_sound(&engine, music_file_name.c_str(), NULL);
    }

    ~Audio() {
        ma_engine_uninit(&engine);
    }

};

#endif
