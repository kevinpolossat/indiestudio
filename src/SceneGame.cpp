//
// Created by vincent on 5/15/17.
//

#include "SceneGame.hh"

SceneGame::SceneGame() :
        _scale(50, 50, 50), _map("./assets/maps/Basic.map"), _referee(_map, 2) {
    ResourceManager::loadAnimatedMesh("box.obj", "assets/box/");
    ResourceManager::loadAnimatedMesh("wall.obj", "assets/wall/");
    ResourceManager::loadAnimatedMesh("bomb.obj", "assets/Bomb/");
}

SceneGame::~SceneGame() {

}

bool SceneGame::setScene() {
    this->_bg = ResourceManager::device()->getGUIEnvironment()->addButton( irr::core::rect<irr::s32>(0, 0, 1920, 1080), 0, -1, NULL);
    this->_bg->setImage(ResourceManager::device()->getVideoDriver()->getTexture("assets/test.jpg"));
    this->_bg->setUseAlphaChannel(true);
    this->_bg->setDrawBorder(false);

    ResourceManager::sceneManager()->setAmbientLight(irr::video::SColorf(1.0,1.0,1.0,0.0));
    _referee = Referee(_map, 2);
    _players.push_back(Player(0, {irr::KEY_KEY_Z , irr::KEY_KEY_D, irr::KEY_KEY_S, irr::KEY_KEY_Q, irr::KEY_SPACE}));
    _players.push_back(Player(1, {irr::KEY_UP , irr::KEY_RIGHT, irr::KEY_DOWN, irr::KEY_LEFT, irr::KEY_END}));
    _players[0].setPosition(_map.getSpawns()[0].getPosition() * _scale + irr::core::vector3df(0, 100, 0));
    _players[1].setPosition(_map.getSpawns()[1].getPosition() * _scale + irr::core::vector3df(0, 100, 0));
    for (auto & wall : _map.getWalls()) {
        irr::scene::IAnimatedMesh*         wallMesh = ResourceManager::getAnimatedMesh("box.obj");
        irr::scene::ISceneNode*            wallNode = NULL;
        if (wallMesh) {
            wallMesh->setMaterialFlag(irr::video::EMF_LIGHTING, false);
            wallNode = ResourceManager::sceneManager()->addOctreeSceneNode(wallMesh->getMesh(0));
            if (wallNode) {
                wallNode->setMaterialTexture(0, ResourceManager::videoDriver()->getTexture("assets/box_test/SciFiCrateTextures/SciFiCrate-Emit.png"));
                wallNode->setPosition(_scale * wall.getPosition());
                wallNode->setScale(_scale / 3);
                _walls.push_back(wallNode);
            }
        }
    }
    for (auto & box : _map.getBoxes()) {
        irr::scene::IAnimatedMesh*         boxMesh = ResourceManager::getAnimatedMesh("box.obj");
        irr::scene::ISceneNode*            boxNode = NULL;
        if (boxMesh) {
            boxMesh->setMaterialFlag(irr::video::EMF_LIGHTING, false);
            boxNode = ResourceManager::sceneManager()->addOctreeSceneNode(boxMesh->getMesh(0));
            if (boxNode) {
                boxNode->setMaterialTexture(0, ResourceManager::videoDriver()->getTexture("assets/box_test/SciFiCrateTextures/SciFiCrate-EmitRed.png"));
                boxNode->setID(box.getId());
                boxNode->setPosition(_scale * box.getPosition());
                boxNode->setScale(_scale / 3);
                _boxes.push_back(boxNode);
            }
        }
    }
//    _applyCollision();
    _camera = ResourceManager::sceneManager()->addCameraSceneNode(
            0,
            _scale * irr::core::vector3df(10, 0, 0) + irr::core::vector3df(0, 700, -100),
            _scale * irr::core::vector3df(10, 0, 10) - irr::core::vector3df(0, 0, 200));
    return true;
}

int SceneGame::refresh(int *menuState) {
//    bool updateCollision = false;
    for (auto & node : _boxes) {
        if (node) {
            bool exist = false;
            for (auto const & box : _map.getBoxes()) {
                exist = exist || box.getId() == node->getID();
            }
            if (!exist) {
                node->remove();
                node = NULL;
//                updateCollision = true;
            }
        }
    }
//    if (updateCollision) {
//        _applyCollision();
//    }
    for (auto & player : _players) {
        player.move(ResourceManager::eventHandler(), _referee);
    }
    _referee.update();
    for (auto const & c : _referee.getCharacters()) {
        irr::core::vector3df v(c.getPosition() * _scale);
        _players[c.getId()].setPosition(v);
    }
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
    _boxes.clear();
    _walls.clear();
    _camera->remove();
    ResourceManager::device()->getGUIEnvironment()->clear();
    ResourceManager::device()->getSceneManager()->clear();
}

void SceneGame::_applyCollision() {
    irr::scene::IMetaTriangleSelector* meta = ResourceManager::sceneManager()->createMetaTriangleSelector();
    if (!meta) {
        return;
    }
    irr::scene::IAnimatedMesh * wallMesh = ResourceManager::getAnimatedMesh("box.obj");
    for (auto & wall : _walls) {
        irr::scene::ITriangleSelector * selector = nullptr;
        if (wall) {
            selector = ResourceManager::sceneManager()->createOctreeTriangleSelector(wallMesh->getMesh(0), wall, 128);
            if (selector) {
                meta->addTriangleSelector(selector);
            }
        }
    }
    irr::scene::IAnimatedMesh * boxMesh = ResourceManager::getAnimatedMesh("box.obj");
    for (auto & box : _boxes) {
        irr::scene::ITriangleSelector * selector = nullptr;
        if (box) {
            selector = ResourceManager::sceneManager()->createOctreeTriangleSelector(boxMesh->getMesh(0), box, 128);
            if (selector) {
                meta->addTriangleSelector(selector);
            }
        }
    }
    for (auto & player : _players) {
        player.removeAnimators();
        const irr::core::aabbox3d<irr::f32>& box = player.getMesh()->getBoundingBox();
        irr::core::vector3df radius = box.MaxEdge - box.getCenter();
        irr::scene::ISceneNodeAnimator* anim = ResourceManager::sceneManager()->createCollisionResponseAnimator(
                meta, player.getMesh(), radius,
                irr::core::vector3df(0,-10,0), irr::core::vector3df(0,0,0), 0);
        player.addAnimator(anim);
        anim->drop();
    }
}
