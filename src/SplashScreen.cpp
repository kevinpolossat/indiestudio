/*
** SplashScreen.cpp for indiestudio in /home/fraiss_c/rendu/indiestudio/SplashScreen.cpp
**
** Made by Charles Fraïssé
** Login   <charles.fraisse@epitech.eu>
**
** Started on  Tue May 16 14:53:17 2017 Charles Fraïssé
** Last update Tue May 16 14:53:17 2017 Charles Fraïssé
*/

#include "SplashScreen.hh"

SplashScreen::SplashScreen() {
    this->_frame = 0;
    ResourceManager::loadAnimatedMesh("tinker.obj", "./assets/Indiefined::Studio/");
}

SplashScreen::~SplashScreen() {

}

bool
SplashScreen::setScene() {
    ResourceManager::device()->getSceneManager()->addCameraSceneNode(0, irr::core::vector3df(0, 0, 0), irr::core::vector3df(0, 0, 1));
    irr::scene::IAnimatedMesh  *titleMesh = ResourceManager::getAnimatedMesh("tinker.obj");
    if (!titleMesh) {
        ResourceManager::device()->drop();
        return false;
    }
    this->_titleNode = ResourceManager::device()->getSceneManager()->addAnimatedMeshSceneNode(titleMesh);
    if (this->_titleNode) {
        this->_titleNode->setMaterialFlag(irr::video::EMF_LIGHTING, false);
        this->_titleNode->setMD2Animation(irr::scene::EMAT_STAND);
        this->_titleNode->setPosition(irr::core::vector3df(0, 0, 400));
        this->_titleNode->setRotation(irr::core::vector3df(0, 180, 0));
    }
    return true;
}

int
SplashScreen::refresh(int *menuState) {
    if (this->_frame <= 150) {
        this->_titleNode->setPosition(irr::core::vector3df(0, 0, 400 - this->_frame * 3));
        this->_titleNode->setRotation(irr::core::vector3df(this->_frame * 15, 180, 0));
    } else {
        this->_titleNode->setPosition(irr::core::vector3df(50, 0, 400));
        this->_titleNode->setScale(irr::core::vector3df(5, 5, .3));
        this->_titleNode->setRotation(irr::core::vector3df(0, 180, 0));
    }
    this->_frame += 1;
    if (this->_frame == 200) {
        this->unsetScene();
        *menuState = 0;
        return 1;
    }
    return 2;
}

void
SplashScreen::unsetScene() {
  ResourceManager::sceneManager()->clear();
}
