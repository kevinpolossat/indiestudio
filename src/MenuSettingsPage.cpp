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
    this->_bHeight = 60;
    this->_bWidth = 250;
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
    this->_back = ResourceManager::device()->getGUIEnvironment()->addButton(irr::core::rect<irr::s32>(this->_hpad, this->_vpad, this->_bWidth + this->_hpad, this->_bHeight + this->_vpad), 0, -1, L"Back");
    this->_reset = ResourceManager::device()->getGUIEnvironment()->addButton(irr::core::rect<irr::s32>(1920 - (this->_bWidth + this->_hpad), this->_vpad, 1920 - this->_hpad, this->_bHeight + this->_vpad), 0, -1, L"Reset");
    this->_player1Bomb = ResourceManager::device()->getGUIEnvironment()->addButton(irr::core::rect<irr::s32>(this->_hpad, 1080 - (this->_vpad + this->_bHeight) * 2, 480 - (this->_hpad / 2), 1080 - this->_vpad - this->_bHeight), 0, -1, L"Place Bomb");
    this->_player1BombKey = ResourceManager::device()->getGUIEnvironment()->addButton(irr::core::rect<irr::s32>(480 + (this->_hpad / 2), 1080 - (this->_vpad + this->_bHeight) * 2, 960 - this->_hpad, 1080 - this->_vpad - this->_bHeight), 0, -1, L"Place Bomb Key");
    this->_player2Bomb = ResourceManager::device()->getGUIEnvironment()->addButton(irr::core::rect<irr::s32>(960 + this->_hpad, 1080 - (this->_vpad + this->_bHeight) * 2, 1440 - (this->_hpad / 2), 1080 - this->_vpad - this->_bHeight), 0, -1, L"Place Bomb");
    this->_player2BombKey = ResourceManager::device()->getGUIEnvironment()->addButton(irr::core::rect<irr::s32>(1440 + (this->_hpad / 2), 1080 - (this->_vpad + this->_bHeight) * 2, 1920 - this->_hpad, 1080 - (this->_vpad + this->_bHeight)), 0, -1, L"Place Bomb Key");
    this->_player1Right = ResourceManager::device()->getGUIEnvironment()->addButton(irr::core::rect<irr::s32>(this->_hpad, 1080 - (this->_vpad + this->_bHeight) * 3 - this->_vpad, 480 - (this->_hpad / 2), 1080 - (this->_vpad + this->_bHeight) * 2 - this->_vpad), 0, -1, L"Move Right");
    this->_player1RightKey = ResourceManager::device()->getGUIEnvironment()->addButton(irr::core::rect<irr::s32>(480 + (this->_hpad / 2), 1080 - (this->_vpad + this->_bHeight) * 3 - this->_vpad, 960 - this->_hpad, 1080 - (this->_vpad + this->_bHeight) * 2 - this->_vpad), 0, -1, L"Move Right Key");
    this->_player2Right = ResourceManager::device()->getGUIEnvironment()->addButton(irr::core::rect<irr::s32>(960 + this->_hpad, 1080 - (this->_vpad + this->_bHeight) * 3 - this->_vpad, 1440 - (this->_hpad / 2), 1080 - (this->_vpad + this->_bHeight) * 2 - this->_vpad), 0, -1, L"Move Right");
    this->_player2RightKey = ResourceManager::device()->getGUIEnvironment()->addButton(irr::core::rect<irr::s32>(1440 + (this->_hpad / 2), 1080 - (this->_vpad + this->_bHeight) * 3 - this->_vpad, 1920 - this->_hpad, 1080 - (this->_vpad + this->_bHeight) * 2 - this->_vpad), 0, -1, L"Move Right Key");
    this->_player1Left = ResourceManager::device()->getGUIEnvironment()->addButton(irr::core::rect<irr::s32>(this->_hpad, 1080 - (this->_vpad + this->_bHeight) * 4 - this->_vpad * 2, 480 - (this->_hpad / 2), 1080 - (this->_vpad + this->_bHeight) * 3 - this->_vpad * 2), 0, -1, L"Move Left");
    this->_player1LeftKey = ResourceManager::device()->getGUIEnvironment()->addButton(irr::core::rect<irr::s32>(480 + (this->_hpad / 2), 1080 - (this->_vpad + this->_bHeight) * 4 - this->_vpad * 2, 960 - this->_hpad, 1080 - (this->_vpad + this->_bHeight) * 3 - this->_vpad * 2), 0, -1, L"Move Left Key");
    this->_player2Left = ResourceManager::device()->getGUIEnvironment()->addButton(irr::core::rect<irr::s32>(960 + this->_hpad, 1080 - (this->_vpad + this->_bHeight) * 4 - this->_vpad * 2, 1440 - (this->_hpad / 2), 1080 - (this->_vpad + this->_bHeight) * 3 - this->_vpad * 2), 0, -1, L"Move Left");
    this->_player2LeftKey = ResourceManager::device()->getGUIEnvironment()->addButton(irr::core::rect<irr::s32>(1440 + (this->_hpad / 2), 1080 - (this->_vpad + this->_bHeight) * 4 - this->_vpad * 2, 1920 - this->_hpad, 1080 - (this->_vpad + this->_bHeight) * 3 - this->_vpad * 2), 0, -1, L"Move Left Key");
    this->_player1Down = ResourceManager::device()->getGUIEnvironment()->addButton(irr::core::rect<irr::s32>(this->_hpad, 1080 - (this->_vpad + this->_bHeight) * 5 - this->_vpad * 3, 480 - (this->_hpad / 2), 1080 - (this->_vpad + this->_bHeight) * 4 - this->_vpad * 3), 0, -1, L"Move Down");
    this->_player1DownKey = ResourceManager::device()->getGUIEnvironment()->addButton(irr::core::rect<irr::s32>(480 + (this->_hpad / 2), 1080 - (this->_vpad + this->_bHeight) * 5 - this->_vpad * 3, 960 - this->_hpad, 1080 - (this->_vpad + this->_bHeight) * 4 - this->_vpad * 3), 0, -1, L"Move Down Key");
    this->_player2Down = ResourceManager::device()->getGUIEnvironment()->addButton(irr::core::rect<irr::s32>(960 + this->_hpad, 1080 - (this->_vpad + this->_bHeight) * 5 - this->_vpad * 3, 1440 - (this->_hpad / 2), 1080 - (this->_vpad + this->_bHeight) * 4 - this->_vpad * 3), 0, -1, L"Move Down");
    this->_player2DownKey = ResourceManager::device()->getGUIEnvironment()->addButton(irr::core::rect<irr::s32>(1440 + (this->_hpad / 2), 1080 - (this->_vpad + this->_bHeight) * 5 - this->_vpad * 3, 1920 - this->_hpad, 1080 - (this->_vpad + this->_bHeight) * 4 - this->_vpad * 3), 0, -1, L"Move Down Key");
    this->_player1Up = ResourceManager::device()->getGUIEnvironment()->addButton(irr::core::rect<irr::s32>(this->_hpad, 1080 - (this->_vpad + this->_bHeight) * 6 - this->_vpad * 4, 480 - (this->_hpad / 2), 1080 - (this->_vpad + this->_bHeight) * 5 - this->_vpad * 4), 0, -1, L"Move Up");
    this->_player1UpKey = ResourceManager::device()->getGUIEnvironment()->addButton(irr::core::rect<irr::s32>(480 + (this->_hpad / 2), 1080 - (this->_vpad + this->_bHeight) * 6 - this->_vpad * 4, 960 - this->_hpad, 1080 - (this->_vpad + this->_bHeight) * 5 - this->_vpad * 4), 0, -1, L"Move Up Key");
    this->_player2Up = ResourceManager::device()->getGUIEnvironment()->addButton(irr::core::rect<irr::s32>(960 + this->_hpad, 1080 - (this->_vpad + this->_bHeight) * 6 - this->_vpad * 4, 1440 - (this->_hpad / 2), 1080 - (this->_vpad + this->_bHeight) * 5 - this->_vpad * 4), 0, -1, L"Move Up");
    this->_player2UpKey = ResourceManager::device()->getGUIEnvironment()->addButton(irr::core::rect<irr::s32>(1440 + (this->_hpad / 2), 1080 - (this->_vpad + this->_bHeight) * 6 - this->_vpad * 4, 1920 - this->_hpad, 1080 - (this->_vpad + this->_bHeight) * 5 - this->_vpad * 4), 0, -1, L"Move Up Key");
    this->_player1Title = ResourceManager::device()->getGUIEnvironment()->addButton(irr::core::rect<irr::s32>(this->_hpad, 1080 - (this->_vpad + this->_bHeight) * 7.5 - this->_vpad * 6, 960 - this->_hpad, 1080 - (this->_vpad + this->_bHeight) * 6 - this->_vpad * 6), 0, -1, L"PLAYER 1");
    this->_player2Title = ResourceManager::device()->getGUIEnvironment()->addButton(irr::core::rect<irr::s32>(960 + this->_hpad, 1080 - (this->_vpad + this->_bHeight) * 7.5 - this->_vpad * 6, 1920 - this->_hpad,  1080 - (this->_vpad + this->_bHeight) * 6 - this->_vpad * 6), 0, -1, L"PLAYER 2");
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