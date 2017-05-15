/*
** MenuSettingsPage.cpp for indiestudio in /home/fraiss_c/rendu/indiestudio/MenuSettingsPage.cpp
**
** Made by Charles Fraïssé
** Login   <charles.fraisse@epitech.eu>
**
** Started on  Mon May 15 14:14:49 2017 Charles Fraïssé
** Last update Mon May 15 14:14:49 2017 Charles Fraïssé
*/

#include "MenuSettingsPage.hh"
/*
MenuSettingsPage::MenuSettingsPage(irr::IrrlichtDevice *device) : Scene(device) {

}

MenuSettingsPage::~MenuSettingsPage() {

}

bool
MenuSettingsPage::setScene(irr::IrrlichtDevice *device) {
    this->_bg = this->_gui->addButton( irr::core::rect<irr::s32>(0, 0, 1920, 1080), 0, -1, NULL);
    this->_bg->setImage(this->_driver->getTexture("BG.png"));
    this->_bg->setUseAlphaChannel(true);
    this->_bg->setDrawBorder(false);
    this->_time = device->getTimer()->getTime();
}

int
MenuSettingsPage::refresh(irr::IrrlichtDevice *device, int *menuState, EventReceiver *receiver) {
    const irr::u32 now = device->getTimer()->getTime();
    const irr::f32 frameDeltaTime = (irr::f32) (now - this->_time) / 1000.f;

    if (frameDeltaTime > 0.075) {
        this->_time = now;
        if (receiver->IsKeyDown(irr::KEY_LEFT)) {
            this->unsetScene();
            *menuState = 0;
            return 1;
        }
    }
    this->_gui->drawAll();
    this->_smgr->drawAll();
    this->_driver->endScene();
    return 2;
}

void
MenuSettingsPage::unsetScene() {
    this->_gui->clear();
}*/