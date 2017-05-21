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
