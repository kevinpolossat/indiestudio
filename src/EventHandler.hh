#ifndef _EVENTHANDLER_HH__
#define _EVENTHANDLER_HH__

#include <irrlicht.h>
#include <iostream>

class EventHandler : public irr::IEventReceiver {
public:
	EventHandler();
	virtual bool                  OnEvent(irr::SEvent const & event);
	bool                          isKeyDown(irr::EKEY_CODE keyCode) const;
	irr::core::vector2d<irr::s32> getMousePos() const;


private:
	bool                          KeyIsDown[irr::KEY_KEY_CODES_COUNT];
	irr::core::vector2d<irr::s32> _cursorPos;
};

#endif /*_EVENTHANDLER_HH__*/
