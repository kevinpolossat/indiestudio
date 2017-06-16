/*
** MenuGameMode.cpp for indiestudio in /home/fraiss_c/rendu/indiestudio/MenuGameMode.cpp
**
** Made by Charles Fraïssé
** Login   <charles.fraisse@epitech.eu>
**
** Started on  Mon May 29 16:18:26 2017 Charles Fraïssé
** Last update Mon May 29 16:18:26 2017 Charles Fraïssé
*/

#include <Save.hh>
#include <Settings.hh>
#include "MenuGameMode.hh"

MenuGameMode::MenuGameMode() {
    this->_hpad = 60;
    this->_bHeight = 125;
}

MenuGameMode::~MenuGameMode() {

}

bool
MenuGameMode::setScene() {
    Settings::refereePath() = "";
    this->_idx = 0;
    this->_frame = 0;
    this->unsetScene();
    this->_bg = ResourceManager::device()->getGUIEnvironment()->addButton( irr::core::rect<irr::s32>(0, 0, 1920, 1080), 0, -1, NULL);
    this->_bg->setImage(ResourceManager::device()->getVideoDriver()->getTexture("./assets/BG.png"));
    this->_bg->setUseAlphaChannel(true);
    this->_bg->setDrawBorder(false);
    this->_bg->setEnabled(false);
    this->_back = ResourceManager::device()->getGUIEnvironment()->addButton(irr::core::rect<irr::s32>(10, 10, 250 + 10, 60 + 10), 0, -1, NULL);
    this->_back->setImage(ResourceManager::device()->getVideoDriver()->getTexture("./assets/Fonts/Back_250x60.png"));
    this->_back->setUseAlphaChannel(true);
    this->_back->setDrawBorder(false);
    this->_local = ResourceManager::device()->getGUIEnvironment()->addButton(irr::core::rect<irr::s32>(this->_hpad, (1080 / 2) - (this->_bHeight / 2), (1920 / 2) - this->_hpad, (1080 / 2) + (this->_bHeight / 2)), 0, -1, NULL);
    this->_local->setImage(ResourceManager::device()->getVideoDriver()->getTexture("./assets/Fonts/NewGameFat_840x125.png"));
    this->_local->setUseAlphaChannel(true);
    this->_local->setDrawBorder(false);
    this->_online = ResourceManager::device()->getGUIEnvironment()->addButton(irr::core::rect<irr::s32>((1920 / 2) + this->_hpad, (1080 / 2) - (this->_bHeight / 2), 1920 - this->_hpad, (1080 / 2) + (this->_bHeight / 2)), 0, -1, NULL);
    this->_online->setImage(ResourceManager::device()->getVideoDriver()->getTexture("./assets/Fonts/LoadGame_840x125.png"));
    this->_online->setUseAlphaChannel(true);
    this->_online->setDrawBorder(false);

    this->_font = ResourceManager::guiEnvironment()->getFont("./assets/IrrFont/cancer.xml");
    irr::gui::IGUISkin *skin = ResourceManager::guiEnvironment()->getSkin();
    skin->setFont(this->_font);
    this->_box = ResourceManager::guiEnvironment()->addComboBox(irr::core::rect<irr::s32>(960,(1080 / 2) - 20 - 200, 1910, (1080/2) + 20 - 200));
    std::vector<std::string> saves = Save::getSaves();
    for(auto s : saves) {
        std::wstring tmp = std::wstring(s.begin(), s.end());
        this->_box->addItem(tmp.c_str());
    }
    return true;
}

int
MenuGameMode::refresh(int &menuState) {
    auto firstController = ResourceManager::eventHandler().getJoystick(ResourceManager::getControllers()[0]);
    const irr::u32 now = ResourceManager::device()->getTimer()->getTime();
    const irr::f32 frameDeltaTime = (irr::f32) (now - this->_time) / 1000.f;

    if (_frame > 10) {
        if (this->_back->isPressed() || ResourceManager::eventHandler().isKeyDown(irr::KEY_ESCAPE) || firstController.ButtonStates == 4) {
            this->unsetScene();
            menuState = MENUMAINPAGE;
            return 1;
        } else if (this->_local->isPressed()) {
            this->unsetScene();
            menuState = MENULOCALGAME;
            return 1;
        } else if (this->_online->isPressed()) {
            std::wstring tmp = std::wstring(this->_box->getItem(this->_box->getSelected()));
            Settings::refereePath() = std::string(tmp.begin(), tmp.end());
            menuState = SCENEGAME;
            this->unsetScene();
            return 1;
        } else if (ResourceManager::eventHandler().isKeyDown(irr::KEY_RETURN) || firstController.ButtonStates == 2) {
            if (this->_idx) {
                std::wstring tmp = std::wstring(this->_box->getItem(this->_box->getSelected()));
                Settings::refereePath() = std::string(tmp.begin(), tmp.end());
                menuState = SCENEGAME;
            } else {
                menuState = MENULOCALGAME;
            }
            this->unsetScene();
            return 1;
        }
    }
    if (frameDeltaTime > 0.1) {
        if (ResourceManager::eventHandler().isKeyDown(irr::KEY_RIGHT) || firstController.Axis[0] > 0) {
            this->_idx = 1;
            this->_local->setImage(ResourceManager::device()->getVideoDriver()->getTexture("./assets/Fonts/NewGame_840x125.png"));
            this->_online->setImage(ResourceManager::device()->getVideoDriver()->getTexture("./assets/Fonts/LoadGameFat_840x125.png"));
        } else if (ResourceManager::eventHandler().isKeyDown(irr::KEY_LEFT)  || firstController.Axis[0] < 0) {
            this->_idx = 0;
            this->_local->setImage(ResourceManager::device()->getVideoDriver()->getTexture("./assets/Fonts/NewGameFat_840x125.png"));
            this->_online->setImage(ResourceManager::device()->getVideoDriver()->getTexture("./assets/Fonts/LoadGame_840x125.png"));
        }
    }
    ResourceManager::guiEnvironment()->drawAll();
    ResourceManager::sceneManager()->drawAll();
    ResourceManager::videoDriver()->endScene();
    if (this->_frame < 11)
        this->_frame += 1;
    return 2;
}

void
MenuGameMode::unsetScene() {
    ResourceManager::device()->getGUIEnvironment()->clear();
}