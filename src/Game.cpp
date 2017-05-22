//
// Created by kevin on 11/05/17.
//

#include <irrlicht.h>
#include <chrono>
#include <vector>

#include "Game.hh"
#include "SceneGame.hh"
#include "MenuMainPage.hh"
#include "MenuSettingsPage.hh"
#include "SplashScreen.hh"
#include "MenuGamePause.hh"

Game::Game() {
    _sceneIdx = 3;
    _scenes.push_back(std::make_unique<MenuMainPage>()); // TO DEFINE BEHAVIOR may be a stack ???
    _scenes.push_back(std::make_unique<MenuSettingsPage>()); // TO DEFINE BEHAVIOR may be a stack ???
    _scenes.push_back(std::make_unique<SceneGame>()); // TO DEFINE BEHAVIOR may be a stack ???
    _scenes.push_back(std::make_unique<SplashScreen>()); // TO DEFINE BEHAVIOR may be a stack ???
    _scenes.push_back(std::make_unique<MenuGamePause>()); // TO DEFINE BEHAVIOR may be a stack ???
}

Game::~Game() {

}

int Game::run() {
    std::chrono::steady_clock::time_point tref = std::chrono::steady_clock::now();

    if (!_scenes[_sceneIdx]->setScene()) {
        return 0;
    }
    while (ResourceManager::device()->run()) {
        Time frameDelta = std::chrono::duration_cast<Time>(std::chrono::steady_clock::now() - tref);

        float coef = frameDelta.count();// TODO REMOVE TO RVLAUE

        ResourceManager::videoDriver()->beginScene(true, true, irr::video::SColor(0, 0, 0, 0));
        int rtn = _scenes[_sceneIdx]->refresh(&_sceneIdx);

        if (!rtn) {
            break;
        } else if (rtn == 1) {
            if (!_scenes[_sceneIdx]->setScene()) {
                return 0;
            }
        }

        tref = std::chrono::steady_clock::now();
    }
   return 0;
}
