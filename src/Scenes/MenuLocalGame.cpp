/*
** MenuLocalGame.cpp for indiestudio in /home/fraiss_c/rendu/indiestudio/MenuLocalGame.cpp
**
** Made by Charles Fraïssé
** Login   <charles.fraisse@epitech.eu>
**
** Started on  Tue May 30 10:43:38 2017 Charles Fraïssé
** Last update Tue May 30 10:43:38 2017 Charles Fraïssé
*/

#include <Settings.hh>
#include "MenuLocalGame.hh"

MenuLocalGame::MenuLocalGame() {
    this->_hpad = 60;
    this->_bHeight = 125;
    this->_isP2IA = true;
}

MenuLocalGame::~MenuLocalGame() {

}

bool
MenuLocalGame::setScene() {
    _frame = 0;
    this->unsetScene();
    this->_bg = ResourceManager::device()->getGUIEnvironment()->addButton( irr::core::rect<irr::s32>(0, 0, 1920, 1080), 0, -1, NULL);
    this->_bg->setImage(ResourceManager::device()->getVideoDriver()->getTexture((ResourceManager::assets_rela + "BG.png").c_str()));
    this->_bg->setUseAlphaChannel(true);
    this->_bg->setDrawBorder(false);
    this->_bg->setEnabled(false);

    this->_back = ResourceManager::device()->getGUIEnvironment()->addButton(irr::core::rect<irr::s32>(10, 10, 250 + 10, 60 + 10), 0, -1, NULL);
    this->_back->setImage(ResourceManager::device()->getVideoDriver()->getTexture((ResourceManager::assets_rela + "Fonts/Back_250x60.png").c_str()));
    this->_back->setUseAlphaChannel(true);
    this->_back->setDrawBorder(false);

    this->_confirm = ResourceManager::device()->getGUIEnvironment()->addButton(irr::core::rect<irr::s32>(960 - 250, 1080 - 100 - 40, 960 + 250, 1080 - 20 - 40), 0, -1, NULL);
    this->_confirm->setImage(ResourceManager::device()->getVideoDriver()->getTexture((ResourceManager::assets_rela + "Fonts/Confirm_500x80.png").c_str()));
    this->_confirm->setUseAlphaChannel(true);
    this->_confirm->setDrawBorder(false);


    this->P1Picture = ResourceManager::device()->getGUIEnvironment()->addButton(irr::core::rect<irr::s32>(480 - 300, 287.5 - 150 - 40, 480 + 300, 287.5 + 150 - 40), 0, -1, NULL);
    this->P1Picture->setImage(ResourceManager::device()->getVideoDriver()->getTexture((ResourceManager::assets_rela + "player_blue.png").c_str()));
    this->P1Picture->setUseAlphaChannel(true);
    this->P1Picture->setDrawBorder(false);
    this->P1Picture->setEnabled(false);

    this->P1Role = ResourceManager::device()->getGUIEnvironment()->addButton(irr::core::rect<irr::s32>(480 - 300, 287.5 + 150 - 40 + 10, 480 + 300, 287.5 + 150 - 40 + 80), 0, -1, NULL);
    this->P1Role->setImage(ResourceManager::device()->getVideoDriver()->getTexture((ResourceManager::assets_rela + "Fonts/Player1_600x70.png").c_str()));
    this->P1Role->setUseAlphaChannel(true);
    this->P1Role->setDrawBorder(false);
    this->P1Role->setEnabled(false);


    this->P2Picture = ResourceManager::device()->getGUIEnvironment()->addButton(irr::core::rect<irr::s32>(1440 - 300, 287.5 - 150 - 40, 1440 + 300, 287.5 + 150 - 40), 0, -1, NULL);
    this->P2Picture->setImage(ResourceManager::device()->getVideoDriver()->getTexture((ResourceManager::assets_rela + "player_orange.png").c_str()));
    this->P2Picture->setUseAlphaChannel(true);
    this->P2Picture->setDrawBorder(false);
    this->P2Picture->setEnabled(false);

    this->P2Role = ResourceManager::device()->getGUIEnvironment()->addButton(irr::core::rect<irr::s32>(1440 - 300, 287.5 + 150 - 40 + 10, 1440 + 300, 287.5 + 150 - 40 + 80), 0, -1, NULL);
    this->P2Role->setImage(ResourceManager::device()->getVideoDriver()->getTexture((ResourceManager::assets_rela + "Fonts/Computer_600x70.png").c_str()));
    this->P2Role->setUseAlphaChannel(true);
    this->P2Role->setDrawBorder(false);
    this->P2Role->setEnabled(false);

    this->P2RoleLeft = ResourceManager::device()->getGUIEnvironment()->addButton(irr::core::rect<irr::s32>(1440 - 300 - 90, 287.5 + 150 - 40 + 10, 1440 - 300 - 10, 287.5 + 150 - 40 + 80), 0, -1, NULL);
    this->P2RoleLeft->setImage(ResourceManager::device()->getVideoDriver()->getTexture((ResourceManager::assets_rela + "Fonts/LeftArrow_70x70.png").c_str()));
    this->P2RoleLeft->setUseAlphaChannel(true);
    this->P2RoleLeft->setDrawBorder(false);

    this->P2RoleRight = ResourceManager::device()->getGUIEnvironment()->addButton(irr::core::rect<irr::s32>(1440 + 300 + 10, 287.5 + 150 - 40 + 10, 1440 + 300 + 90, 287.5 + 150 - 40 + 80), 0, -1, NULL);
    this->P2RoleRight->setImage(ResourceManager::device()->getVideoDriver()->getTexture((ResourceManager::assets_rela + "Fonts/RightArrow_70x70.png").c_str()));
    this->P2RoleRight->setUseAlphaChannel(true);
    this->P2RoleRight->setDrawBorder(false);


    this->P3Picture = ResourceManager::device()->getGUIEnvironment()->addButton(irr::core::rect<irr::s32>(480 - 300, 722.5 - 150 - 40, 480 + 300, 722.5 + 150 - 40), 0, -1, NULL);
    this->P3Picture->setImage(ResourceManager::device()->getVideoDriver()->getTexture((ResourceManager::assets_rela + "player_green.png").c_str()));
    this->P3Picture->setUseAlphaChannel(true);
    this->P3Picture->setDrawBorder(false);
    this->P3Picture->setEnabled(false);

    this->P3Role = ResourceManager::device()->getGUIEnvironment()->addButton(irr::core::rect<irr::s32>(480 - 300, 722.5 + 150 - 40 + 10, 480 + 300, 722.5 + 150 - 40 + 80), 0, -1, NULL);
    this->P3Role->setImage(ResourceManager::device()->getVideoDriver()->getTexture((ResourceManager::assets_rela + "Fonts/Computer_600x70.png").c_str()));
    this->P3Role->setUseAlphaChannel(true);
    this->P3Role->setDrawBorder(false);
    this->P3Role->setEnabled(false);


    this->P4Picture = ResourceManager::device()->getGUIEnvironment()->addButton(irr::core::rect<irr::s32>(1440 - 300, 722.5 - 150 - 40, 1440 + 300, 722.5 + 150 - 40), 0, -1, NULL);
    this->P4Picture->setEnabled(false);
    this->P4Picture->setImage(ResourceManager::device()->getVideoDriver()->getTexture((ResourceManager::assets_rela + "player_purple.png").c_str()));
    this->P4Picture->setUseAlphaChannel(true);
    this->P4Picture->setDrawBorder(false);
    this->P4Picture->setEnabled(false);

    this->P4Role = ResourceManager::device()->getGUIEnvironment()->addButton(irr::core::rect<irr::s32>(1440 - 300, 722.5 + 150 - 40 + 10, 1440 + 300, 722.5 + 150 - 40 + 80), 0, -1, NULL);
    this->P4Role->setImage(ResourceManager::device()->getVideoDriver()->getTexture((ResourceManager::assets_rela + "Fonts/Computer_600x70.png").c_str()));
    this->P4Role->setUseAlphaChannel(true);
    this->P4Role->setDrawBorder(false);
    this->P4Role->setEnabled(false);


    this->_time = ResourceManager::device()->getTimer()->getTime();
    return true;
}

int
MenuLocalGame::refresh(int &menuState) {
    const irr::u32 now = ResourceManager::device()->getTimer()->getTime();
    const irr::f32 frameDeltaTime = (irr::f32) (now - this->_time) / 1000.f;
    auto firstController = ResourceManager::eventHandler().getJoystick(ResourceManager::getControllers()[0]);
    if (this->_back->isPressed() || ResourceManager::eventHandler().isKeyDown(irr::KEY_ESCAPE) || firstController.ButtonStates == 4) {
        this->unsetScene();
        menuState = MENUGAMEMODE;
        return 1;
    } else if (this->_frame > 10 && (this->_confirm->isPressed() || firstController.ButtonStates == 2 || ResourceManager::eventHandler().isKeyDown(irr::KEY_RETURN))) {
        this->unsetScene();
        Settings::p2isAI() = this->_isP2IA;
        menuState = SCENEGAME;
        return 1;
    } else if (firstController.ButtonStates == 4096) {
        this->unsetScene();
        menuState = MENUMAINPAGE;
        return 1;
    } else if (this->P2RoleLeft->isPressed() || this->P2RoleRight->isPressed() || firstController.Axis[0] || ResourceManager::eventHandler().isKeyDown(irr::KEY_LEFT)
            || ResourceManager::eventHandler().isKeyDown(irr::KEY_RIGHT)) {
        if (frameDeltaTime > 0.075) {
            this->_time = now;
            if (this->_isP2IA) {
                this->P2Role->setImage(
                        ResourceManager::device()->getVideoDriver()->getTexture((ResourceManager::assets_rela + "Fonts/Player2_600x70.png").c_str()));
                this->_isP2IA = false;
            } else {
                this->P2Role->setImage(
                        ResourceManager::device()->getVideoDriver()->getTexture((ResourceManager::assets_rela + "Fonts/Computer_600x70.png").c_str()));
                this->_isP2IA = true;
            }
        }
    }
    if (this->_frame < 11)
        this->_frame += 1;
    ResourceManager::guiEnvironment()->drawAll();
    ResourceManager::sceneManager()->drawAll();
    ResourceManager::videoDriver()->endScene();
    return 2;
}

void
MenuLocalGame::unsetScene() {
    ResourceManager::device()->getGUIEnvironment()->clear();
}