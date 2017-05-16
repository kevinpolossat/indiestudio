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

Game::Game() {
    _sceneIdx = 0;
    _scenes.push_back(std::make_unique<MenuMainPage>()); // TO DEFINE BEHAVIOR may be a stack ???
}

Game::~Game() {

}

int Game::run() {
    std::chrono::steady_clock::time_point tref = std::chrono::steady_clock::now();

    _scenes[_sceneIdx]->setScene(_rm.device());
    while (_rm.device()->run()) {
        Time frameDelta = std::chrono::duration_cast<Time>(std::chrono::steady_clock::now() - tref);

        float coef = frameDelta.count();// TODO REMOVE TO RVLAUE

        _rm.videoDriver()->beginScene(true, true, irr::video::SColor(0,255,255,255));
        _scenes[_sceneIdx]->refresh(_rm.device(), &_sceneIdx, NULL);
        _rm.guiEnvironment()->drawAll();
        _rm.sceneManager()->drawAll();
        _rm.videoDriver()->endScene();

        tref = std::chrono::steady_clock::now();
    }
   return 0;
}
