//
// Created by vincent on 5/15/17.
//

#include "SceneGame.hh"

SceneGame::SceneGame() {
    Map map("./assets/maps/Basic.map");
    for (auto & wall : map.getWalls()) {
        ResourceManager::loadAnimatedMesh(wall.getMesh() + ".obj", "./assets/box/");
    }
}

SceneGame::~SceneGame() {

}

bool SceneGame::setScene() {
    /* MAP */
    player = new Player(0, {irr::KEY_UP, irr::KEY_RIGHT, irr::KEY_DOWN, irr::KEY_LEFT, irr::KEY_SPACE});
    Map map("./assets/maps/Basic.map");

    irr::scene::IMetaTriangleSelector* meta = ResourceManager::sceneManager()->createMetaTriangleSelector();
    if (!meta) {
        return false;
    }
    for (auto & wall : map.getWalls()) {
        irr::scene::ITriangleSelector*     selector = NULL;
        irr::scene::IAnimatedMesh*         wallMesh = ResourceManager::getAnimatedMesh(wall.getMesh() + ".obj");
        irr::scene::ISceneNode*            wallNode = NULL;
        if (wallMesh) {
            wallMesh->setMaterialFlag(irr::video::EMF_LIGHTING, false);
            wallNode = ResourceManager::sceneManager()->addOctreeSceneNode(wallMesh->getMesh(0));
            if (wallNode) {
                wallNode->setPosition(irr::core::vector3df(50, 50, -50) * wall.getPosition());
                wallNode->setScale(irr::core::vector3df(0.5f, 0.5f, 0.5f));
            }
            ResourceManager::sceneManager()->setAmbientLight(irr::video::SColorf(1.0,1.0,1.0,0.0));
            selector = ResourceManager::sceneManager()->createOctreeTriangleSelector(wallMesh->getMesh(0), wallNode, 128);
            if (selector) {
                meta->addTriangleSelector(selector);
            }
        }
    }

    irr::scene::ISceneNodeAnimator* anim = ResourceManager::sceneManager()->createCollisionResponseAnimator(
            meta, player->getMesh(), irr::core::vector3df(10, 25, 10),
            irr::core::vector3df(0,-10,0), irr::core::vector3df(0,0,0));
    player->addAnimator(anim);
    anim->drop();
    camera = ResourceManager::sceneManager()->addCameraSceneNode(
            0,
            irr::core::vector3df(100, 100, 0),
            irr::core::vector3df(100, 0, 100));
    return true;
}

int SceneGame::refresh(int *) {
    player->move(ResourceManager::eventHandler());
    camera->setPosition(player->getPosition() + irr::core::vector3df(0, 150, -100));
    camera->setTarget(player->getPosition());
    return 2;
}

void SceneGame::unsetScene() {
  ResourceManager::device()->getGUIEnvironment()->clear();
  ResourceManager::device()->getSceneManager()->clear();
}
