/*
** MenuGameMode.cpp for indiestudio in /home/fraiss_c/rendu/indiestudio/MenuGameMode.cpp
**
** Made by Charles Fraïssé
** Login   <charles.fraisse@epitech.eu>
**
** Started on  Mon May 29 16:18:26 2017 Charles Fraïssé
** Last update Mon May 29 16:18:26 2017 Charles Fraïssé
*/

#include "MenuGameMode.hh"

MenuGameMode::MenuGameMode() {
    this->_hpad = 60;
    this->_bHeight = 125;
}

MenuGameMode::~MenuGameMode() {

}

bool
MenuGameMode::setScene() {
    this->unsetScene();
    this->_bg = ResourceManager::device()->getGUIEnvironment()->addButton( irr::core::rect<irr::s32>(0, 0, 1920, 1080), 0, -1, NULL);
    this->_bg->setImage(ResourceManager::device()->getVideoDriver()->getTexture("./assets/BG.png"));
    this->_bg->setUseAlphaChannel(true);
    this->_bg->setDrawBorder(false);
    this->_back = ResourceManager::device()->getGUIEnvironment()->addButton(irr::core::rect<irr::s32>(10, 10, 250 + 10, 60 + 10), 0, -1, L"Back");
    this->_local = ResourceManager::device()->getGUIEnvironment()->addButton(irr::core::rect<irr::s32>(this->_hpad, (1080 / 2) - (this->_bHeight / 2), (1920 / 2) - this->_hpad, (1080 / 2) + (this->_bHeight / 2)), 0, -1, L"LOCAL");
    this->_online = ResourceManager::device()->getGUIEnvironment()->addButton(irr::core::rect<irr::s32>((1920 / 2) + this->_hpad, (1080 / 2) - (this->_bHeight / 2), 1920 - this->_hpad, (1080 / 2) + (this->_bHeight / 2)), 0, -1, L"ONLINE");
    return true;
}

int
MenuGameMode::refresh(int &menuState) {
    if (this->_back->isPressed()) {
        this->unsetScene();
        menuState = MENUMAINPAGE;
        return 1;
    } else if (this->_local->isPressed()) {
        this->unsetScene();
        menuState = SCENEGAME;
        return 1;
    }
    ResourceManager::guiEnvironment()->drawAll();
    ResourceManager::sceneManager()->drawAll();
    ResourceManager::videoDriver()->endScene();
    return 2;
}

void
MenuGameMode::unsetScene() {
    ResourceManager::device()->getGUIEnvironment()->clear();
}