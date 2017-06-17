#ifndef _EVENTHANDLER_HH__
#define _EVENTHANDLER_HH__

#include <irrlicht.h>
#include <iostream>
#include <vector>

class EventHandler : public irr::IEventReceiver {
public:
    EventHandler();
    virtual bool                    OnEvent(irr::SEvent const & event);
    bool                            isKeyDown(irr::EKEY_CODE keyCode) const;
    irr::core::vector2d<irr::s32>   getMousePos() const;
    irr::SEvent::SJoystickEvent     getJoystick(irr::u8 const &) const;
    bool                            isMouseLeftClickPressed() const;
    irr::EKEY_CODE                  getKeyPressed() const;
    void                            resetLastKeyPressed();
    bool                            isAnyKeyPressed() const;

private:
    bool                                         KeyIsDown[irr::KEY_KEY_CODES_COUNT];
    bool                                         _leftMouseClick;
    irr::core::vector2d<irr::s32>                _cursorPos;
    irr::SEvent::SJoystickEvent                  _joystick1;
    irr::SEvent::SJoystickEvent                  _joystick2;
    irr::EKEY_CODE                               _lastKeyPressed;
};

#endif /*_EVENTHANDLER_HH__*/
