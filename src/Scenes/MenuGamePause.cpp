/*
** MenuGamePause.cpp for indiestudio in /home/fraiss_c/rendu/indiestudio/MenuGamePause.cpp
**
** Made by Charles Fraïssé
** Login   <charles.fraisse@epitech.eu>
**
** Started on  Wed May 17 10:22:16 2017 Charles Fraïssé
** Last update Wed May 17 10:22:16 2017 Charles Fraïssé
*/

#include "MenuGamePause.hh"

MenuGamePause::MenuGamePause() {
}

MenuGamePause::~MenuGamePause() {

}

bool
MenuGamePause::setScene() {
    int verticalSize = 100;
    int horizontalSize = 500 - 100;
    float verticalPadding = (1080 - 400 - (verticalSize * 4)) / 5;
    float horizontalPadding = 50;
    this->_bg = ResourceManager::device()->getGUIEnvironment()->addButton( irr::core::rect<irr::s32>(710, 200, 500 + 710, 1080 - 200), 0, -1, NULL);
    this->_bg->setImage(ResourceManager::device()->getVideoDriver()->getTexture("assets/BG.png"));
    this->_bg->setUseAlphaChannel(true);
    this->_bg->setDrawBorder(false);
    this->_resume = ResourceManager::guiEnvironment()->addButton(irr::core::rect<irr::s32>(760 , 200 + verticalPadding, 760 + horizontalSize, 200 + verticalPadding + verticalSize), 0, 42, NULL);
    this->_resume->setImage(ResourceManager::device()->getVideoDriver()->getTexture("assets/Fonts/Resume_400x100.png"));
    this->_resume->setUseAlphaChannel(true);
    this->_resume->setDrawBorder(false);
    this->_save = ResourceManager::guiEnvironment()->addButton(irr::core::rect<irr::s32>(760 , 200 + verticalSize + verticalPadding * 2, 760 + horizontalSize, 200 + verticalSize * 2 + verticalPadding * 2), 0, 42, NULL);
    this->_save->setImage(ResourceManager::device()->getVideoDriver()->getTexture("assets/Fonts/Save_400x100.png"));
    this->_save->setUseAlphaChannel(true);
    this->_save->setDrawBorder(false);
    this->_settings = ResourceManager::guiEnvironment()->addButton(irr::core::rect<irr::s32>(760 , 200 + verticalSize * 2 + verticalPadding * 3, 760 + horizontalSize, 200 + verticalSize * 3 + verticalPadding * 3), 0, 42, NULL);
    this->_settings->setImage(ResourceManager::device()->getVideoDriver()->getTexture("assets/Fonts/Settings_400x100.png"));
    this->_settings->setUseAlphaChannel(true);
    this->_settings->setDrawBorder(false);
    this->_leave = ResourceManager::guiEnvironment()->addButton(irr::core::rect<irr::s32>(760 , 200 + verticalSize * 3 + verticalPadding * 4, 760 + horizontalSize, 200 + verticalSize * 4 + verticalPadding * 4), 0, 42, NULL);
    this->_leave->setImage(ResourceManager::device()->getVideoDriver()->getTexture("assets/Fonts/Exit_400x100.png"));
    this->_leave->setUseAlphaChannel(true);
    this->_leave->setDrawBorder(false);
    return true;
}

int
MenuGamePause::refresh(int &menuState) {
    if (this->_resume->isPressed()) {
        this->unsetScene();
        menuState = SCENEGAME;
        return 2;
    } else if (this->_save->isPressed()) {
        this->unsetScene();
        menuState = SCENEGAME;
        return 2;
    } else if (this->_settings->isPressed()) {
        this->unsetScene();
        menuState = SCENEGAME;
        return 2;
    } else if (this->_leave->isPressed()) {
        menuState = MENUMAINPAGE;
        ResourceManager::guiEnvironment()->clear();
        ResourceManager::sceneManager()->clear();
        return 1;
    }
    ResourceManager::guiEnvironment()->drawAll();
    ResourceManager::sceneManager()->drawAll();
    this->drawGui();
    ResourceManager::videoDriver()->endScene();
    return 2;
}

void
MenuGamePause::unsetScene() {
    this->_bg->remove();
    this->_resume->remove();
    this->_save->remove();
    this->_settings->remove();
    this->_leave->remove();
}

void
MenuGamePause::drawGui() const {
    this->_bg->draw();
    this->_resume->draw();
    this->_leave->draw();
    this->_save->draw();
    this->_settings->draw();
}