#include "Game.hh"

int main(void) {
	Game bomberman;

	return bomberman.run();
}
/*
#include <iostream>
#include <vector>
#include <memory>
#include "Scene.hh"
#include "MenuMainPage.hh"
#include "MenuSettingsPage.hh"
#include "EventReceiver.hh"

int main() {

    EventReceiver receiver;

    irr::IrrlichtDevice *device = irr::createDevice(irr::video::EDT_OPENGL, irr::core::dimension2d<irr::u32>(1920, 1080), 16, false, false, false, &receiver);
    if (!device)
        return 1;

    device->setWindowCaption(L"BOMBERBOOM");

    std::vector<std::unique_ptr<Scene>>    Scenes;
    int menuState = 0;

    Scenes.push_back(std::make_unique<MenuMainPage>(device));
    Scenes.push_back(std::make_unique<MenuSettingsPage>(device));
    Scenes.push_back(std::make_unique<MenuSettingsPage>(device));
    if (!Scenes[menuState]->setScene(device)) {
        return 0;
    }
    while (device->run()) {
        int rtn = Scenes[menuState]->refresh(device, &menuState, &receiver);
        if (!rtn) {
            break;
        } else if (rtn == 1) {
            if (!Scenes[menuState]->setScene(device))
                return 0;
        }
    }
    device->drop();
    return 0;
}
*/
