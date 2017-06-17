//
// Created by kevin on 11/05/17.
//

#include <irrlicht.h>
#include <chrono>
#include <vector>

#include "Game.hh"
#include "IScene.hh"
#include "SceneGame.hh"
#include "MenuMainPage.hh"
#include "MenuSettingsPage.hh"
#include "MenuGameMode.hh"
#include "MenuLocalGame.hh"
#include "MenuCreditPage.hh"
#include "SplashScreen.hh"
#include "Settings.hh"

Game::Game() {
    _sceneIdx = SPLASHSCREEN;
    _scenes.push_back(std::make_unique<SplashScreen>());
    _scenes.push_back(std::make_unique<MenuMainPage>());
    _scenes.push_back(std::make_unique<MenuSettingsPage>());
    _scenes.push_back(std::make_unique<MenuCreditPage>());
    _scenes.push_back(std::make_unique<MenuGameMode>());
    _scenes.push_back(std::make_unique<MenuLocalGame>());
    _scenes.push_back(std::make_unique<SceneGame>());
#ifdef SOUND
    ResourceManager::loadSound("menuSong.ogg");
#endif
}

Game::~Game() {

}

int Game::run() {
    std::chrono::steady_clock::time_point tref = std::chrono::steady_clock::now();
    bool                isSoundPlaying = false;
    bool                first = true;
    sf::Sound           menusound;

#ifdef SOUND
    menusound.setBuffer(ResourceManager::getSound("menuSong.ogg"));
#endif
    menusound.setLoop(true);
    auto &controllersID = ResourceManager::getControllers();
    irr::core::array<irr::SJoystickInfo> joystickInfo;
    if(ResourceManager::device()->activateJoysticks(joystickInfo))
    {
        std::cout << "Joystick support is enabled and " << joystickInfo.size() << " joystick(s) are present." << std::endl;
        for(irr::u32 joystick = 0; joystick < joystickInfo.size(); ++joystick)
        {
            if (joystickInfo[joystick].Name == "Sony Computer Entertainment Wireless Controller") {
                if (controllersID[0] == -1) {
                    controllersID[0] = joystick;
                } else {
                    controllersID[1] = joystick;
                }
            }
            std::cout << "Joystick " << joystick << ":" << std::endl;
            std::cout << "\tName: '" << joystickInfo[joystick].Name.c_str() << "'" << std::endl;
            std::cout << "\tAxes: " << joystickInfo[joystick].Axes << std::endl;
            std::cout << "\tButtons: " << joystickInfo[joystick].Buttons << std::endl;

            std::cout << "\tHat is: ";

            switch(joystickInfo[joystick].PovHat)
            {
                case irr::SJoystickInfo::POV_HAT_PRESENT:
                    std::cout << "present" << std::endl;
                    break;

                case irr::SJoystickInfo::POV_HAT_ABSENT:
                    std::cout << "absent" << std::endl;
                    break;

                case irr::SJoystickInfo::POV_HAT_UNKNOWN:
                default:
                    std::cout << "unknown" << std::endl;
                    break;
            }
        }
    } else {
        std::cout << "Joystick support is not enabled." << std::endl;
    }

    if (!_scenes[_sceneIdx]->setScene()) {
        return 0;
    }
    while (ResourceManager::device()->run()) {
        Time frameDelta = std::chrono::duration_cast<Time>(std::chrono::steady_clock::now() - tref);

        //float coef = frameDelta.count();// TODO REMOVE TO RVLAUE

        ResourceManager::videoDriver()->beginScene(true, true, irr::video::SColor(0, 0, 0, 0));
        int rtn = _scenes[_sceneIdx]->refresh(_sceneIdx);

        if (!rtn) {
            break;
        } else if (rtn == 1) {
            if (first && _sceneIdx == MENUMAINPAGE) {
                menusound.play();
                isSoundPlaying = true;
                first = false;
            } else if (_sceneIdx == SCENEGAME) {
                menusound.stop();
                isSoundPlaying = false;
            } else if (!isSoundPlaying) {
                menusound.play();
                isSoundPlaying = true;
            }
            if (!_scenes[_sceneIdx]->setScene()) {
                if (isSoundPlaying)
                    menusound.stop();
                return 0;
            }
        }
        tref = std::chrono::steady_clock::now();
        menusound.setVolume(Settings::music_volume() * 10);
    }
    if (isSoundPlaying)
        menusound.stop();
    return 0;
}
