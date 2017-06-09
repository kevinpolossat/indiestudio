//
// Created by kevin on 15/05/17.
//

#ifndef INDIESTUDIO_SETTINGS_HH
#define INDIESTUDIO_SETTINGS_HH

#include <cstdint>
#include <boost/serialization/serialization.hpp>
#include <irrlicht.h>
#include <array>

class Settings {
public:
    ~Settings();

    static int &music_volume();
    static int &sound_volume();

    template <class Archive>
    void serialize(Archive &ar, unsigned int const) {
        ar & _music_volume;
        ar & _sound_volume;
        ar & _keyMap;
    }

private:
    explicit Settings();
    Settings(Settings const &other)                 = delete;
    Settings(Settings &&other)                      = delete;

    Settings    &operator = (Settings const &other) = delete;
    static      Settings &instance();

    int                             _music_volume;
    int                             _sound_volume;
    std::array<irr::EKEY_CODE, 5>   _keyMap;

    int         &music_volume_impl();
    int         &sound_volume_impl();
};


#endif //INDIESTUDIO_SETTINGS_HH
