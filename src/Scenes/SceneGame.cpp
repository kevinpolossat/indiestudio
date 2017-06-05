//
// Created by vincent on 5/15/17.
//

#include "SceneGame.hh"

SceneGame::SceneGame()
        : _scale(2.f, 2.f, 2.f),
          _map("./assets/maps/Basic.map"),
          _referee(_map, 3),
          _isPaused(false),
          _echapTimer(-1) {
    ResourceManager::loadAnimatedMesh("box.obj", "assets/box/");
    ResourceManager::loadAnimatedMesh("wall.obj", "assets/wall/");
    ResourceManager::loadAnimatedMesh("bomb.obj", "assets/bomb/");
    ResourceManager::loadAnimatedMesh("powerup.obj", "assets/powerup/");
    ResourceManager::loadAnimatedMesh("ground.obj", "assets/ground/");
}

SceneGame::~SceneGame() {
}

bool SceneGame::setScene() {
    ResourceManager::sceneManager()->setAmbientLight(irr::video::SColorf(1.0,1.0,1.0,0.0));
    _map.clearMap();
    _map.loadFromFile("./assets/maps/Basic.map");
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

    int verticalSize = 100;
    int horizontalSize = 500 - 100;
    float verticalPadding = (1080 - 400 - (verticalSize * 4)) / 5;
//    float horizontalPadding = 50;
    _menuBg = ResourceManager::device()->getGUIEnvironment()->addButton( irr::core::rect<irr::s32>(710, 200, 500 + 710, 1080 - 200), 0, -1, NULL);
    _menuBg->setImage(ResourceManager::device()->getVideoDriver()->getTexture("assets/BG.png"));
    _menuBg->setUseAlphaChannel(true);
    _menuBg->setDrawBorder(false);
    _menuBg->setEnabled(false);
    _menuResume = ResourceManager::guiEnvironment()->addButton(irr::core::rect<irr::s32>(760 , 200 + verticalPadding, 760 + horizontalSize, 200 + verticalPadding + verticalSize), 0, 42, NULL);
    _menuResume->setImage(ResourceManager::device()->getVideoDriver()->getTexture("assets/Fonts/Resume_400x100.png"));
    _menuResume->setUseAlphaChannel(true);
    _menuResume->setDrawBorder(false);
    _menuSave = ResourceManager::guiEnvironment()->addButton(irr::core::rect<irr::s32>(760 , 200 + verticalSize + verticalPadding * 2, 760 + horizontalSize, 200 + verticalSize * 2 + verticalPadding * 2), 0, 42, NULL);
    _menuSave->setImage(ResourceManager::device()->getVideoDriver()->getTexture("assets/Fonts/Save_400x100.png"));
    _menuSave->setUseAlphaChannel(true);
    _menuSave->setDrawBorder(false);
    _menuSettings = ResourceManager::guiEnvironment()->addButton(irr::core::rect<irr::s32>(760 , 200 + verticalSize * 2 + verticalPadding * 3, 760 + horizontalSize, 200 + verticalSize * 3 + verticalPadding * 3), 0, 42, NULL);
    _menuSettings->setImage(ResourceManager::device()->getVideoDriver()->getTexture("assets/Fonts/Settings_400x100.png"));
    _menuSettings->setUseAlphaChannel(true);
    _menuSettings->setDrawBorder(false);
    _menuQuit = ResourceManager::guiEnvironment()->addButton(irr::core::rect<irr::s32>(760 , 200 + verticalSize * 3 + verticalPadding * 4, 760 + horizontalSize, 200 + verticalSize * 4 + verticalPadding * 4), 0, 42, NULL);
    _menuQuit->setImage(ResourceManager::device()->getVideoDriver()->getTexture("assets/Fonts/Exit_400x100.png"));
    _menuQuit->setUseAlphaChannel(true);
    _menuQuit->setDrawBorder(false);
    return true;
}

void SceneGame::_scaleNode(irr::scene::ISceneNode *node) {
    irr::core::vector3df boundingBox = node->getBoundingBox().getExtent();
    float maxVal = std::max(boundingBox.X, std::max(boundingBox.Y, boundingBox.Z));
    node->setScale(_scale / maxVal);
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
    _referee.update(true);
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
    // REMOVE EXPLOSIONS
    _explosions.erase(std::remove_if(_explosions.begin(), _explosions.end(), [](Explosion & e){ return e.isOver(); }), _explosions.end());
    // REMOVE BOMBS
    for (auto & bomb : _bombs) {
        if (bomb) {
            auto f = std::find_if(_referee.getBombs().begin(), _referee.getBombs().end(), [&bomb](Bomb const & cell){ return bomb->getID() == cell.getId(); });
            if (f == _referee.getBombs().end()) {
                _explosions.push_back(Explosion(bomb->getPosition(), 2.0f));
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
                    _bombs.push_back(bombNode);
                }
            }

        }
    }
    // REMOVE POWERUPS
    for (auto & powerup : _powerups) {
        if (powerup) {
            auto f = std::find_if(_referee.getBonuses().begin(), _referee.getBonuses().end(), [&powerup](PowerUp const & cell){ return powerup->getID() == cell.getId(); });
            if (f == _referee.getBonuses().end()) {
                powerup->remove();
                powerup = nullptr;
            }
        }
    }
    // ADD NEW POWERUPS
    for (auto & powerup : _referee.getBonuses()) {
        auto f = std::find_if(_powerups.begin(), _powerups.end(), [&powerup](auto node) -> bool { return node && node->getID() == powerup.getId(); });
        if (f == _powerups.end()) {
            irr::scene::IAnimatedMesh * powerupMesh = ResourceManager::getAnimatedMesh("powerup.obj");
            irr::scene::ISceneNode *    powerupNode = nullptr;
            if (powerupMesh) {
                powerupMesh->setMaterialFlag(irr::video::EMF_LIGHTING, false);
                powerupNode = ResourceManager::sceneManager()->addOctreeSceneNode(powerupMesh->getMesh(0));
                if (powerupNode) {
                    powerupNode->addAnimator(ResourceManager::sceneManager()->createRotationAnimator(irr::core::vector3df(0, 1, 0)));
                    powerupNode->setPosition((powerup.getPosition() + irr::core::vector3df(0.5f, 0.5f, -0.5f)) * _scale);
                    powerupNode->setID(powerup.getId());
                    _scaleNode(powerupNode);
                    _powerups.push_back(powerupNode);
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
    // DRAW ALL
    ResourceManager::sceneManager()->drawAll();
    // MENU
    if (_isPaused) {
        if (_menuResume->isPressed()) {
            _isPaused = false;
            _echapTimer = -1;
        } else if (_menuSave->isPressed()) {
            _isPaused = false;
            _echapTimer = -1;
        } else if (_menuSettings->isPressed()) {
            _isPaused = false;
            _echapTimer = -1;
        } else if (_menuQuit->isPressed()) {
            menuState = MENUMAINPAGE;
            unsetScene();
            return 1;
        }
        _drawMenu();
        ResourceManager::guiEnvironment()->drawAll();
    }
    // CHECK FOR PAUSE MENU
    if (ResourceManager::eventHandler().isKeyDown(irr::KEY_ESCAPE)) {
        if (_echapTimer) {
            _echapTimer = !_echapTimer;
            _isPaused = !_isPaused;
        }
    } else {
        if (!_echapTimer) {
            _echapTimer = !_echapTimer;
        }
    }
    ResourceManager::videoDriver()->endScene();
    return 2;
}

void SceneGame::unsetScene() {
    _isPaused = false;
    _players.clear();
    _boxes.clear();
    _powerups.clear();
    _walls.clear();
    _bombs.clear();
    _explosions.clear();
    _camera->remove();
    ResourceManager::device()->getGUIEnvironment()->clear();
    ResourceManager::device()->getSceneManager()->clear();
}

void SceneGame::_drawMenu() const {
    _menuBg->draw();
    _menuResume->draw();
    _menuQuit->draw();
    _menuSave->draw();
    _menuSettings->draw();
}