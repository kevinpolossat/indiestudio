//
// Created by kevin on 15/05/17.
//

#include "Settings.hh"

Settings::Settings(int mv, int sv): _music_volume(mv), _sound_volume(sv) {

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