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

Game::Game() {
    _sceneIdx = SPLASHSCREEN;
    _scenes.push_back(std::make_unique<SplashScreen>()); // TO DEFINE BEHAVIOR may be a stack ???
    _scenes.push_back(std::make_unique<MenuMainPage>()); // TO DEFINE BEHAVIOR may be a stack ???
    _scenes.push_back(std::make_unique<MenuSettingsPage>()); // TO DEFINE BEHAVIOR may be a stack ???
    _scenes.push_back(std::make_unique<MenuCreditPage>()); // TO DEFINE BEHAVIOR may be a stack ???
    _scenes.push_back(std::make_unique<MenuGameMode>()); // TO DEFINE BEHAVIOR may be a stack ???
    _scenes.push_back(std::make_unique<MenuLocalGame>()); // TO DEFINE BEHAVIOR may be a stack ???
    _scenes.push_back(std::make_unique<SceneGame>()); // TO DEFINE BEHAVIOR may be a stack ???
//    _scenes.push_back(std::make_unique<MenuGamePause>()); // TO DEFINE BEHAVIOR may be a stack ???
}

Game::~Game() {

}

int Game::run() {
    std::chrono::steady_clock::time_point tref = std::chrono::steady_clock::now();
    bool                isSoundPlaying = false;
    bool                first = true;
    sf::SoundBuffer     menubuf;
    sf::Sound           menusound;

    if (!menubuf.loadFromFile("assets/menuSong.ogg"))
        return 0;
    menusound.setBuffer(menubuf);
    menusound.setLoop(true);

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
    }
    if (isSoundPlaying)
        menusound.stop();
   return 0;
}
