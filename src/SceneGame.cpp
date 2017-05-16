//
// Created by vincent on 5/15/17.
//

#include "SceneGame.hh"
#include "Player.hh"
#include "Map.hh"

SceneGame::SceneGame(ResourceManager & rm) : rm(rm) {

}

SceneGame::~SceneGame() {

}

bool SceneGame::setScene() {
//    Player player(rm.sceneManager(), rm.videoDriver());
//
//    /* MAP */
//    Map map("./assets/maps/Basic.map");
//
//    irr::scene::IMetaTriangleSelector* meta = rm.sceneManager()->createMetaTriangleSelector();
//    if (!meta) {
//        return false;
//    }
//    for (auto & wall : map.getWalls()) {
//        irr::scene::ITriangleSelector*     selector = NULL;
//        irr::scene::IAnimatedMesh*         wallMesh = rm.sceneManager()->getMesh(("./assets/box/" + wall.getMesh() + ".obj").c_str());
//        irr::scene::ISceneNode*            wallNode = NULL;
//        if (wallMesh) {
//            wallMesh->setMaterialFlag(irr::video::EMF_LIGHTING, false);
//            wallNode = rm.sceneManager()->addOctreeSceneNode(wallMesh->getMesh(0));
//            if (wallNode) {
//                wallNode->setPosition(irr::core::vector3df(50, 50, -50) * wall.getPosition());
//                wallNode->setScale(irr::core::vector3df(0.5f, 0.5f, 0.5f));
//            }
//            rm.sceneManager()->setAmbientLight(irr::video::SColorf(1.0,1.0,1.0,0.0));
//            selector = rm.sceneManager()->createOctreeTriangleSelector(wallMesh->getMesh(0), wallNode, 128);
//            if (selector) {
//                meta->addTriangleSelector(selector);
//            }
//        }
//    }
//
//    irr::scene::ISceneNodeAnimator* anim = rm.sceneManager()->createCollisionResponseAnimator(
//            meta, player.getMesh(), irr::core::vector3df(10, 25, 10),
//            irr::core::vector3df(0,-10,0), irr::core::vector3df(0,0,0));
//    player.addAnimator(anim);
//    anim->drop();
//
//    irr::scene::ICameraSceneNode* camera = rm.sceneManager()->addCameraSceneNode(
//            0,
//            irr::core::vector3df(100, 100, 0),
//            irr::core::vector3df(100, 0, 100));
//
//    /* RENDU */
//
    return true;
}

int SceneGame::refresh(int *) {
//    player.move(receiver);
//    camera->setPosition(player.getPosition() + irr::core::vector3df(0, 150, -100));
//    camera->setTarget(player.getPosition());
    return 1;
}

void SceneGame::unsetScene() {
}