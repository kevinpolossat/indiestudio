/*
** EventReceiver.cpp for indiestudio in /home/fraiss_c/rendu/indiestudio/EventReceiver.cpp
**
** Made by Charles Fraïssé
** Login   <charles.fraisse@epitech.eu>
**
** Started on  Thu May 11 10:39:14 2017 Charles Fraïssé
** Last update Thu May 11 10:39:14 2017 Charles Fraïssé
*/

#include "EventReceiver.hh"

EventReceiver::EventReceiver() {
    for (int i = 0; i < irr::KEY_KEY_CODES_COUNT; i++) {
        this->_Keys[i] = false;
    }
}

EventReceiver::~EventReceiver() {

}

bool
EventReceiver::OnEvent(const irr::SEvent &event) {
    if (event.EventType == irr::EET_KEY_INPUT_EVENT)
        this->_Keys[event.KeyInput.Key] = event.KeyInput.PressedDown;
    return false;
}

bool
EventReceiver::IsKeyDown(irr::EKEY_CODE code) const {
    return this->_Keys[code];
}