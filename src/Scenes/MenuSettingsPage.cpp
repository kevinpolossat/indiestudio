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
    this->_reset = ResourceManager::device()->getGUIEnvironment()->addButton(irr::core::rect<irr::s32>(1920 - (this->_bWidth + this->_hpad), this->_vpad, 1920 - this->_hpad, this->_bHeight + this->_vpad), 0, -1, L"Reset");


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
MenuSettingsPage::refresh(int &menuState) {
    //TODO GHOSTING
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
    }


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