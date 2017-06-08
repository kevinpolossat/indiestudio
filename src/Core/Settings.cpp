//
// Created by kevin on 15/05/17.
//

#include "Settings.hh"

Settings::Settings() {

}

Settings::~Settings() {

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