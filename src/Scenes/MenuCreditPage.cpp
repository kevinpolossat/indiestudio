/*
** MenuCreditPage.cpp for indiestudio in /home/fraiss_c/rendu/indiestudio/MenuCreditPage.cpp
**
** Made by Charles Fraïssé
** Login   <charles.fraisse@epitech.eu>
**
** Started on  Wed Jun 07 11:18:50 2017 Charles Fraïssé
** Last update Wed Jun 07 11:18:50 2017 Charles Fraïssé
*/

#include "MenuCreditPage.hh"

MenuCreditPage::MenuCreditPage() {
    this->_hpad = 60;
    this->_bHeight = 125;
}

MenuCreditPage::~MenuCreditPage() {

}

bool
MenuCreditPage::setScene() {
    this->_frame = 0;
    this->unsetScene();
    this->_bg = ResourceManager::device()->getGUIEnvironment()->addButton( irr::core::rect<irr::s32>(0, 0, 1920, 1080), 0, -1, NULL);
    this->_bg->setImage(ResourceManager::device()->getVideoDriver()->getTexture("./assets/BG.png"));
    this->_bg->setUseAlphaChannel(true);
    this->_bg->setDrawBorder(false);
    this->_bg->setEnabled(false);

    this->_credit = ResourceManager::videoDriver()->getTexture("./assets/BomberBoomCredit.png");
    return true;
}

int
MenuCreditPage::refresh(int &menuState) {
    int                 imageHeight = 7500;

    if (_frame > 10 &&ResourceManager::eventHandler().isKeyDown(irr::KEY_ESCAPE)) {
        this->unsetScene();
        menuState = MENUMAINPAGE;
        return 1;
    }
    ResourceManager::guiEnvironment()->drawAll();
    ResourceManager::videoDriver()->draw2DImage(this->_credit, irr::core::position2d<irr::s32>(0, -(3 * this->_frame)),
                                                irr::core::rect<irr::s32>(0, 0, 1920, imageHeight), 0,
                                                irr::video::SColor(255, 255, 255, 255), true);
    ResourceManager::sceneManager()->drawAll();
    ResourceManager::videoDriver()->endScene();
    if (this->_frame * 3 < imageHeight)
        this->_frame += 1;
    else {
        this->unsetScene();
        menuState = MENUMAINPAGE;
        return 1;
    }
    return 2;
}

void
MenuCreditPage::unsetScene() {
    ResourceManager::device()->getGUIEnvironment()->clear();
}