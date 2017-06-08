//
// Created by kevin on 15/05/17.
//

#include <fstream>

#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

#include "Settings.hh"

Settings::Settings() {
    std::ifstream ifs("./saves/.settings");
    if (ifs.good()) {
        boost::archive::text_iarchive ia(ifs);
        ia >> *this;
        std::min(std::max(0, _music_volume), 10);
        std::min(std::max(0, _sound_volume), 10);
    }
    else {
        _music_volume = 10;
        _sound_volume = 10;
    }
}

Settings::~Settings() {
    std::ofstream ofs("./saves/.settings");

    if (ofs.good()) {
        boost::archive::text_oarchive ia(ofs);
        ia << *this;
    }
}

Settings &Settings::instance() {
    static Settings settings;
    return settings;
}

int &Settings::music_volume_impl() {
    return _music_volume;
}

int &Settings::sound_volume_impl() {
    return _sound_volume;
}

int &Settings::music_volume() {
    return Settings::instance()._music_volume;
}

int &Settings::sound_volume() {
    return Settings::instance()._sound_volume;
}