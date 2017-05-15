//
// Created by kevin on 11/05/17.
//

#include <irrlicht.h>
#include "EventHandler.hh"
#include "Player.hh"
#include "Map.hh"

#include "Game.hh"

Game::Game() {

}

Game::~Game() {

}

int Game::run() {
    irr::video::IVideoDriver*  driver       = _rm.videoDriver();
    irr::scene::ISceneManager* sceneManager = _rm.sceneManager();

    EventHandler receiver;
    _rm.device()->setEventReceiver(&receiver);

    while (_rm.device()->run()) {
        driver->beginScene(true, true, irr::video::SColor(0,255,255,255));
        sceneManager->drawAll();
        driver->endScene();
    }
   return 0;
}
