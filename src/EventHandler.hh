#ifndef _EVENTHANDLER_HH__
#define _EVENTHANDLER_HH__

#include <irrlicht.h>
#include <iostream>

class EventHandler : public irr::IEventReceiver {
public:
	EventHandler();
	virtual bool OnEvent(irr::SEvent const & event);
	virtual bool isKeyDown(irr::EKEY_CODE keyCode) const;

private:
	bool KeyIsDown[irr::KEY_KEY_CODES_COUNT];
};

#endif /*_EVENTHANDLER_HH__*/
