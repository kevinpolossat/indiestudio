//
// Created by kevin on 11/05/17.
//

#include <irrlicht.h>
#include <chrono>

#include "Game.hh"

Game::Game() {

}

Game::~Game() {

}

int Game::run() {
    std::chrono::steady_clock::time_point tref = std::chrono::steady_clock::now();

    while (rm.device()->run()) {
        Time frameDelta = std::chrono::duration_cast<Time>(std::chrono::steady_clock::now() - tref);

        float coef = frameDelta.count();// TODO REMOVE TO RVLAUE

        rm.videoDriver()->beginScene(true, true, irr::video::SColor(0,255,255,255));
        rm.sceneManager()->drawAll();
        rm.videoDriver()->endScene();

        tref = std::chrono::steady_clock::now();
    }
   return 0;
}
