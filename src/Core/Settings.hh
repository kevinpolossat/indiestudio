//
// Created by kevin on 15/05/17.
//

#ifndef INDIESTUDIO_SETTINGS_HH
#define INDIESTUDIO_SETTINGS_HH

#include <cstdint>
#include <boost/serialization/serialization.hpp>
#include <irrlicht.h>
#include <array>
#include <Referee.hh>

class Settings {
public:
    ~Settings();

    static int                              &music_volume();
    static int                              &sound_volume();
    static std::array<irr::EKEY_CODE, 5>    &keyMapP1();
    static std::array<irr::EKEY_CODE, 5>    &keyMapP2();
    static std::string &                    refereePath();
    static bool &                           p2isAI();
    static std::array<int, 3>               &aisLevel();

    template <class Archive>
    void serialize(Archive &ar, unsigned int const) {
        ar & _music_volume;
        ar & _sound_volume;
        ar & _keyMapP1;
        ar & _keyMapP2;
    }

private:
    explicit Settings();
    Settings(Settings const &other)                 = delete;
    Settings(Settings &&other)                      = delete;

    Settings    &operator = (Settings const &other) = delete;
    static      Settings &instance();
    void        default_init();

    int                             _music_volume;
    int                             _sound_volume;
    std::array<irr::EKEY_CODE, 5>   _keyMapP1;
    std::array<irr::EKEY_CODE, 5>   _keyMapP2;
    std::string                     _refereePath;
    bool                            _p2isAI;
    std::array<int, 3>              _aisLevel;

    int                             &music_volume_impl();
    int                             &sound_volume_impl();
    std::array<irr::EKEY_CODE, 5>   &keyMapP1_impl();
    std::array<irr::EKEY_CODE, 5>   &keyMapP2_impl();
    std::string &                   refereePath_impl();
    bool &                          p2isAI_impl();
    std::array<int, 3>              &aisLevel_impl();
};


#endif //INDIESTUDIO_SETTINGS_HH
