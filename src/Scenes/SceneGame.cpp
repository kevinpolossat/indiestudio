//
// Created by vincent on 5/15/17.
//

#include <IA.hh>
#include "SceneGame.hh"

SceneGame::SceneGame()
        : _scale(2.f, 2.f, 2.f), _map("./assets/maps/Basic.map"), _referee(_map, 3) {
    ResourceManager::loadAnimatedMesh("box.obj", "assets/box/");
    ResourceManager::loadAnimatedMesh("wall.obj", "assets/wall/");
    ResourceManager::loadAnimatedMesh("bomb.obj", "assets/bomb/");
    ResourceManager::loadAnimatedMesh("ground.obj", "assets/ground/");
}

SceneGame::~SceneGame() {
}

bool SceneGame::setScene() {
    ResourceManager::sceneManager()->setAmbientLight(irr::video::SColorf(1.0,1.0,1.0,0.0));
    _referee = Referee(_map, 3);
    _players.push_back(std::make_unique<Player>(Player(0, {irr::KEY_KEY_Z , irr::KEY_KEY_D, irr::KEY_KEY_S, irr::KEY_KEY_Q, irr::KEY_SPACE}, _scale)));
    _players.push_back(std::make_unique<Player>(Player(1, {irr::KEY_UP , irr::KEY_RIGHT, irr::KEY_DOWN, irr::KEY_LEFT, irr::KEY_END}, _scale)));
    _players.push_back(std::make_unique<IA>(IA(2, _scale)));
    for (auto & player : _players) {
        player->getNode().init();
    }
    _createGround();
    _createWalls();
    _createBoxes();
    _camera = ResourceManager::sceneManager()->addCameraSceneNode(
            0,
            _scale * irr::core::vector3df(10.5, 15, -5),
            _scale * irr::core::vector3df(10.5, 0, 12));
    return true;
}

void SceneGame::_scaleNode(irr::scene::ISceneNode *node) {
    irr::core::vector3df boundingBox = node->getBoundingBox().getExtent();
    node->setScale(irr::core::vector3df(_scale.X / boundingBox.X, _scale.Y / boundingBox.Y, _scale.Z / boundingBox.Z));
}

void SceneGame::_createBoxes() {
    irr::scene::IAnimatedMesh * boxMesh = ResourceManager::getAnimatedMesh("box.obj");
    irr::scene::ISceneNode *    boxNode = nullptr;
    if (boxMesh) {
        boxMesh->setMaterialFlag(irr::video::EMF_LIGHTING, false);
        for (auto const & box : _map.getBoxes()) {
            boxNode = ResourceManager::sceneManager()->addOctreeSceneNode(boxMesh->getMesh(0));
            if (boxNode) {
                boxNode->setMaterialTexture(0, ResourceManager::videoDriver()->getTexture("assets/box/SciFiCrateTextures/SciFiCrate-EmitRed.png"));
                boxNode->setID(box.getId());
                boxNode->setPosition(_scale * box.getPosition());
                _scaleNode(boxNode);
                _boxes.push_back(boxNode);
            }
        }
    }
}

void SceneGame::_createWalls() {
    irr::scene::IAnimatedMesh * wallMesh = ResourceManager::getAnimatedMesh("box.obj");
    irr::scene::ISceneNode *    wallNode = nullptr;
    if (wallMesh) {
        wallMesh->setMaterialFlag(irr::video::EMF_LIGHTING, false);
        for (auto const & wall : _map.getWalls()) {
            wallNode = ResourceManager::sceneManager()->addOctreeSceneNode(wallMesh->getMesh(0));
            if (wallNode) {
                wallNode->setMaterialTexture(0, ResourceManager::videoDriver()->getTexture("assets/box/SciFiCrateTextures/SciFiCrate-Emit.png"));
                wallNode->setPosition(_scale * wall.getPosition());
                _scaleNode(wallNode);
                _walls.push_back(wallNode);
            }
        }
    }
}

void SceneGame::_createGround() {
    irr::scene::IAnimatedMesh * groundMesh = ResourceManager::getAnimatedMesh("ground.obj");
    irr::scene::ISceneNode *    groundNode = nullptr;
    if (groundMesh) {
        groundMesh->setMaterialFlag(irr::video::EMF_LIGHTING, false);
        groundNode = ResourceManager::sceneManager()->addOctreeSceneNode(groundMesh->getMesh(0));
        if (groundNode) {
            groundNode->setPosition(irr::core::vector3df(-4, -1, -4) * _scale);
            groundNode->setScale(_scale * irr::core::vector3df(29, 0, 29));
        }
    }
}

int SceneGame::refresh(int &menuState) {
    _players.erase(std::remove_if(_players.begin(), _players.end(), [&](auto & player) {
        return std::find_if(_referee.getCharacters().begin(), _referee.getCharacters().end(), [&player](Character const & c) -> bool { return c.getId() == player->getId();}) == _referee.getCharacters().end();
    }), _players.end());
    for (auto & player : _players) {
        if (player) {
            player->move(ResourceManager::eventHandler(), _referee);
        }
    }
    _referee.update();
    // DELETE BOXES
    for (auto & node : _boxes) {
        if (node) {
            auto f = std::find_if(_map.getBoxes().begin(), _map.getBoxes().end(), [&node](Cell const & c){ return node->getID() == c.getId(); });
            if (f == _map.getBoxes().end()) {
                node->remove();
                node = nullptr;
            }
        }
    }
    // REMOVE BOMBS
    for (auto & bomb : _bombs) {
        if (bomb) {
            auto f = std::find_if(_referee.getBombs().begin(), _referee.getBombs().end(), [&bomb](Bomb const & cell){ return bomb->getID() == cell.getId(); });
            if (f == _referee.getBombs().end()) {
                bomb->remove();
                bomb = nullptr;
            }
        }
    }
    // ADD NEW BOMB
    for (auto & bomb : _referee.getBombs()) {
        auto f = std::find_if(_bombs.begin(), _bombs.end(), [&bomb](auto node){ return node && node->getID() == bomb.getId(); });
        if (f == _bombs.end()) {
            irr::scene::IAnimatedMesh * bombMesh = ResourceManager::getAnimatedMesh("bomb.obj");
            irr::scene::ISceneNode *    bombNode = nullptr;
            if (bombMesh) {
                bombMesh->setMaterialFlag(irr::video::EMF_LIGHTING, false);
                bombNode = ResourceManager::sceneManager()->addOctreeSceneNode(bombMesh->getMesh(0));
                if (bombNode) {
                    bombNode->setPosition(bomb.getPosition() * _scale);
                    bombNode->setID(bomb.getId());
                    _scaleNode(bombNode);
                    std::cerr << bombNode->getPosition().X << " " << bombNode->getPosition().Y << " " << bombNode->getPosition().Z << std::endl;
                    _bombs.push_back(bombNode);
                }
            }

        }
    }
    // CHANGE PLAYER POSITION
    for (auto & player : _players) {
        auto c = std::find_if(_referee.getCharacters().begin(), _referee.getCharacters().end(), [&player](Character const & c) -> bool { return c.getId() == player->getId();});
        if (c != _referee.getCharacters().end()) {
            player->getNode().setPosition(c->getPosition() * _scale);
        }
    }
    // CHECK FOR PAUSE MENU
    if (ResourceManager::eventHandler().isKeyDown(irr::KEY_ESCAPE)) {
        menuState = MENUGAMEPAUSE;
        return 1;
    }
    // DRAW ALL
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