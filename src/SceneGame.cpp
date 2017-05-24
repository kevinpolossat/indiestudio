//
// Created by vincent on 5/15/17.
//

#include "SceneGame.hh"

SceneGame::SceneGame()
: _map("assets/maps/Basic.map"), _referee(_map, 2) {
    ResourceManager::loadAnimatedMesh("SciFiCrate.obj", "assets/box_test/");
    ResourceManager::loadAnimatedMesh("wall.obj", "assets/wall/");
}

SceneGame::~SceneGame() {

}

bool SceneGame::setScene() {
    this->_bg = ResourceManager::device()->getGUIEnvironment()->addButton( irr::core::rect<irr::s32>(0, 0, 1920, 1080), 0, -1, NULL);
    this->_bg->setImage(ResourceManager::device()->getVideoDriver()->getTexture("assets/test.jpg"));
    this->_bg->setUseAlphaChannel(true);
    this->_bg->setDrawBorder(false);

    _referee = Referee(_map, 2);
    _players.push_back(Player(0, {irr::KEY_KEY_Z , irr::KEY_KEY_D, irr::KEY_KEY_S, irr::KEY_KEY_Q, irr::KEY_SPACE}));
    _players.push_back(Player(1, {irr::KEY_UP , irr::KEY_RIGHT, irr::KEY_DOWN, irr::KEY_LEFT, irr::KEY_SPACE}));
    irr::scene::IMetaTriangleSelector* meta = ResourceManager::sceneManager()->createMetaTriangleSelector();
    if (!meta) {
        return false;
    }
    irr::core::vector3df scale = irr::core::vector3df(62, 62, 62);
    for (auto & wall : _map.getWalls()) {
        irr::scene::ITriangleSelector*     selector = NULL;
        irr::scene::IAnimatedMesh*         wallMesh = ResourceManager::getAnimatedMesh("wall.obj");
        irr::scene::ISceneNode*            wallNode = NULL;
        if (wallMesh) {
            wallMesh->setMaterialFlag(irr::video::EMF_LIGHTING, false);
            wallNode = ResourceManager::sceneManager()->addOctreeSceneNode(wallMesh->getMesh(0));
            if (wallNode) {
                wallNode->setPosition(scale * wall.getPosition());
                wallNode->setScale(scale);
            }
            ResourceManager::sceneManager()->setAmbientLight(irr::video::SColorf(1.0,1.0,1.0,0.0));
            selector = ResourceManager::sceneManager()->createOctreeTriangleSelector(wallMesh->getMesh(0), wallNode, 128);
            if (selector) {
                meta->addTriangleSelector(selector);
            }
        }
    }
    _players[0].setPosition(_map.getSpawns()[0].getPosition() * scale + irr::core::vector3df(0, 100, 0));
    _players[1].setPosition(_map.getSpawns()[1].getPosition() * scale + irr::core::vector3df(0, 100, 0));
    for (auto & box : _map.getBoxes()) {
        irr::scene::ITriangleSelector*     selector = NULL;
        irr::scene::IAnimatedMesh*         boxMesh = ResourceManager::getAnimatedMesh("box.obj");
        irr::scene::ISceneNode*            boxNode = NULL;
        if (boxMesh) {
            boxMesh->setMaterialFlag(irr::video::EMF_LIGHTING, false);
            boxNode = ResourceManager::sceneManager()->addOctreeSceneNode(boxMesh->getMesh(0));
            if (boxNode) {
                boxNode->setPosition(scale * box.getPosition());
                boxNode->setScale(scale);
            }
            ResourceManager::sceneManager()->setAmbientLight(irr::video::SColorf(1.0,1.0,1.0,0.0));
            selector = ResourceManager::sceneManager()->createOctreeTriangleSelector(boxMesh->getMesh(0), boxNode, 128);
            if (selector) {
                meta->addTriangleSelector(selector);
            }
        }
    }

//    for (auto & player : _players) {
//        irr::scene::ISceneNodeAnimator* anim = ResourceManager::sceneManager()->createCollisionResponseAnimator(
//                meta, player.getMesh(), irr::core::vector3df(10, 25, 10),
//                irr::core::vector3df(0,-10,0), irr::core::vector3df(0,0,0));
//        player.addAnimator(anim);
//        anim->drop();
//    }
    _camera = ResourceManager::sceneManager()->addCameraSceneNode(
            0,
            irr::core::vector3df(100, 100, 0),
            irr::core::vector3df(100, 0, 100));
    return true;
}

int SceneGame::refresh(int *menuState) {
    for (auto & player : _players) {
        player.move(ResourceManager::eventHandler(), _referee);
    }
    _referee.update();
    for (auto const & c : _referee.getCharacters()) {
        irr::core::vector3df v(c.getPosition() * irr::core::vector3df(62, 62, 62));
//        v.Y = _players[c.getId()].getPosition().Y;
        _players[c.getId()].setPosition(v);
    }
    _camera->setPosition(_players[0].getPosition() + irr::core::vector3df(0, 150, -100));
    _camera->setTarget(_players[0].getPosition());
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
    _players.clear();
    _camera->remove();
    ResourceManager::device()->getGUIEnvironment()->clear();
    ResourceManager::device()->getSceneManager()->clear();
}
