//
// Created by kevin on 11/05/17.
//

#include <irrlicht.h>
#include "EventHandler.hh"
#include "Player.hh"
#include "Map.hh"

#include "Core.hh"

Core::Core() {

}

Core::~Core() {

}

int Core::run() {
    irr::IrrlichtDevice* device =
            irr::createDevice(irr::video::EDT_OPENGL,
                         irr::core::dimension2d<irr::u32>(640,480),
                         32);
    irr::video::IVideoDriver*  driver = device->getVideoDriver();
    irr::scene::ISceneManager* sceneManager = device->getSceneManager();

    Map map("./assets/maps/Basic.map");

    /* MODELE */

    std::array<irr::EKEY_CODE, 5>       keyMap;

    keyMap[0] = irr::KEY_KEY_Z;
    keyMap[1] = irr::KEY_KEY_S;
    keyMap[2] = irr::KEY_KEY_Q;
    keyMap[3] = irr::KEY_KEY_D;
    keyMap[4] = irr::KEY_SPACE;
    Player player(sceneManager, driver, 0, keyMap);

    /* MAP */

    irr::scene::IMetaTriangleSelector* meta = sceneManager->createMetaTriangleSelector();
    if (!meta) {
        return 1;
    }
    for (auto & wall : map.getWalls()) {
        irr::scene::ITriangleSelector*     selector = NULL;
        irr::scene::IAnimatedMesh*         wallMesh = sceneManager->getMesh(("./assets/box/" + wall.getMesh() + ".obj").c_str());
        irr::scene::ISceneNode*            wallNode = NULL;
        if (wallMesh) {
            wallMesh->setMaterialFlag(irr::video::EMF_LIGHTING, false);
            wallNode = sceneManager->addOctreeSceneNode(wallMesh->getMesh(0));
            if (wallNode) {
                wallNode->setPosition(irr::core::vector3df(50, 50, -50) * wall.getPosition());
                wallNode->setScale(irr::core::vector3df(0.5f, 0.5f, 0.5f));
            }
            sceneManager->setAmbientLight(irr::video::SColorf(1.0,1.0,1.0,0.0));
            selector = sceneManager->createOctreeTriangleSelector(wallMesh->getMesh(0), wallNode, 128);
            if (selector) {
                meta->addTriangleSelector(selector);
            }
        }
    }

    irr::scene::ISceneNodeAnimator* anim = sceneManager->createCollisionResponseAnimator(
            meta, player.getMesh(), irr::core::vector3df(10, 25, 10),
            irr::core::vector3df(0,-10,0), irr::core::vector3df(0,0,0));
    player.addAnimator(anim);
    anim->drop();

    irr::scene::ICameraSceneNode* camera = sceneManager->addCameraSceneNode(
            0,
            irr::core::vector3df(100, 100, 0),
            irr::core::vector3df(100, 0, 100));

    EventHandler receiver;
    device->setEventReceiver(&receiver);

    /* RENDU */

    while (device->run()) {
        driver->beginScene(true, true, irr::video::SColor(0,255,255,255));
        player.move(receiver);
        camera->setPosition(player.getPosition() + irr::core::vector3df(0, 150, -100));
        camera->setTarget(player.getPosition());
        sceneManager->drawAll();
        driver->endScene();
    }

    device->drop();
    return 0;
}
