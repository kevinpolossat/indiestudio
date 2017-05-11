#include "EventHandler.hh"

EventHandler::EventHandler() {
	for (irr::u32 i = 0; i < irr::KEY_KEY_CODES_COUNT; ++i)
		KeyIsDown[i] = false;
}

bool EventHandler::OnEvent(irr::SEvent const & event) {
	if (event.EventType == irr::EET_KEY_INPUT_EVENT) {
		KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
	} else if (event.EventType == irr::EET_MOUSE_INPUT_EVENT) {
		_cursorPos.X = event.MouseInput.X;
		_cursorPos.Y = event.MouseInput.Y;
	}
	return false;
}

bool EventHandler::isKeyDown(irr::EKEY_CODE keyCode) const {
	return KeyIsDown[keyCode];
}

irr::core::vector2d<irr::s32> EventHandler::getMousePos() const {
	return _cursorPos;
}
