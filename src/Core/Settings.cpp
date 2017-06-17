//
// Created by kevin on 15/05/17.
//

#include <fstream>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <irrlicht.h>
#include <iostream>
#include "Settings.hh"
#include "Save.hh"

Settings::Settings(): _refereePath(""), _p2isAI(false) {
    _aisLevel = {3, 3, 3};
    std::ifstream ifs(Save::getGameDirectory() + ".settings");
    if (ifs.good()) {
        boost::archive::text_iarchive ia(ifs);
        try {
            ia >> *this;
        }
        catch (boost::archive::archive_exception const & ae) {
            default_init();
        }
        std::min(std::max(0, _music_volume), 10);
        std::min(std::max(0, _sound_volume), 10);
    }
    else {
        default_init();
    }
}

Settings::~Settings() {
    std::ofstream ofs(Save::getGameDirectory() + ".settings");
    if (ofs.good()) {
        boost::archive::text_oarchive ia(ofs);
        ia << *this;
    }
}

Settings &Settings::instance() {
    static Settings settings;
    return settings;
}

void Settings::default_init() {
    _music_volume = 10;
    _sound_volume = 10;
    _keyMapP1 = { irr::EKEY_CODE::KEY_KEY_Z, irr::EKEY_CODE::KEY_KEY_D,
                        irr::EKEY_CODE::KEY_KEY_S, irr::EKEY_CODE::KEY_KEY_Q,
                        irr::EKEY_CODE::KEY_SPACE };
    _keyMapP2 = { irr::EKEY_CODE::KEY_UP, irr::EKEY_CODE::KEY_RIGHT,
                        irr::EKEY_CODE::KEY_DOWN, irr::EKEY_CODE::KEY_LEFT,
                        irr::EKEY_CODE::KEY_END };

}

int &Settings::music_volume_impl() {
    return _music_volume;
}

int &Settings::sound_volume_impl() {
    return _sound_volume;
}

std::array<irr::EKEY_CODE, 5> &Settings::keyMapP2_impl() {
    return _keyMapP1;
}

std::array<irr::EKEY_CODE, 5> &Settings::keyMapP1_impl() {
    return _keyMapP2;
}

int &Settings::music_volume() {
    return Settings::instance().music_volume_impl();
}

int &Settings::sound_volume() {
    return Settings::instance().sound_volume_impl();
}


std::array<irr::EKEY_CODE, 5> &Settings::keyMapP1() {
    return Settings::instance().keyMapP1_impl();
}

std::array<irr::EKEY_CODE, 5> &Settings::keyMapP2() {
    return Settings::instance().keyMapP2_impl();
}

std::string &Settings::refereePath() {
    return Settings::instance().refereePath_impl();
}

bool &Settings::p2isAI() {
    return Settings::instance().p2isAI_impl();
}

std::string &Settings::refereePath_impl() {
    return _refereePath;
}

bool & Settings::p2isAI_impl() {
    return _p2isAI;
}

std::array<int, 3> &Settings::aisLevel_impl() {
    return _aisLevel;
}

std::array<int, 3> &Settings::aisLevel() {
    return Settings::instance().aisLevel_impl();
}
