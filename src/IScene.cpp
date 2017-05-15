/*
** Scene.cpp for indiestudio in /home/fraiss_c/rendu/indiestudio/Scene.cpp
**
** Made by Charles Fraïssé
** Login   <charles.fraisse@epitech.eu>
**
** Started on  Mon May 15 11:16:06 2017 Charles Fraïssé
** Last update Mon May 15 11:16:06 2017 Charles Fraïssé
*/

#include "IScene.hh"

Scene::Scene(irr::IrrlichtDevice *device) {
    this->_driver = device->getVideoDriver();
    this->_smgr = device->getSceneManager();
    this->_gui = device->getGUIEnvironment();
}

Scene::~Scene() {

}

bool
Scene::setScene(irr::IrrlichtDevice *) {
    return true;
}

int
Scene::refresh(irr::IrrlichtDevice *, int *, EventReceiver *) {
    return 0;
}

void
Scene::unsetScene() {

}