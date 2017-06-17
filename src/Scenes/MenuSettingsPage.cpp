/*
** MenuSettingsPage.cpp for indiestudio in /home/fraiss_c/rendu/indiestudio/MenuSettingsPage.cpp
**
** Made by Charles Fraïssé
** Login   <charles.fraisse@epitech.eu>
**
** Started on  Mon May 15 14:14:49 2017 Charles Fraïssé
** Last update Mon May 15 14:14:49 2017 Charles Fraïssé
*/

#include <Settings.hh>
#include "MenuSettingsPage.hh"

MenuSettingsPage::MenuSettingsPage() {
    this->_vpad = 10;
    this->_hpad = 10;
    this->_bHeight = 80;
    this->_bWidth = 250;
    this->_effectVolumeIdx = Settings::sound_volume();
    this->_musicVolumeIdx = Settings::music_volume();
    this->_volumePath.push_back(ResourceManager::assets_rela + "settings/Volume0_700x100.png");
    this->_volumePath.push_back(ResourceManager::assets_rela + "settings/Volume10_700x100.png");
    this->_volumePath.push_back(ResourceManager::assets_rela + "settings/Volume20_700x100.png");
    this->_volumePath.push_back(ResourceManager::assets_rela + "settings/Volume30_700x100.png");
    this->_volumePath.push_back(ResourceManager::assets_rela + "settings/Volume40_700x100.png");
    this->_volumePath.push_back(ResourceManager::assets_rela + "settings/Volume50_700x100.png");
    this->_volumePath.push_back(ResourceManager::assets_rela + "settings/Volume60_700x100.png");
    this->_volumePath.push_back(ResourceManager::assets_rela + "settings/Volume70_700x100.png");
    this->_volumePath.push_back(ResourceManager::assets_rela + "settings/Volume80_700x100.png");
    this->_volumePath.push_back(ResourceManager::assets_rela + "settings/Volume90_700x100.png");
    this->_volumePath.push_back(ResourceManager::assets_rela + "settings/Volume100_700x100.png");
    this->_wfkP1Up = false;
    this->_wfkP1Right = false;
    this->_wfkP1Down = false;
    this->_wfkP1Left = false;
    this->_wfkP1Bomb = false;
    this->_wfkP2Up = false;
    this->_wfkP2Right = false;
    this->_wfkP2Down = false;
    this->_wfkP2Left = false;
    this->_wfkP2Bomb = false;
    this->_bind = ResourceManager::videoDriver()->getTexture((ResourceManager::assets_rela + "bind.png").c_str());
}

MenuSettingsPage::~MenuSettingsPage() {

}

bool
MenuSettingsPage::setScene() {
    this->unsetScene();
    irr::video::ITexture *plus = ResourceManager::videoDriver()->getTexture((ResourceManager::assets_rela + "settings/plusBig_100x100.png").c_str());
    irr::video::ITexture *minus = ResourceManager::videoDriver()->getTexture((ResourceManager::assets_rela + "settings/minusBig_100x100.png").c_str());

    this->_bg = ResourceManager::device()->getGUIEnvironment()->addButton( irr::core::rect<irr::s32>(0, 0, 1920, 1080), 0, -1, NULL);
    this->_bg->setImage(ResourceManager::device()->getVideoDriver()->getTexture((ResourceManager::assets_rela + "BG.png").c_str()));
    this->_bg->setUseAlphaChannel(true);
    this->_bg->setDrawBorder(false);
    this->_bg->setEnabled(false);

    this->_back = ResourceManager::device()->getGUIEnvironment()->addButton(irr::core::rect<irr::s32>(10, 10, 250 + 10, 60 + 10), 0, -1, NULL);
    this->_back->setImage(ResourceManager::device()->getVideoDriver()->getTexture((ResourceManager::assets_rela + "Fonts/Back_250x60.png").c_str()));
    this->_back->setUseAlphaChannel(true);
    this->_back->setDrawBorder(false);

    this->_reset = ResourceManager::device()->getGUIEnvironment()->addButton(irr::core::rect<irr::s32>(1920 - (250 + 10), 0, 1920 - this->_hpad, this->_bHeight), 0, -1, NULL);
    this->_reset->setImage(ResourceManager::device()->getVideoDriver()->getTexture((ResourceManager::assets_rela + "settings/Reset_250x60.png").c_str()));
    this->_reset->setUseAlphaChannel(true);
    this->_reset->setDrawBorder(false);

    this->_effectVolumeTitle = ResourceManager::device()->getGUIEnvironment()->addButton(irr::core::rect<irr::s32>(10, 100, 520, 200), 0, -1, NULL);
    this->_effectVolumeTitle->setImage(ResourceManager::device()->getVideoDriver()->getTexture((ResourceManager::assets_rela + "settings/effectVolume_510x100.png").c_str()));
    this->_effectVolumeTitle->setUseAlphaChannel(true);
    this->_effectVolumeTitle->setDrawBorder(false);
    this->_effectVolumeTitle->setEnabled(false);

    this->_effectVolumeDOWN = ResourceManager::device()->getGUIEnvironment()->addButton(irr::core::rect<irr::s32>(530, 100, 630, 200), 0, -1, NULL);
    this->_effectVolumeDOWN->setPressedImage(minus);
    this->_effectVolumeDOWN->setImage(ResourceManager::device()->getVideoDriver()->getTexture((ResourceManager::assets_rela + "settings/minusLow_100x100.png").c_str()));
    this->_effectVolumeDOWN->setUseAlphaChannel(true);
    this->_effectVolumeDOWN->setDrawBorder(false);

    this->_effectVolume = ResourceManager::device()->getGUIEnvironment()->addButton(irr::core::rect<irr::s32>(640, 100, 1340, 200), 0, -1, NULL);
    this->_effectVolume->setImage(ResourceManager::device()->getVideoDriver()->getTexture((this->_volumePath[this->_effectVolumeIdx]).c_str()));
    this->_effectVolume->setUseAlphaChannel(true);
    this->_effectVolume->setDrawBorder(false);
    this->_effectVolume->setEnabled(false);

    this->_effectVolumeUP = ResourceManager::device()->getGUIEnvironment()->addButton(irr::core::rect<irr::s32>(1350, 100, 1450, 200), 0, -1, NULL);
    this->_effectVolumeUP->setPressedImage(plus);
    this->_effectVolumeUP->setImage(ResourceManager::device()->getVideoDriver()->getTexture((ResourceManager::assets_rela + "settings/plusLow_100x100.png").c_str()));
    this->_effectVolumeUP->setUseAlphaChannel(true);
    this->_effectVolumeUP->setDrawBorder(false);

    this->_musicVolumeTitle = ResourceManager::device()->getGUIEnvironment()->addButton(irr::core::rect<irr::s32>(10, 220, 520, 320), 0, -1, NULL);
    this->_musicVolumeTitle->setImage(ResourceManager::device()->getVideoDriver()->getTexture((ResourceManager::assets_rela + "settings/musicVolume_510x100.png").c_str()));
    this->_musicVolumeTitle->setUseAlphaChannel(true);
    this->_musicVolumeTitle->setDrawBorder(false);
    this->_musicVolumeTitle->setEnabled(false);

    this->_musicVolumeDOWN = ResourceManager::device()->getGUIEnvironment()->addButton(irr::core::rect<irr::s32>(530, 220, 630, 320), 0, -1, NULL);
    this->_musicVolumeDOWN->setPressedImage(minus);
    this->_musicVolumeDOWN->setImage(ResourceManager::device()->getVideoDriver()->getTexture((ResourceManager::assets_rela + "settings/minusLow_100x100.png").c_str()));
    this->_musicVolumeDOWN->setUseAlphaChannel(true);
    this->_musicVolumeDOWN->setDrawBorder(false);

    this->_musicVolume = ResourceManager::device()->getGUIEnvironment()->addButton(irr::core::rect<irr::s32>(640, 220, 1340, 320), 0, -1, NULL);
    this->_musicVolume->setImage(ResourceManager::device()->getVideoDriver()->getTexture((this->_volumePath[this->_musicVolumeIdx]).c_str()));
    this->_musicVolume->setUseAlphaChannel(true);
    this->_musicVolume->setDrawBorder(false);
    this->_musicVolume->setEnabled(false);

    this->_musicVolumeUP = ResourceManager::device()->getGUIEnvironment()->addButton(irr::core::rect<irr::s32>(1350, 220, 1450, 320), 0, -1, NULL);
    this->_musicVolumeUP->setPressedImage(plus);
    this->_musicVolumeUP->setImage(ResourceManager::device()->getVideoDriver()->getTexture((ResourceManager::assets_rela + "settings/plusLow_100x100.png").c_str()));
    this->_musicVolumeUP->setUseAlphaChannel(true);
    this->_musicVolumeUP->setDrawBorder(false);

    this->_player1Bomb = ResourceManager::device()->getGUIEnvironment()->addButton(irr::core::rect<irr::s32>(this->_hpad, 1080 - (this->_vpad + this->_bHeight) * 2, 480 - (this->_hpad / 2), 1080 - this->_vpad - this->_bHeight), 0, -1, NULL);
    this->_player1Bomb->setImage(ResourceManager::device()->getVideoDriver()->getTexture((ResourceManager::assets_rela + "settings/PlaceBomb_465x100.png").c_str()));
    this->_player1Bomb->setUseAlphaChannel(true);
    this->_player1Bomb->setDrawBorder(false);
    this->_player1Bomb->setEnabled(false);

    this->_player2Bomb = ResourceManager::device()->getGUIEnvironment()->addButton(irr::core::rect<irr::s32>(960 + this->_hpad, 1080 - (this->_vpad + this->_bHeight) * 2, 1440 - (this->_hpad / 2), 1080 - this->_vpad - this->_bHeight), 0, -1, NULL);
    this->_player2Bomb->setImage(ResourceManager::device()->getVideoDriver()->getTexture((ResourceManager::assets_rela + "settings/PlaceBomb_465x100.png").c_str()));
    this->_player2Bomb->setUseAlphaChannel(true);
    this->_player2Bomb->setDrawBorder(false);
    this->_player2Bomb->setEnabled(false);

    this->_player1Right = ResourceManager::device()->getGUIEnvironment()->addButton(irr::core::rect<irr::s32>(this->_hpad, 1080 - (this->_vpad + this->_bHeight) * 3 - this->_vpad, 480 - (this->_hpad / 2), 1080 - (this->_vpad + this->_bHeight) * 2 - this->_vpad), 0, -1, NULL);
    this->_player1Right->setImage(ResourceManager::device()->getVideoDriver()->getTexture((ResourceManager::assets_rela + "settings/MoveRight_465x100.png").c_str()));
    this->_player1Right->setUseAlphaChannel(true);
    this->_player1Right->setDrawBorder(false);
    this->_player1Right->setEnabled(false);

    this->_player2Right = ResourceManager::device()->getGUIEnvironment()->addButton(irr::core::rect<irr::s32>(960 + this->_hpad, 1080 - (this->_vpad + this->_bHeight) * 3 - this->_vpad, 1440 - (this->_hpad / 2), 1080 - (this->_vpad + this->_bHeight) * 2 - this->_vpad), 0, -1, NULL);
    this->_player2Right->setImage(ResourceManager::device()->getVideoDriver()->getTexture((ResourceManager::assets_rela + "settings/MoveRight_465x100.png").c_str()));
    this->_player2Right->setUseAlphaChannel(true);
    this->_player2Right->setDrawBorder(false);
    this->_player2Right->setEnabled(false);

    this->_player1Left = ResourceManager::device()->getGUIEnvironment()->addButton(irr::core::rect<irr::s32>(this->_hpad, 1080 - (this->_vpad + this->_bHeight) * 4 - this->_vpad * 2, 480 - (this->_hpad / 2), 1080 - (this->_vpad + this->_bHeight) * 3 - this->_vpad * 2), 0, -1, NULL);
    this->_player1Left->setImage(ResourceManager::device()->getVideoDriver()->getTexture((ResourceManager::assets_rela + "settings/MoveLeft_465x100.png").c_str()));
    this->_player1Left->setUseAlphaChannel(true);
    this->_player1Left->setDrawBorder(false);
    this->_player1Left->setEnabled(false);

    this->_player2Left = ResourceManager::device()->getGUIEnvironment()->addButton(irr::core::rect<irr::s32>(960 + this->_hpad, 1080 - (this->_vpad + this->_bHeight) * 4 - this->_vpad * 2, 1440 - (this->_hpad / 2), 1080 - (this->_vpad + this->_bHeight) * 3 - this->_vpad * 2), 0, -1, NULL);
    this->_player2Left->setImage(ResourceManager::device()->getVideoDriver()->getTexture((ResourceManager::assets_rela + "settings/MoveLeft_465x100.png").c_str()));
    this->_player2Left->setUseAlphaChannel(true);
    this->_player2Left->setDrawBorder(false);
    this->_player2Left->setEnabled(false);

    this->_player1Down = ResourceManager::device()->getGUIEnvironment()->addButton(irr::core::rect<irr::s32>(this->_hpad, 1080 - (this->_vpad + this->_bHeight) * 5 - this->_vpad * 3, 480 - (this->_hpad / 2), 1080 - (this->_vpad + this->_bHeight) * 4 - this->_vpad * 3), 0, -1, NULL);
    this->_player1Down->setImage(ResourceManager::device()->getVideoDriver()->getTexture((ResourceManager::assets_rela + "settings/MoveDown_465x100.png").c_str()));
    this->_player1Down->setUseAlphaChannel(true);
    this->_player1Down->setDrawBorder(false);
    this->_player1Down->setEnabled(false);

    this->_player2Down = ResourceManager::device()->getGUIEnvironment()->addButton(irr::core::rect<irr::s32>(960 + this->_hpad, 1080 - (this->_vpad + this->_bHeight) * 5 - this->_vpad * 3, 1440 - (this->_hpad / 2), 1080 - (this->_vpad + this->_bHeight) * 4 - this->_vpad * 3), 0, -1, NULL);
    this->_player2Down->setImage(ResourceManager::device()->getVideoDriver()->getTexture((ResourceManager::assets_rela + "settings/MoveDown_465x100.png").c_str()));
    this->_player2Down->setUseAlphaChannel(true);
    this->_player2Down->setDrawBorder(false);
    this->_player2Down->setEnabled(false);

    this->_player1Up = ResourceManager::device()->getGUIEnvironment()->addButton(irr::core::rect<irr::s32>(this->_hpad, 1080 - (this->_vpad + this->_bHeight) * 6 - this->_vpad * 4, 480 - (this->_hpad / 2), 1080 - (this->_vpad + this->_bHeight) * 5 - this->_vpad * 4), 0, -1, NULL);
    this->_player1Up->setImage(ResourceManager::device()->getVideoDriver()->getTexture((ResourceManager::assets_rela + "settings/MoveUp_465x100.png").c_str()));
    this->_player1Up->setUseAlphaChannel(true);
    this->_player1Up->setDrawBorder(false);
    this->_player1Up->setEnabled(false);

    this->_player2Up = ResourceManager::device()->getGUIEnvironment()->addButton(irr::core::rect<irr::s32>(960 + this->_hpad, 1080 - (this->_vpad + this->_bHeight) * 6 - this->_vpad * 4, 1440 - (this->_hpad / 2), 1080 - (this->_vpad + this->_bHeight) * 5 - this->_vpad * 4), 0, -1, NULL);
    this->_player2Up->setImage(ResourceManager::device()->getVideoDriver()->getTexture((ResourceManager::assets_rela + "settings/MoveUp_465x100.png").c_str()));
    this->_player2Up->setUseAlphaChannel(true);
    this->_player2Up->setDrawBorder(false);
    this->_player2Up->setEnabled(false);

    this->_player1Title = ResourceManager::device()->getGUIEnvironment()->addButton(irr::core::rect<irr::s32>(this->_hpad, 1080 - (this->_vpad + this->_bHeight) * 7.5 - this->_vpad * 6, 960 - this->_hpad, 1080 - (this->_vpad + this->_bHeight) * 6 - this->_vpad * 6), 0, -1, NULL);
    this->_player1Title->setImage(ResourceManager::device()->getVideoDriver()->getTexture((ResourceManager::assets_rela + "settings/Player1Title_940x135.png").c_str()));
    this->_player1Title->setUseAlphaChannel(true);
    this->_player1Title->setDrawBorder(false);
    this->_player1Title->setEnabled(false);

    this->_player2Title = ResourceManager::device()->getGUIEnvironment()->addButton(irr::core::rect<irr::s32>(960 + this->_hpad, 1080 - (this->_vpad + this->_bHeight) * 7.5 - this->_vpad * 6, 1920 - this->_hpad,  1080 - (this->_vpad + this->_bHeight) * 6 - this->_vpad * 6), 0, -1, NULL);
    this->_player2Title->setImage(ResourceManager::device()->getVideoDriver()->getTexture((ResourceManager::assets_rela + "settings/Player2Title_940x135.png").c_str()));
    this->_player2Title->setUseAlphaChannel(true);
    this->_player2Title->setDrawBorder(false);
    this->_player2Title->setEnabled(false);

    auto keyP1 = Settings::keyMapP1();
    auto keyP2 = Settings::keyMapP2();

    this->_player1BombKey = ResourceManager::device()->getGUIEnvironment()->addButton(irr::core::rect<irr::s32>(480 + (this->_hpad / 2), 1080 - (this->_vpad + this->_bHeight) * 2, 960 - this->_hpad, 1080 - this->_vpad - this->_bHeight), 0, -1, NULL);
    this->_player1BombKey->setImage(ResourceManager::device()->getVideoDriver()->getTexture((ResourceManager::assets_rela + "settings/Keyboard/KEY_" + std::to_string(keyP1[4]) + "_465x100.png").c_str()));
    this->_player1BombKey->setUseAlphaChannel(true);
    this->_player1BombKey->setDrawBorder(false);

    this->_player2BombKey = ResourceManager::device()->getGUIEnvironment()->addButton(irr::core::rect<irr::s32>(1440 + (this->_hpad / 2), 1080 - (this->_vpad + this->_bHeight) * 2, 1920 - this->_hpad, 1080 - (this->_vpad + this->_bHeight)), 0, -1, NULL);
    this->_player2BombKey->setImage(ResourceManager::device()->getVideoDriver()->getTexture((ResourceManager::assets_rela + "settings/Keyboard/KEY_" + std::to_string(keyP2[4]) + "_465x100.png").c_str()));
    this->_player2BombKey->setUseAlphaChannel(true);
    this->_player2BombKey->setDrawBorder(false);

    this->_player1RightKey = ResourceManager::device()->getGUIEnvironment()->addButton(irr::core::rect<irr::s32>(480 + (this->_hpad / 2), 1080 - (this->_vpad + this->_bHeight) * 3 - this->_vpad, 960 - this->_hpad, 1080 - (this->_vpad + this->_bHeight) * 2 - this->_vpad), 0, -1, NULL);
    this->_player1RightKey->setImage(ResourceManager::device()->getVideoDriver()->getTexture((ResourceManager::assets_rela + "settings/Keyboard/KEY_" + std::to_string(keyP1[1]) + "_465x100.png").c_str()));
    this->_player1RightKey->setUseAlphaChannel(true);
    this->_player1RightKey->setDrawBorder(false);

    this->_player2RightKey = ResourceManager::device()->getGUIEnvironment()->addButton(irr::core::rect<irr::s32>(1440 + (this->_hpad / 2), 1080 - (this->_vpad + this->_bHeight) * 3 - this->_vpad, 1920 - this->_hpad, 1080 - (this->_vpad + this->_bHeight) * 2 - this->_vpad), 0, -1, NULL);
    this->_player2RightKey->setImage(ResourceManager::device()->getVideoDriver()->getTexture((ResourceManager::assets_rela + "settings/Keyboard/KEY_" + std::to_string(keyP2[1]) + "_465x100.png").c_str()));
    this->_player2RightKey->setUseAlphaChannel(true);
    this->_player2RightKey->setDrawBorder(false);

    this->_player1LeftKey = ResourceManager::device()->getGUIEnvironment()->addButton(irr::core::rect<irr::s32>(480 + (this->_hpad / 2), 1080 - (this->_vpad + this->_bHeight) * 4 - this->_vpad * 2, 960 - this->_hpad, 1080 - (this->_vpad + this->_bHeight) * 3 - this->_vpad * 2), 0, -1, NULL);
    this->_player1LeftKey->setImage(ResourceManager::device()->getVideoDriver()->getTexture((ResourceManager::assets_rela + "settings/Keyboard/KEY_" + std::to_string(keyP1[3]) + "_465x100.png").c_str()));
    this->_player1LeftKey->setUseAlphaChannel(true);
    this->_player1LeftKey->setDrawBorder(false);

    this->_player2LeftKey = ResourceManager::device()->getGUIEnvironment()->addButton(irr::core::rect<irr::s32>(1440 + (this->_hpad / 2), 1080 - (this->_vpad + this->_bHeight) * 4 - this->_vpad * 2, 1920 - this->_hpad, 1080 - (this->_vpad + this->_bHeight) * 3 - this->_vpad * 2), 0, -1, NULL);
    this->_player2LeftKey->setImage(ResourceManager::device()->getVideoDriver()->getTexture((ResourceManager::assets_rela + "settings/Keyboard/KEY_" + std::to_string(keyP2[3]) + "_465x100.png").c_str()));
    this->_player2LeftKey->setUseAlphaChannel(true);
    this->_player2LeftKey->setDrawBorder(false);

    this->_player1DownKey = ResourceManager::device()->getGUIEnvironment()->addButton(irr::core::rect<irr::s32>(480 + (this->_hpad / 2), 1080 - (this->_vpad + this->_bHeight) * 5 - this->_vpad * 3, 960 - this->_hpad, 1080 - (this->_vpad + this->_bHeight) * 4 - this->_vpad * 3), 0, -1, NULL);
    this->_player1DownKey->setImage(ResourceManager::device()->getVideoDriver()->getTexture((ResourceManager::assets_rela + "settings/Keyboard/KEY_" + std::to_string(keyP1[2]) + "_465x100.png").c_str()));
    this->_player1DownKey->setUseAlphaChannel(true);
    this->_player1DownKey->setDrawBorder(false);

    this->_player2DownKey = ResourceManager::device()->getGUIEnvironment()->addButton(irr::core::rect<irr::s32>(1440 + (this->_hpad / 2), 1080 - (this->_vpad + this->_bHeight) * 5 - this->_vpad * 3, 1920 - this->_hpad, 1080 - (this->_vpad + this->_bHeight) * 4 - this->_vpad * 3), 0, -1, NULL);
    this->_player2DownKey->setImage(ResourceManager::device()->getVideoDriver()->getTexture((ResourceManager::assets_rela + "settings/Keyboard/KEY_" + std::to_string(keyP2[2]) + "_465x100.png").c_str()));
    this->_player2DownKey->setUseAlphaChannel(true);
    this->_player2DownKey->setDrawBorder(false);

    this->_player1UpKey = ResourceManager::device()->getGUIEnvironment()->addButton(irr::core::rect<irr::s32>(480 + (this->_hpad / 2), 1080 - (this->_vpad + this->_bHeight) * 6 - this->_vpad * 4, 960 - this->_hpad, 1080 - (this->_vpad + this->_bHeight) * 5 - this->_vpad * 4), 0, -1, NULL);
    this->_player1UpKey->setImage(ResourceManager::device()->getVideoDriver()->getTexture((ResourceManager::assets_rela + "settings/Keyboard/KEY_" + std::to_string(keyP1[0]) + "_465x100.png").c_str()));
    this->_player1UpKey->setUseAlphaChannel(true);
    this->_player1UpKey->setDrawBorder(false);

    this->_player2UpKey = ResourceManager::device()->getGUIEnvironment()->addButton(irr::core::rect<irr::s32>(1440 + (this->_hpad / 2), 1080 - (this->_vpad + this->_bHeight) * 6 - this->_vpad * 4, 1920 - this->_hpad, 1080 - (this->_vpad + this->_bHeight) * 5 - this->_vpad * 4), 0, -1, NULL);
    this->_player2UpKey->setImage(ResourceManager::device()->getVideoDriver()->getTexture((ResourceManager::assets_rela + "settings/Keyboard/KEY_" + std::to_string(keyP2[0]) + "_465x100.png").c_str()));
    this->_player2UpKey->setUseAlphaChannel(true);
    this->_player2UpKey->setDrawBorder(false);

    return true;
}

int
MenuSettingsPage::refresh(int &menuState) {
    //TODO GHOSTING
    auto &keyP1 = Settings::keyMapP1();
    auto &keyP2 = Settings::keyMapP2();
    auto firstController = ResourceManager::eventHandler().getJoystick(ResourceManager::getControllers()[0]);
    if ((isMouseOnBack() && ResourceManager::eventHandler().isMouseLeftClickPressed()) || ResourceManager::eventHandler().isKeyDown(irr::KEY_ESCAPE)
        || firstController.ButtonStates == 4) {
        this->unsetScene();
        menuState = MENUMAINPAGE;
        return 1;
    }
    if (this->_effectVolumeDOWN->isPressed() || firstController.Axis[0] < 0) {
        this->_effectVolumeIdx -= 1;
        if (this->_effectVolumeIdx < 0)
            this->_effectVolumeIdx = 0;
    }
    if (this->_musicVolumeDOWN->isPressed() || firstController.Axis[2] < 0) {
        this->_musicVolumeIdx -= 1;
        if (this->_musicVolumeIdx < 0)
            this->_musicVolumeIdx = 0;
    }
    if (this->_effectVolumeUP->isPressed() || firstController.Axis[0] > 0) {
        this->_effectVolumeIdx += 1;
        if (this->_effectVolumeIdx > 10)
            this->_effectVolumeIdx = 10;
    }
    if (this->_musicVolumeUP->isPressed() || firstController.Axis[2] > 0) {
        this->_musicVolumeIdx += 1;
        if (this->_musicVolumeIdx > 10)
            this->_musicVolumeIdx = 10;
    }
    if (this->_reset->isPressed() || firstController.ButtonStates == 4096) {
        this->_musicVolumeIdx = 10;
        this->_effectVolumeIdx = 10;
        keyP1[0] = irr::KEY_UP;
        keyP1[1] = irr::KEY_RIGHT;
        keyP1[2] = irr::KEY_DOWN;
        keyP1[3] = irr::KEY_LEFT;
        keyP1[4] = irr::KEY_END;
        keyP2[0] = irr::KEY_KEY_Z;
        keyP2[1] = irr::KEY_KEY_D;
        keyP2[2] = irr::KEY_KEY_S;
        keyP2[3] = irr::KEY_KEY_Q;
        keyP2[4] = irr::KEY_SPACE;
    } else if (this->_player1UpKey->isPressed() || this->_wfkP1Up) {
        if (!this->_wfkP1Up) {
            ResourceManager::eventHandler().resetLastKeyPressed();
            this->_wfkP1Up = true;
        }
        irr::EKEY_CODE  key = ResourceManager::eventHandler().getKeyPressed();
        bool            keyAvailable;
        if (key != irr::KEY_CANCEL) {
            if (key != irr::KEY_ESCAPE && key != irr::KEY_RETURN && (keyAvailable = this->_isKeyFree(1, 0, key))) {
                keyP1[0] = key;
            }
            if (key != irr::KEY_RETURN && (key == irr::KEY_ESCAPE || keyAvailable)) {
                    this->_wfkP1Up = false;
            }
        }
    } else if (this->_player1RightKey->isPressed() || this->_wfkP1Right) {
        if (!this->_wfkP1Right) {
            ResourceManager::eventHandler().resetLastKeyPressed();
            this->_wfkP1Right = true;
        }
        irr::EKEY_CODE  key = ResourceManager::eventHandler().getKeyPressed();
        bool            keyAvailable;
        if (key != irr::KEY_CANCEL) {
            if (key != irr::KEY_ESCAPE && key != irr::KEY_RETURN && (keyAvailable = this->_isKeyFree(1, 1, key))) {
                keyP1[1] = key;
            }
            if (key != irr::KEY_RETURN && (key == irr::KEY_ESCAPE || keyAvailable)) {
                this->_wfkP1Right = false;
            }
        }
    } else if (this->_player1DownKey->isPressed() || this->_wfkP1Down) {
        if (!this->_wfkP1Down) {
            ResourceManager::eventHandler().resetLastKeyPressed();
            this->_wfkP1Down = true;
        }
        irr::EKEY_CODE  key = ResourceManager::eventHandler().getKeyPressed();
        bool            keyAvailable;
        if (key != irr::KEY_CANCEL) {
            if (key != irr::KEY_ESCAPE && key != irr::KEY_RETURN && (keyAvailable = this->_isKeyFree(1, 2, key))) {
                keyP1[2] = key;
            }
            if (key != irr::KEY_RETURN && (key == irr::KEY_ESCAPE || keyAvailable)) {
                this->_wfkP1Down = false;
            }
        }
    } else if (this->_player1LeftKey->isPressed() || this->_wfkP1Left) {
        if (!this->_wfkP1Left) {
            ResourceManager::eventHandler().resetLastKeyPressed();
            this->_wfkP1Left = true;
        }
        irr::EKEY_CODE  key = ResourceManager::eventHandler().getKeyPressed();
        bool            keyAvailable;
        if (key != irr::KEY_CANCEL) {
            if (key != irr::KEY_ESCAPE && key != irr::KEY_RETURN && (keyAvailable = this->_isKeyFree(1, 3, key))) {
                keyP1[3] = key;
            }
            if (key != irr::KEY_RETURN && (key == irr::KEY_ESCAPE || keyAvailable)) {
                this->_wfkP1Left = false;
            }
        }
    } else if (this->_player1BombKey->isPressed() || this->_wfkP1Bomb) {
        if (!this->_wfkP1Bomb) {
            ResourceManager::eventHandler().resetLastKeyPressed();
            this->_wfkP1Bomb = true;
        }
        irr::EKEY_CODE  key = ResourceManager::eventHandler().getKeyPressed();
        bool            keyAvailable;
        if (key != irr::KEY_CANCEL) {
            if (key != irr::KEY_ESCAPE && key != irr::KEY_RETURN && (keyAvailable = this->_isKeyFree(1, 4, key))) {
                keyP1[4] = key;
            }
            if (key != irr::KEY_RETURN && (key == irr::KEY_ESCAPE || keyAvailable)) {
                this->_wfkP1Bomb = false;
            }
        }
    } else if (this->_player2UpKey->isPressed() || this->_wfkP2Up) {
        if (!this->_wfkP2Up) {
            ResourceManager::eventHandler().resetLastKeyPressed();
            this->_wfkP2Up = true;
        }
        irr::EKEY_CODE  key = ResourceManager::eventHandler().getKeyPressed();
        bool            keyAvailable;
        if (key != irr::KEY_CANCEL) {
            if (key != irr::KEY_ESCAPE && key != irr::KEY_RETURN && (keyAvailable = this->_isKeyFree(2, 0, key))) {
                keyP2[0] = key;
            }
            if (key != irr::KEY_RETURN && (key == irr::KEY_ESCAPE || keyAvailable)) {
                this->_wfkP2Up = false;
            }
        }
    } else if (this->_player2RightKey->isPressed() || this->_wfkP2Right) {
        if (!this->_wfkP2Right) {
            ResourceManager::eventHandler().resetLastKeyPressed();
            this->_wfkP2Right = true;
        }
        irr::EKEY_CODE  key = ResourceManager::eventHandler().getKeyPressed();
        bool            keyAvailable;
        if (key != irr::KEY_CANCEL) {
            if (key != irr::KEY_ESCAPE && key != irr::KEY_RETURN && (keyAvailable = this->_isKeyFree(2, 1, key))) {
                keyP2[1] = key;
            }
            if (key != irr::KEY_RETURN && (key == irr::KEY_ESCAPE || keyAvailable)) {
                this->_wfkP2Right = false;
            }
        }
    } else if (this->_player2DownKey->isPressed() || this->_wfkP2Down) {
        if (!this->_wfkP2Down) {
            ResourceManager::eventHandler().resetLastKeyPressed();
            this->_wfkP2Down = true;
        }
        irr::EKEY_CODE  key = ResourceManager::eventHandler().getKeyPressed();
        bool            keyAvailable;
        if (key != irr::KEY_CANCEL) {
            if (key != irr::KEY_ESCAPE && key != irr::KEY_RETURN && (keyAvailable = this->_isKeyFree(2, 2, key))) {
                keyP2[2] = key;
            }
            if (key != irr::KEY_RETURN && (key == irr::KEY_ESCAPE || keyAvailable)) {
                this->_wfkP2Down = false;
            }
        }
    } else if (this->_player2LeftKey->isPressed() || this->_wfkP2Left) {
        if (!this->_wfkP2Left) {
            ResourceManager::eventHandler().resetLastKeyPressed();
            this->_wfkP2Left = true;
        }
        irr::EKEY_CODE  key = ResourceManager::eventHandler().getKeyPressed();
        bool            keyAvailable;
        if (key != irr::KEY_CANCEL) {
            if (key != irr::KEY_ESCAPE && key != irr::KEY_RETURN && (keyAvailable = this->_isKeyFree(2, 3, key))) {
                keyP2[3] = key;
            }
            if (key != irr::KEY_RETURN && (key == irr::KEY_ESCAPE || keyAvailable)) {
                this->_wfkP2Left = false;
            }
        }
    } else if (this->_player2BombKey->isPressed() || this->_wfkP2Bomb) {
        if (!this->_wfkP2Bomb) {
            ResourceManager::eventHandler().resetLastKeyPressed();
            this->_wfkP2Bomb = true;
        }
        irr::EKEY_CODE  key = ResourceManager::eventHandler().getKeyPressed();
        bool            keyAvailable;
        if (key != irr::KEY_CANCEL) {
            if (key != irr::KEY_ESCAPE && key != irr::KEY_RETURN && (keyAvailable = this->_isKeyFree(2, 4, key))) {
                keyP2[4] = key;
            }
            if (key != irr::KEY_RETURN && (key == irr::KEY_ESCAPE || keyAvailable)) {
                this->_wfkP2Bomb = false;
            }
        }
    }

    this->_player1BombKey->setImage(ResourceManager::device()->getVideoDriver()->getTexture((ResourceManager::assets_rela + "settings/Keyboard/KEY_" + std::to_string(keyP1[4]) + "_465x100.png").c_str()));
    this->_player1BombKey->setPressedImage(ResourceManager::device()->getVideoDriver()->getTexture((ResourceManager::assets_rela + "settings/Keyboard/KEY_" + std::to_string(keyP1[4]) + "_465x100.png").c_str()));

    this->_player2BombKey->setImage(ResourceManager::device()->getVideoDriver()->getTexture((ResourceManager::assets_rela + "settings/Keyboard/KEY_" + std::to_string(keyP2[4]) + "_465x100.png").c_str()));
    this->_player2BombKey->setPressedImage(ResourceManager::device()->getVideoDriver()->getTexture((ResourceManager::assets_rela + "settings/Keyboard/KEY_" + std::to_string(keyP2[4]) + "_465x100.png").c_str()));

    this->_player1RightKey->setImage(ResourceManager::device()->getVideoDriver()->getTexture((ResourceManager::assets_rela + "settings/Keyboard/KEY_" + std::to_string(keyP1[1]) + "_465x100.png").c_str()));
    this->_player1RightKey->setPressedImage(ResourceManager::device()->getVideoDriver()->getTexture((ResourceManager::assets_rela + "settings/Keyboard/KEY_" + std::to_string(keyP1[1]) + "_465x100.png").c_str()));

    this->_player2RightKey->setImage(ResourceManager::device()->getVideoDriver()->getTexture((ResourceManager::assets_rela + "settings/Keyboard/KEY_" + std::to_string(keyP2[1]) + "_465x100.png").c_str()));
    this->_player2RightKey->setPressedImage(ResourceManager::device()->getVideoDriver()->getTexture((ResourceManager::assets_rela + "settings/Keyboard/KEY_" + std::to_string(keyP2[1]) + "_465x100.png").c_str()));

    this->_player1LeftKey->setImage(ResourceManager::device()->getVideoDriver()->getTexture((ResourceManager::assets_rela + "settings/Keyboard/KEY_" + std::to_string(keyP1[3]) + "_465x100.png").c_str()));
    this->_player1LeftKey->setPressedImage(ResourceManager::device()->getVideoDriver()->getTexture((ResourceManager::assets_rela + "settings/Keyboard/KEY_" + std::to_string(keyP1[3]) + "_465x100.png").c_str()));

    this->_player2LeftKey->setImage(ResourceManager::device()->getVideoDriver()->getTexture((ResourceManager::assets_rela + "settings/Keyboard/KEY_" + std::to_string(keyP2[3]) + "_465x100.png").c_str()));
    this->_player2LeftKey->setPressedImage(ResourceManager::device()->getVideoDriver()->getTexture((ResourceManager::assets_rela + "settings/Keyboard/KEY_" + std::to_string(keyP2[3]) + "_465x100.png").c_str()));

    this->_player1DownKey->setImage(ResourceManager::device()->getVideoDriver()->getTexture((ResourceManager::assets_rela + "settings/Keyboard/KEY_" + std::to_string(keyP1[2]) + "_465x100.png").c_str()));
    this->_player1DownKey->setPressedImage(ResourceManager::device()->getVideoDriver()->getTexture((ResourceManager::assets_rela + "settings/Keyboard/KEY_" + std::to_string(keyP1[2]) + "_465x100.png").c_str()));

    this->_player2DownKey->setImage(ResourceManager::device()->getVideoDriver()->getTexture((ResourceManager::assets_rela + "settings/Keyboard/KEY_" + std::to_string(keyP2[2]) + "_465x100.png").c_str()));
    this->_player2DownKey->setPressedImage(ResourceManager::device()->getVideoDriver()->getTexture((ResourceManager::assets_rela + "settings/Keyboard/KEY_" + std::to_string(keyP2[2]) + "_465x100.png").c_str()));

    this->_player1UpKey->setImage(ResourceManager::device()->getVideoDriver()->getTexture((ResourceManager::assets_rela + "settings/Keyboard/KEY_" + std::to_string(keyP1[0]) + "_465x100.png").c_str()));
    this->_player1UpKey->setPressedImage(ResourceManager::device()->getVideoDriver()->getTexture((ResourceManager::assets_rela + "settings/Keyboard/KEY_" + std::to_string(keyP1[0]) + "_465x100.png").c_str()));

    this->_player2UpKey->setImage(ResourceManager::device()->getVideoDriver()->getTexture((ResourceManager::assets_rela + "settings/Keyboard/KEY_" + std::to_string(keyP2[0]) + "_465x100.png").c_str()));
    this->_player2UpKey->setPressedImage(ResourceManager::device()->getVideoDriver()->getTexture((ResourceManager::assets_rela + "settings/Keyboard/KEY_" + std::to_string(keyP2[0]) + "_465x100.png").c_str()));

    this->_effectVolume->setImage(ResourceManager::device()->getVideoDriver()->getTexture((this->_volumePath[this->_effectVolumeIdx]).c_str()));
    this->_musicVolume->setImage(ResourceManager::device()->getVideoDriver()->getTexture((this->_volumePath[this->_musicVolumeIdx]).c_str()));
    ResourceManager::guiEnvironment()->drawAll();
    ResourceManager::sceneManager()->drawAll();

    if (this->_wfkP1Bomb || this->_wfkP1Down || this->_wfkP1Left || this->_wfkP1Right || this->_wfkP1Up
        || this->_wfkP2Bomb || this->_wfkP2Down || this->_wfkP2Left || this->_wfkP2Right || this->_wfkP2Up) {
        ResourceManager::videoDriver()->draw2DImage(this->_bind, irr::core::position2d<irr::s32>(1920 / 2 - 320, 1080 / 2 - 90),
                                                    irr::core::rect<irr::s32>(0, 0, 640, 180), 0,
                                                    irr::video::SColor(255, 255, 255, 255), true);
    }
    ResourceManager::videoDriver()->endScene();

    Settings::music_volume() = this->_musicVolumeIdx;
    Settings::sound_volume() = this->_effectVolumeIdx;

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

bool
MenuSettingsPage::_isKeyFree(uint32_t const player, uint32_t const index, irr::EKEY_CODE const key) const {
    auto &keyP1 = Settings::keyMapP1();
    auto &keyP2 = Settings::keyMapP2();

    for (size_t i = 0; i < keyP1.size(); ++i) {
        if (player != 1 || index != i) {
            if (keyP1[i] == key) {
                return false;
            }
        }
    }
    for (size_t j = 0; j < keyP2.size(); ++j) {
        if (player != 2 || index != j) {
            if (keyP2[j] == key) {
                return false;
            }
        }
    }
    return true;
}
