//
// Created by vincent on 5/15/17.
//

#include "SceneGame.hh"

SceneGame::SceneGame() {
    Map map("./assets/maps/Basic.map");
    for (auto & wall : map.getWalls()) {
        ResourceManager::loadAnimatedMesh("untitled.obj", "./assets/obj/");
    }
}

SceneGame::~SceneGame() {

}

bool SceneGame::setScene() {
    /* MAP */
    player = new Player(0, {irr::KEY_KEY_Z , irr::KEY_KEY_D, irr::KEY_KEY_S, irr::KEY_KEY_Q, irr::KEY_SPACE});
    Map map("./assets/maps/Basic.map");

    this->_bg = ResourceManager::device()->getGUIEnvironment()->addButton( irr::core::rect<irr::s32>(0, 0, 1920, 1080), 0, -1, NULL);
    this->_bg->setImage(ResourceManager::device()->getVideoDriver()->getTexture("assets/test.jpg"));
    this->_bg->setUseAlphaChannel(true);
    this->_bg->setDrawBorder(false);
    irr::scene::IMetaTriangleSelector* meta = ResourceManager::sceneManager()->createMetaTriangleSelector();
    if (!meta) {
        return false;
    }
    for (auto & wall : map.getWalls()) {
        irr::scene::ITriangleSelector*     selector = NULL;
        irr::scene::IAnimatedMesh*         wallMesh = ResourceManager::getAnimatedMesh("untitled.obj");
        irr::scene::ISceneNode*            wallNode = NULL;
        if (wallMesh) {
            wallMesh->setMaterialFlag(irr::video::EMF_LIGHTING, false);
            wallNode = ResourceManager::sceneManager()->addOctreeSceneNode(wallMesh->getMesh(0));
            if (wallNode) {
                wallNode->setPosition(irr::core::vector3df(50, 50, -50) * wall.getPosition());
//                wallNode->setScale(irr::core::vector3df(0.5f, 0.5f, 0.5f));
                wallNode->setScale(irr::core::vector3df(62, 62, 62));
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

int SceneGame::refresh(int *menuState) {
    player->move(ResourceManager::eventHandler());
    camera->setPosition(player->getPosition() + irr::core::vector3df(0, 150, -100));
    camera->setTarget(player->getPosition());
    if (ResourceManager::eventHandler().isKeyDown(irr::KEY_ESCAPE)) {
        *menuState = 4;
        return 1;
    }
    ResourceManager::guiEnvironment()->drawAll();
    ResourceManager::sceneManager()->drawAll();
    ResourceManager::videoDriver()->endScene();
    return 2;
}

void SceneGame::unsetScene() {
    camera->remove();
    ResourceManager::device()->getGUIEnvironment()->clear();
    ResourceManager::device()->getSceneManager()->clear();
}
