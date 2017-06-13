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
    this->_volumePath.push_back("./assets/settings/Volume0_700x100.png");
    this->_volumePath.push_back("./assets/settings/Volume10_700x100.png");
    this->_volumePath.push_back("./assets/settings/Volume20_700x100.png");
    this->_volumePath.push_back("./assets/settings/Volume30_700x100.png");
    this->_volumePath.push_back("./assets/settings/Volume40_700x100.png");
    this->_volumePath.push_back("./assets/settings/Volume50_700x100.png");
    this->_volumePath.push_back("./assets/settings/Volume60_700x100.png");
    this->_volumePath.push_back("./assets/settings/Volume70_700x100.png");
    this->_volumePath.push_back("./assets/settings/Volume80_700x100.png");
    this->_volumePath.push_back("./assets/settings/Volume90_700x100.png");
    this->_volumePath.push_back("./assets/settings/Volume100_700x100.png");
}

MenuSettingsPage::~MenuSettingsPage() {

}

bool
MenuSettingsPage::setScene() {
    this->unsetScene();
    irr::video::ITexture *plus = ResourceManager::videoDriver()->getTexture("./assets/settings/plusBig_100x100.png");
    irr::video::ITexture *minus = ResourceManager::videoDriver()->getTexture("./assets/settings/minusBig_100x100.png");

    this->_bg = ResourceManager::device()->getGUIEnvironment()->addButton( irr::core::rect<irr::s32>(0, 0, 1920, 1080), 0, -1, NULL);
    this->_bg->setImage(ResourceManager::device()->getVideoDriver()->getTexture("./assets/BG.png"));
    this->_bg->setUseAlphaChannel(true);
    this->_bg->setDrawBorder(false);
    this->_bg->setEnabled(false);

    this->_back = ResourceManager::device()->getGUIEnvironment()->addButton(irr::core::rect<irr::s32>(10, 10, 250 + 10, 60 + 10), 0, -1, NULL);
    this->_back->setImage(ResourceManager::device()->getVideoDriver()->getTexture("./assets/Fonts/Back_250x60.png"));
    this->_back->setUseAlphaChannel(true);
    this->_back->setDrawBorder(false);

    this->_reset = ResourceManager::device()->getGUIEnvironment()->addButton(irr::core::rect<irr::s32>(1920 - (250 + 10), 0, 1920 - this->_hpad, this->_bHeight), 0, -1, NULL);
    this->_reset->setImage(ResourceManager::device()->getVideoDriver()->getTexture("./assets/settings/Reset_250x60.png"));
    this->_reset->setUseAlphaChannel(true);
    this->_reset->setDrawBorder(false);

    this->_effectVolumeTitle = ResourceManager::device()->getGUIEnvironment()->addButton(irr::core::rect<irr::s32>(10, 100, 520, 200), 0, -1, NULL);
    this->_effectVolumeTitle->setImage(ResourceManager::device()->getVideoDriver()->getTexture("./assets/settings/effectVolume_510x100.png"));
    this->_effectVolumeTitle->setUseAlphaChannel(true);
    this->_effectVolumeTitle->setDrawBorder(false);
    this->_effectVolumeTitle->setEnabled(false);

    this->_effectVolumeDOWN = ResourceManager::device()->getGUIEnvironment()->addButton(irr::core::rect<irr::s32>(530, 100, 630, 200), 0, -1, NULL);
    this->_effectVolumeDOWN->setPressedImage(minus);
    this->_effectVolumeDOWN->setImage(ResourceManager::device()->getVideoDriver()->getTexture("./assets/settings/minusLow_100x100.png"));
    this->_effectVolumeDOWN->setUseAlphaChannel(true);
    this->_effectVolumeDOWN->setDrawBorder(false);

    this->_effectVolume = ResourceManager::device()->getGUIEnvironment()->addButton(irr::core::rect<irr::s32>(640, 100, 1340, 200), 0, -1, NULL);
    this->_effectVolume->setImage(ResourceManager::device()->getVideoDriver()->getTexture((this->_volumePath[this->_effectVolumeIdx]).c_str()));
    this->_effectVolume->setUseAlphaChannel(true);
    this->_effectVolume->setDrawBorder(false);
    this->_effectVolume->setEnabled(false);

    this->_effectVolumeUP = ResourceManager::device()->getGUIEnvironment()->addButton(irr::core::rect<irr::s32>(1350, 100, 1450, 200), 0, -1, NULL);
    this->_effectVolumeUP->setPressedImage(plus);
    this->_effectVolumeUP->setImage(ResourceManager::device()->getVideoDriver()->getTexture("./assets/settings/plusLow_100x100.png"));
    this->_effectVolumeUP->setUseAlphaChannel(true);
    this->_effectVolumeUP->setDrawBorder(false);

    this->_musicVolumeTitle = ResourceManager::device()->getGUIEnvironment()->addButton(irr::core::rect<irr::s32>(10, 220, 520, 320), 0, -1, NULL);
    this->_musicVolumeTitle->setImage(ResourceManager::device()->getVideoDriver()->getTexture("./assets/settings/musicVolume_510x100.png"));
    this->_musicVolumeTitle->setUseAlphaChannel(true);
    this->_musicVolumeTitle->setDrawBorder(false);
    this->_musicVolumeTitle->setEnabled(false);

    this->_musicVolumeDOWN = ResourceManager::device()->getGUIEnvironment()->addButton(irr::core::rect<irr::s32>(530, 220, 630, 320), 0, -1, NULL);
    this->_musicVolumeDOWN->setPressedImage(minus);
    this->_musicVolumeDOWN->setImage(ResourceManager::device()->getVideoDriver()->getTexture("./assets/settings/minusLow_100x100.png"));
    this->_musicVolumeDOWN->setUseAlphaChannel(true);
    this->_musicVolumeDOWN->setDrawBorder(false);

    this->_musicVolume = ResourceManager::device()->getGUIEnvironment()->addButton(irr::core::rect<irr::s32>(640, 220, 1340, 320), 0, -1, NULL);
    this->_musicVolume->setImage(ResourceManager::device()->getVideoDriver()->getTexture((this->_volumePath[this->_musicVolumeIdx]).c_str()));
    this->_musicVolume->setUseAlphaChannel(true);
    this->_musicVolume->setDrawBorder(false);
    this->_musicVolume->setEnabled(false);

    this->_musicVolumeUP = ResourceManager::device()->getGUIEnvironment()->addButton(irr::core::rect<irr::s32>(1350, 220, 1450, 320), 0, -1, NULL);
    this->_musicVolumeUP->setPressedImage(plus);
    this->_musicVolumeUP->setImage(ResourceManager::device()->getVideoDriver()->getTexture("./assets/settings/plusLow_100x100.png"));
    this->_musicVolumeUP->setUseAlphaChannel(true);
    this->_musicVolumeUP->setDrawBorder(false);

    this->_player1Bomb = ResourceManager::device()->getGUIEnvironment()->addButton(irr::core::rect<irr::s32>(this->_hpad, 1080 - (this->_vpad + this->_bHeight) * 2, 480 - (this->_hpad / 2), 1080 - this->_vpad - this->_bHeight), 0, -1, NULL);
    this->_player1Bomb->setImage(ResourceManager::device()->getVideoDriver()->getTexture("./assets/settings/PlaceBomb_465x100.png"));
    this->_player1Bomb->setUseAlphaChannel(true);
    this->_player1Bomb->setDrawBorder(false);
    this->_player1Bomb->setEnabled(false);

    this->_player2Bomb = ResourceManager::device()->getGUIEnvironment()->addButton(irr::core::rect<irr::s32>(960 + this->_hpad, 1080 - (this->_vpad + this->_bHeight) * 2, 1440 - (this->_hpad / 2), 1080 - this->_vpad - this->_bHeight), 0, -1, NULL);
    this->_player2Bomb->setImage(ResourceManager::device()->getVideoDriver()->getTexture("./assets/settings/PlaceBomb_465x100.png"));
    this->_player2Bomb->setUseAlphaChannel(true);
    this->_player2Bomb->setDrawBorder(false);
    this->_player2Bomb->setEnabled(false);

    this->_player1Right = ResourceManager::device()->getGUIEnvironment()->addButton(irr::core::rect<irr::s32>(this->_hpad, 1080 - (this->_vpad + this->_bHeight) * 3 - this->_vpad, 480 - (this->_hpad / 2), 1080 - (this->_vpad + this->_bHeight) * 2 - this->_vpad), 0, -1, NULL);
    this->_player1Right->setImage(ResourceManager::device()->getVideoDriver()->getTexture("./assets/settings/MoveRight_465x100.png"));
    this->_player1Right->setUseAlphaChannel(true);
    this->_player1Right->setDrawBorder(false);
    this->_player1Right->setEnabled(false);

    this->_player2Right = ResourceManager::device()->getGUIEnvironment()->addButton(irr::core::rect<irr::s32>(960 + this->_hpad, 1080 - (this->_vpad + this->_bHeight) * 3 - this->_vpad, 1440 - (this->_hpad / 2), 1080 - (this->_vpad + this->_bHeight) * 2 - this->_vpad), 0, -1, NULL);
    this->_player2Right->setImage(ResourceManager::device()->getVideoDriver()->getTexture("./assets/settings/MoveRight_465x100.png"));
    this->_player2Right->setUseAlphaChannel(true);
    this->_player2Right->setDrawBorder(false);
    this->_player2Right->setEnabled(false);

    this->_player1Left = ResourceManager::device()->getGUIEnvironment()->addButton(irr::core::rect<irr::s32>(this->_hpad, 1080 - (this->_vpad + this->_bHeight) * 4 - this->_vpad * 2, 480 - (this->_hpad / 2), 1080 - (this->_vpad + this->_bHeight) * 3 - this->_vpad * 2), 0, -1, NULL);
    this->_player1Left->setImage(ResourceManager::device()->getVideoDriver()->getTexture("./assets/settings/MoveLeft_465x100.png"));
    this->_player1Left->setUseAlphaChannel(true);
    this->_player1Left->setDrawBorder(false);
    this->_player1Left->setEnabled(false);

    this->_player2Left = ResourceManager::device()->getGUIEnvironment()->addButton(irr::core::rect<irr::s32>(960 + this->_hpad, 1080 - (this->_vpad + this->_bHeight) * 4 - this->_vpad * 2, 1440 - (this->_hpad / 2), 1080 - (this->_vpad + this->_bHeight) * 3 - this->_vpad * 2), 0, -1, NULL);
    this->_player2Left->setImage(ResourceManager::device()->getVideoDriver()->getTexture("./assets/settings/MoveLeft_465x100.png"));
    this->_player2Left->setUseAlphaChannel(true);
    this->_player2Left->setDrawBorder(false);
    this->_player2Left->setEnabled(false);

    this->_player1Down = ResourceManager::device()->getGUIEnvironment()->addButton(irr::core::rect<irr::s32>(this->_hpad, 1080 - (this->_vpad + this->_bHeight) * 5 - this->_vpad * 3, 480 - (this->_hpad / 2), 1080 - (this->_vpad + this->_bHeight) * 4 - this->_vpad * 3), 0, -1, NULL);
    this->_player1Down->setImage(ResourceManager::device()->getVideoDriver()->getTexture("./assets/settings/MoveDown_465x100.png"));
    this->_player1Down->setUseAlphaChannel(true);
    this->_player1Down->setDrawBorder(false);
    this->_player1Down->setEnabled(false);

    this->_player2Down = ResourceManager::device()->getGUIEnvironment()->addButton(irr::core::rect<irr::s32>(960 + this->_hpad, 1080 - (this->_vpad + this->_bHeight) * 5 - this->_vpad * 3, 1440 - (this->_hpad / 2), 1080 - (this->_vpad + this->_bHeight) * 4 - this->_vpad * 3), 0, -1, NULL);
    this->_player2Down->setImage(ResourceManager::device()->getVideoDriver()->getTexture("./assets/settings/MoveDown_465x100.png"));
    this->_player2Down->setUseAlphaChannel(true);
    this->_player2Down->setDrawBorder(false);
    this->_player2Down->setEnabled(false);

    this->_player1Up = ResourceManager::device()->getGUIEnvironment()->addButton(irr::core::rect<irr::s32>(this->_hpad, 1080 - (this->_vpad + this->_bHeight) * 6 - this->_vpad * 4, 480 - (this->_hpad / 2), 1080 - (this->_vpad + this->_bHeight) * 5 - this->_vpad * 4), 0, -1, NULL);
    this->_player1Up->setImage(ResourceManager::device()->getVideoDriver()->getTexture("./assets/settings/MoveUp_465x100.png"));
    this->_player1Up->setUseAlphaChannel(true);
    this->_player1Up->setDrawBorder(false);
    this->_player1Up->setEnabled(false);

    this->_player2Up = ResourceManager::device()->getGUIEnvironment()->addButton(irr::core::rect<irr::s32>(960 + this->_hpad, 1080 - (this->_vpad + this->_bHeight) * 6 - this->_vpad * 4, 1440 - (this->_hpad / 2), 1080 - (this->_vpad + this->_bHeight) * 5 - this->_vpad * 4), 0, -1, NULL);
    this->_player2Up->setImage(ResourceManager::device()->getVideoDriver()->getTexture("./assets/settings/MoveUp_465x100.png"));
    this->_player2Up->setUseAlphaChannel(true);
    this->_player2Up->setDrawBorder(false);
    this->_player2Up->setEnabled(false);

    this->_player1Title = ResourceManager::device()->getGUIEnvironment()->addButton(irr::core::rect<irr::s32>(this->_hpad, 1080 - (this->_vpad + this->_bHeight) * 7.5 - this->_vpad * 6, 960 - this->_hpad, 1080 - (this->_vpad + this->_bHeight) * 6 - this->_vpad * 6), 0, -1, NULL);
    this->_player1Title->setImage(ResourceManager::device()->getVideoDriver()->getTexture("./assets/settings/Player1Title_940x135.png"));
    this->_player1Title->setUseAlphaChannel(true);
    this->_player1Title->setDrawBorder(false);
    this->_player1Title->setEnabled(false);

    this->_player2Title = ResourceManager::device()->getGUIEnvironment()->addButton(irr::core::rect<irr::s32>(960 + this->_hpad, 1080 - (this->_vpad + this->_bHeight) * 7.5 - this->_vpad * 6, 1920 - this->_hpad,  1080 - (this->_vpad + this->_bHeight) * 6 - this->_vpad * 6), 0, -1, NULL);
    this->_player2Title->setImage(ResourceManager::device()->getVideoDriver()->getTexture("./assets/settings/Player2Title_940x135.png"));
    this->_player2Title->setUseAlphaChannel(true);
    this->_player2Title->setDrawBorder(false);
    this->_player2Title->setEnabled(false);
    return true;
}

int
MenuSettingsPage::refresh(int &menuState) {
    //TODO GHOSTING
    auto KeyP1 = Settings::keyMapP1();
    auto KeyP2 = Settings::keyMapP2();
    if ((isMouseOnBack() && ResourceManager::eventHandler().isMouseLeftClickPressed()) || ResourceManager::eventHandler().isKeyDown(irr::KEY_ESCAPE)) {
        this->unsetScene();
        menuState = MENUMAINPAGE;
        return 1;
    } else if (this->_effectVolumeDOWN->isPressed()) {
        this->_effectVolumeIdx -= 1;
            if (this->_effectVolumeIdx < 0)
                this->_effectVolumeIdx = 0;
    } else if (this->_musicVolumeDOWN->isPressed()) {
            this->_musicVolumeIdx -= 1;
            if (this->_musicVolumeIdx < 0)
                this->_musicVolumeIdx = 0;
    } else if (this->_effectVolumeUP->isPressed()) {
            this->_effectVolumeIdx += 1;
            if (this->_effectVolumeIdx > 10)
                this->_effectVolumeIdx = 10;
    } else if (this->_musicVolumeUP->isPressed()) {
            this->_musicVolumeIdx += 1;
            if (this->_musicVolumeIdx > 10)
                this->_musicVolumeIdx = 10;
    } else if (this->_reset->isPressed()) {
        this->_musicVolumeIdx = 10;
        this->_effectVolumeIdx = 10;
        KeyP1[0] = irr::KEY_UP;
        KeyP1[1] = irr::KEY_RIGHT;
        KeyP1[2] = irr::KEY_DOWN;
        KeyP1[3] = irr::KEY_LEFT;
        KeyP1[4] = irr::KEY_END;
        KeyP2[0] = irr::KEY_KEY_Z;
        KeyP2[1] = irr::KEY_KEY_D;
        KeyP2[2] = irr::KEY_KEY_S;
        KeyP2[3] = irr::KEY_KEY_Q;
        KeyP2[4] = irr::KEY_SPACE;
    }

    this->_player1BombKey = ResourceManager::device()->getGUIEnvironment()->addButton(irr::core::rect<irr::s32>(480 + (this->_hpad / 2), 1080 - (this->_vpad + this->_bHeight) * 2, 960 - this->_hpad, 1080 - this->_vpad - this->_bHeight), 0, -1, NULL);
    this->_player1BombKey->setImage(ResourceManager::device()->getVideoDriver()->getTexture(("./assets/settings/Keyboard/KEY_" + std::to_string(KeyP1[4]) + "_465x100.png").c_str()));
    this->_player1BombKey->setUseAlphaChannel(true);
    this->_player1BombKey->setDrawBorder(false);

    this->_player2BombKey = ResourceManager::device()->getGUIEnvironment()->addButton(irr::core::rect<irr::s32>(1440 + (this->_hpad / 2), 1080 - (this->_vpad + this->_bHeight) * 2, 1920 - this->_hpad, 1080 - (this->_vpad + this->_bHeight)), 0, -1, NULL);
    this->_player2BombKey->setImage(ResourceManager::device()->getVideoDriver()->getTexture(("./assets/settings/Keyboard/KEY_" + std::to_string(KeyP2[4]) + "_465x100.png").c_str()));
    this->_player2BombKey->setUseAlphaChannel(true);
    this->_player2BombKey->setDrawBorder(false);

    this->_player1RightKey = ResourceManager::device()->getGUIEnvironment()->addButton(irr::core::rect<irr::s32>(480 + (this->_hpad / 2), 1080 - (this->_vpad + this->_bHeight) * 3 - this->_vpad, 960 - this->_hpad, 1080 - (this->_vpad + this->_bHeight) * 2 - this->_vpad), 0, -1, NULL);
    this->_player1RightKey->setImage(ResourceManager::device()->getVideoDriver()->getTexture(("./assets/settings/Keyboard/KEY_" + std::to_string(KeyP1[1]) + "_465x100.png").c_str()));
    this->_player1RightKey->setUseAlphaChannel(true);
    this->_player1RightKey->setDrawBorder(false);

    this->_player2RightKey = ResourceManager::device()->getGUIEnvironment()->addButton(irr::core::rect<irr::s32>(1440 + (this->_hpad / 2), 1080 - (this->_vpad + this->_bHeight) * 3 - this->_vpad, 1920 - this->_hpad, 1080 - (this->_vpad + this->_bHeight) * 2 - this->_vpad), 0, -1, NULL);
    this->_player2RightKey->setImage(ResourceManager::device()->getVideoDriver()->getTexture(("./assets/settings/Keyboard/KEY_" + std::to_string(KeyP2[1]) + "_465x100.png").c_str()));
    this->_player2RightKey->setUseAlphaChannel(true);
    this->_player2RightKey->setDrawBorder(false);

    this->_player1LeftKey = ResourceManager::device()->getGUIEnvironment()->addButton(irr::core::rect<irr::s32>(480 + (this->_hpad / 2), 1080 - (this->_vpad + this->_bHeight) * 4 - this->_vpad * 2, 960 - this->_hpad, 1080 - (this->_vpad + this->_bHeight) * 3 - this->_vpad * 2), 0, -1, NULL);
    this->_player1LeftKey->setImage(ResourceManager::device()->getVideoDriver()->getTexture(("./assets/settings/Keyboard/KEY_" + std::to_string(KeyP1[3]) + "_465x100.png").c_str()));
    this->_player1LeftKey->setUseAlphaChannel(true);
    this->_player1LeftKey->setDrawBorder(false);

    this->_player2LeftKey = ResourceManager::device()->getGUIEnvironment()->addButton(irr::core::rect<irr::s32>(1440 + (this->_hpad / 2), 1080 - (this->_vpad + this->_bHeight) * 4 - this->_vpad * 2, 1920 - this->_hpad, 1080 - (this->_vpad + this->_bHeight) * 3 - this->_vpad * 2), 0, -1, NULL);
    this->_player2LeftKey->setImage(ResourceManager::device()->getVideoDriver()->getTexture(("./assets/settings/Keyboard/KEY_" + std::to_string(KeyP2[3]) + "_465x100.png").c_str()));
    this->_player2LeftKey->setUseAlphaChannel(true);
    this->_player2LeftKey->setDrawBorder(false);

    this->_player1DownKey = ResourceManager::device()->getGUIEnvironment()->addButton(irr::core::rect<irr::s32>(480 + (this->_hpad / 2), 1080 - (this->_vpad + this->_bHeight) * 5 - this->_vpad * 3, 960 - this->_hpad, 1080 - (this->_vpad + this->_bHeight) * 4 - this->_vpad * 3), 0, -1, NULL);
    this->_player1DownKey->setImage(ResourceManager::device()->getVideoDriver()->getTexture(("./assets/settings/Keyboard/KEY_" + std::to_string(KeyP1[2]) + "_465x100.png").c_str()));
    this->_player1DownKey->setUseAlphaChannel(true);
    this->_player1DownKey->setDrawBorder(false);

    this->_player2DownKey = ResourceManager::device()->getGUIEnvironment()->addButton(irr::core::rect<irr::s32>(1440 + (this->_hpad / 2), 1080 - (this->_vpad + this->_bHeight) * 5 - this->_vpad * 3, 1920 - this->_hpad, 1080 - (this->_vpad + this->_bHeight) * 4 - this->_vpad * 3), 0, -1, NULL);
    this->_player2DownKey->setImage(ResourceManager::device()->getVideoDriver()->getTexture(("./assets/settings/Keyboard/KEY_" + std::to_string(KeyP2[2]) + "_465x100.png").c_str()));
    this->_player2DownKey->setUseAlphaChannel(true);
    this->_player2DownKey->setDrawBorder(false);

    this->_player1UpKey = ResourceManager::device()->getGUIEnvironment()->addButton(irr::core::rect<irr::s32>(480 + (this->_hpad / 2), 1080 - (this->_vpad + this->_bHeight) * 6 - this->_vpad * 4, 960 - this->_hpad, 1080 - (this->_vpad + this->_bHeight) * 5 - this->_vpad * 4), 0, -1, NULL);
    this->_player1UpKey->setImage(ResourceManager::device()->getVideoDriver()->getTexture(("./assets/settings/Keyboard/KEY_" + std::to_string(KeyP1[0]) + "_465x100.png").c_str()));
    this->_player1UpKey->setUseAlphaChannel(true);
    this->_player1UpKey->setDrawBorder(false);

    this->_player2UpKey = ResourceManager::device()->getGUIEnvironment()->addButton(irr::core::rect<irr::s32>(1440 + (this->_hpad / 2), 1080 - (this->_vpad + this->_bHeight) * 6 - this->_vpad * 4, 1920 - this->_hpad, 1080 - (this->_vpad + this->_bHeight) * 5 - this->_vpad * 4), 0, -1, NULL);
    this->_player2UpKey->setImage(ResourceManager::device()->getVideoDriver()->getTexture(("./assets/settings/Keyboard/KEY_" + std::to_string(KeyP2[0]) + "_465x100.png").c_str()));
    this->_player2UpKey->setUseAlphaChannel(true);
    this->_player2UpKey->setDrawBorder(false);

    this->_effectVolume->setImage(ResourceManager::device()->getVideoDriver()->getTexture((this->_volumePath[this->_effectVolumeIdx]).c_str()));
    this->_musicVolume->setImage(ResourceManager::device()->getVideoDriver()->getTexture((this->_volumePath[this->_musicVolumeIdx]).c_str()));
    ResourceManager::guiEnvironment()->drawAll();
    ResourceManager::sceneManager()->drawAll();
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