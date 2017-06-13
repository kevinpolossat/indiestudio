#include <algorithm>
#include "Error.hh"
#include "EventHandler.hh"

EventHandler::EventHandler() {
    for (irr::u32 i = 0; i < irr::KEY_KEY_CODES_COUNT; ++i)
        this->KeyIsDown[i] = false;
    this->_leftMouseClick = false;
}

bool EventHandler::OnEvent(irr::SEvent const & event) {
    if (event.EventType == irr::EET_KEY_INPUT_EVENT) {
        this->KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
//        std::cout << event.KeyInput.Key << std::endl;
    } else if (event.EventType == irr::EET_MOUSE_INPUT_EVENT) {
        switch(event.MouseInput.Event)
        {
            case irr::EMIE_LMOUSE_PRESSED_DOWN:
                this->_leftMouseClick = true;
                break;

            case irr::EMIE_LMOUSE_LEFT_UP:
                this->_leftMouseClick = false;
                break;

            case irr::EMIE_MOUSE_MOVED:
                this->_cursorPos.X = event.MouseInput.X;
                this->_cursorPos.Y = event.MouseInput.Y;
                break;

            default:
                break;
        }
    } else if (event.EventType == irr::EET_JOYSTICK_INPUT_EVENT) {
//        std::cout << "JOYSTICK event" << std::endl;
        if (event.JoystickEvent.Joystick == 0) {
            this->_joystick1 = event.JoystickEvent;
        } else if (event.JoystickEvent.Joystick == 1) {
            this->_joystick2 = event.JoystickEvent;
        }
    }
    return false;
}

bool EventHandler::isKeyDown(irr::EKEY_CODE keyCode) const {
    return this->KeyIsDown[keyCode];
}

irr::core::vector2d<irr::s32> EventHandler::getMousePos() const {
    return this->_cursorPos;
}

irr::SEvent::SJoystickEvent
EventHandler::getJoystick(irr::u8 const &id) const {
    if (id > 1) {
        throw BadArgument("EventHandler::getJoystick", "id can't be > 1");
    }
    return id == 0 ? this->_joystick1 : this->_joystick2;
}

bool
EventHandler::isMouseLeftClickPressed() const {
    return this->_leftMouseClick;
}