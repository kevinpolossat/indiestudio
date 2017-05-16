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

MenuSettingsPage::MenuSettingsPage(ResourceManager & rm) : rm(rm){

}

MenuSettingsPage::~MenuSettingsPage() {

}

bool
MenuSettingsPage::setScene() {
    this->_bg = rm.device()->getGUIEnvironment()->addButton( irr::core::rect<irr::s32>(0, 0, 1920, 1080), 0, -1, NULL);
    this->_bg->setImage(rm.device()->getVideoDriver()->getTexture("./assets/BG.png"));
    this->_bg->setUseAlphaChannel(true);
    this->_bg->setDrawBorder(false);
    this->_time = rm.device()->getTimer()->getTime();
    return true;
}

int
MenuSettingsPage::refresh(int *menuState) {
    const irr::u32 now = rm.device()->getTimer()->getTime();
    const irr::f32 frameDeltaTime = (irr::f32) (now - this->_time) / 1000.f;

    if (frameDeltaTime > 0.075) {
        this->_time = now;
        if (rm.eventHandler().isKeyDown(irr::KEY_LEFT)) {
            this->unsetScene();
            *menuState = 0;
            return 1;
        }
    }
    return 2;
}

void
MenuSettingsPage::unsetScene() {
    rm.device()->getGUIEnvironment()->clear();
}