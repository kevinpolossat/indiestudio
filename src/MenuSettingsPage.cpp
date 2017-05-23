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

MenuSettingsPage::MenuSettingsPage() {
    this->_vpad = 10;
    this->_hpad = 10;
    this->_bHeight = 50;
    this->_bWidth = 190;
}

MenuSettingsPage::~MenuSettingsPage() {

}

bool
MenuSettingsPage::setScene() {
    this->unsetScene();
    this->_bg = ResourceManager::device()->getGUIEnvironment()->addButton( irr::core::rect<irr::s32>(0, 0, 1920, 1080), 0, -1, NULL);
    this->_bg->setImage(ResourceManager::device()->getVideoDriver()->getTexture("./assets/BG.png"));
    this->_bg->setUseAlphaChannel(true);
    this->_bg->setDrawBorder(false);
    this->_time = ResourceManager::device()->getTimer()->getTime();
    this->_back = ResourceManager::device()->getGUIEnvironment()->addStaticText(L"Back", irr::core::rect<irr::s32>(this->_hpad, this->_vpad, this->_bWidth + this->_hpad, this->_bHeight + this->_vpad), true, true, 0, -1, true);
    this->_reset = ResourceManager::device()->getGUIEnvironment()->addStaticText(L"Reset", irr::core::rect<irr::s32>(1920 - (this->_bWidth + this->_hpad), this->_vpad, 1920 - this->_hpad, this->_bHeight + this->_vpad), true, true, 0, -1, true);
    return true;
}

int
MenuSettingsPage::refresh(int *menuState) {
    if (isMouseOnBack() && ResourceManager::eventHandler().isMouseLeftClickPressed()) {
        this->unsetScene();
        *menuState = 0;
        return 1;
    }
    ResourceManager::guiEnvironment()->drawAll();
    ResourceManager::sceneManager()->drawAll();
    ResourceManager::videoDriver()->endScene();
    return 2;
}

void
MenuSettingsPage::unsetScene() {
  ResourceManager::device()->getGUIEnvironment()->clear();
}

bool
MenuSettingsPage::isMouseOnBack() const {
    const irr::core::vector2d<irr::s32> mousePos = ResourceManager::eventHandler().getMousePos();
    return mousePos.X >= this->_hpad && mousePos.X <= (this->_bWidth + this->_hpad) && mousePos.Y >= this->_hpad && mousePos.Y <= (this->_bHeight + this->_vpad);
}

bool
MenuSettingsPage::isMouseOnReset() const {
    const irr::core::vector2d<irr::s32> mousePos = ResourceManager::eventHandler().getMousePos();
    return mousePos.X >= (1920 - (this->_bWidth + this->_hpad)) && mousePos.X <= (1920 - this->_hpad) && mousePos.Y >= this->_hpad && mousePos.Y <= (this->_bHeight + this->_vpad);
}