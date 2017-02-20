#include "EventHandler.hh"

EventHandler::EventHandler() {
  for (irr::u32 i = 0; i < irr::KEY_KEY_CODES_COUNT; ++i)
  KeyIsDown[i] = false;
}

bool EventHandler::OnEvent(irr::SEvent const & event) {
  if (event.EventType == irr::EET_KEY_INPUT_EVENT) {
    KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
  }
  return false;
}

bool EventHandler::isKeyDown(irr::EKEY_CODE keyCode) const {
  return KeyIsDown[keyCode];
}
