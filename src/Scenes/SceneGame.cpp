//
// Created by vincent on 5/15/17.
//

#include "Spawn.hh"
#include "Explosion.hh"
#include "SceneGame.hh"
#include "Save.hh"

SceneGame::SceneGame()
        : _scale(2.f, 2.f, 2.f),
          _map("./assets/maps/Basic.map"),
          _referee(_map, 4),
          _isPaused(false),
          _echapTimer(-1) {
    ResourceManager::loadAnimatedMesh("box.obj", "assets/box/");
    ResourceManager::loadAnimatedMesh("wall.obj", "assets/wall/");
    ResourceManager::loadAnimatedMesh("CryoMine.obj", "assets/bomb/CryoMineGlove/");
    ResourceManager::loadAnimatedMesh("powerup_capacity.obj", "assets/powerup/");
    ResourceManager::loadAnimatedMesh("powerup_shortfuse.obj", "assets/powerup/");
    ResourceManager::loadAnimatedMesh("powerup_speed.obj", "assets/powerup/");
    ResourceManager::loadAnimatedMesh("powerup_strength.obj", "assets/powerup/");
}

SceneGame::~SceneGame() {
}

bool SceneGame::setScene() {
    ResourceManager::sceneManager()->setAmbientLight(irr::video::SColorf(1.0,1.0,1.0,0.0));
    ResourceManager::sceneManager()->addLightSceneNode (0, irr::core::vector3df(7.f, 100.f, 11.5f) * _scale,
                                                        irr::video::SColorf(0.01f,0.01f,0.01f,0.0f), 5.0f);
    ResourceManager::sceneManager()->addSkyBoxSceneNode(
            ResourceManager::videoDriver()->getTexture("assets/spacebox/Up_1K_TEX0.png"),
            ResourceManager::videoDriver()->getTexture("assets/spacebox/Down_1K_TEX0.png"),
            ResourceManager::videoDriver()->getTexture("assets/spacebox/Left_1K_TEX0.png"),
            ResourceManager::videoDriver()->getTexture("assets/spacebox/Right_1K_TEX0.png"),
            ResourceManager::videoDriver()->getTexture("assets/spacebox/Back_1K_TEX0.png"),
            ResourceManager::videoDriver()->getTexture("assets/spacebox/Front_1K_TEX0.png")
    );
    _th = std::make_unique<ThreadPool>();
    _map.clearMap();
    _map.loadFromFile("./assets/maps/Basic.map");
    _referee = Referee(_map, 4);
    for (auto const & spawn : _referee.getMap().getSpawns()) {
        _specialEffectManager.addEffect<Spawn>(spawn.getPosition() * _scale, 20);
    }
    _players.push_back(std::make_shared<IA>(IA(0, _scale)));
//    _players.push_back(std::make_shared<IA>(IA(1, _scale)));
//    _players.push_back(std::make_shared<IA>(IA(2, _scale)));
    _players.push_back(std::make_shared<Player>(Player(1, {irr::KEY_UP , irr::KEY_RIGHT, irr::KEY_DOWN, irr::KEY_LEFT, irr::KEY_END}, _scale)));
    for (auto & player : _players) {
        player->getNode().init();
    }
//    _createGround();
    _createWalls();
    _createBoxes();
    _camera = ResourceManager::sceneManager()->addCameraSceneNode(
            0,
            _scale * irr::core::vector3df(7.f, 13.f, 9.5),
            _scale * irr::core::vector3df(7.f, 0.f, 6.5f));

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
    irr::core::array<irr::video::ITexture*> textures;
    textures.push_back(ResourceManager::videoDriver()->getTexture("assets/box/SciFiCrateTextures/SciFiCrate-EmitRed.png"));
    textures.push_back(ResourceManager::videoDriver()->getTexture("assets/box/SciFiCrateTextures/SciFiCrate-Emit.png"));
    irr::scene::IAnimatedMesh * boxMesh = ResourceManager::getAnimatedMesh("box.obj");
    irr::scene::ISceneNode *    boxNode = nullptr;
    if (boxMesh) {
        for (auto const & box : _referee.getMap().getBoxes()) {
            boxNode = ResourceManager::sceneManager()->addOctreeSceneNode(boxMesh->getMesh(0));
            if (boxNode) {
                boxNode->setMaterialFlag(irr::video::EMF_LIGHTING, true);
//                boxNode->setMaterialTexture(0, ResourceManager::videoDriver()->getTexture("assets/box/SciFiCrateTextures/SciFiCrate1-AO.png"));
//                boxNode->setMaterialTexture(1, ResourceManager::videoDriver()->getTexture("assets/box/SciFiCrateTextures/SciFiCrate-EmitRed.png"));
                boxNode->addAnimator(ResourceManager::sceneManager()->createTextureAnimator(textures, 1000, true));
                boxNode->setID(box.getId());
                boxNode->setPosition(_scale * box.getPosition());
                _scaleNode(boxNode);
                boxNode->setScale(irr::core::vector3df(0.8f, 1.f, 0.8f) * boxNode->getScale());
                _boxes.push_back(boxNode);
            }
        }
    }
}

void SceneGame::_createWalls() {
    irr::scene::IAnimatedMesh * wallMesh = ResourceManager::getAnimatedMesh("wall.obj");
    irr::scene::ISceneNode *    wallNode = nullptr;
    if (wallMesh) {
        for (auto const & wall : _referee.getMap().getWalls()) {
            wallNode = ResourceManager::sceneManager()->addOctreeSceneNode(wallMesh->getMesh(0));
            if (wallNode) {
                wallNode->setMaterialFlag(irr::video::EMF_LIGHTING, true);
                wallNode->setPosition(_scale * wall.getPosition());
                wallNode->setMaterialTexture(0, ResourceManager::videoDriver()->getTexture("assets/box/SciFiCrateTextures/SciFiCrate1-AO.png"));
                _scaleNode(wallNode);
                _walls.push_back(wallNode);
            }
        }
    }
}

void SceneGame::_createGround() {
    irr::scene::IAnimatedMesh * groundMesh = ResourceManager::getAnimatedMesh("asteroid.obj");
    irr::scene::ISceneNode *    groundNode = nullptr;
    if (groundMesh) {
        groundMesh->setMaterialFlag(irr::video::EMF_LIGHTING, false);
        groundNode = ResourceManager::sceneManager()->addOctreeSceneNode(groundMesh->getMesh(0));
        if (groundNode) {
            groundNode->setPosition(irr::core::vector3df(0, 0, 0));
//            groundNode->setScale(irr::core::vector3df(0.05f, 0.05f, 0.05f));
        }
    }
}

int SceneGame::refresh(int &menuState) {
    _specialEffectManager.refresh();
    _players.erase(std::remove_if(_players.begin(), _players.end(), [&](auto & player) {
        return std::find_if(_referee.getCharacters().begin(), _referee.getCharacters().end(), [&player](Character const & c) -> bool { return c.getId() == player->getId();}) == _referee.getCharacters().end();
    }), _players.end());

    std::vector<std::future<Action>>    AIActions;
    std::vector<Action>                 playerActions;
    for (auto & player : _players) {
        if (player) {
            IA *ai;
            if ((ai = dynamic_cast<IA *>(player.get()))) {
                AIActions.push_back(_th->submit([ai, this]() -> Action { return ai->move(ResourceManager::eventHandler(), _referee); }));
            }
            else {
                playerActions.push_back(player->move(ResourceManager::eventHandler(), _referee));
            }
        }
    }
    for (auto & async_a : AIActions) {
        auto a = async_a.get();
        _referee.doAction(a);
    }
    for (auto & a : playerActions) {
        _referee.doAction(a);
    }
    _referee.update(true, 1);
    // DELETE BOXES
    for (auto & node : _boxes) {
        if (node) {
            auto f = std::find_if(_referee.getMap().getBoxes().begin(), _referee.getMap().getBoxes().end(), [&node](Cell const & c){ return node->getID() == c.getId(); });
            if (f == _referee.getMap().getBoxes().end()) {
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
                _specialEffectManager.addEffect<Spawn>(bomb->getPosition(), 30);
                bomb->remove();
                bomb = nullptr;
            }
        }
    }
    // ADD NEW BOMB
    for (auto & bomb : _referee.getBombs()) {
        auto f = std::find_if(_bombs.begin(), _bombs.end(), [&bomb](auto node){ return node && node->getID() == bomb.getId(); });
        if (f == _bombs.end()) {
            irr::scene::IAnimatedMesh * bombMesh = ResourceManager::getAnimatedMesh("CryoMine.obj");
            irr::scene::ISceneNode *    bombNode = nullptr;
            if (bombMesh) {
                bombNode = ResourceManager::sceneManager()->addOctreeSceneNode(bombMesh->getMesh(0));
                if (bombNode) {
                    bombNode->setMaterialFlag(irr::video::EMF_LIGHTING, true);
                    bombNode->setPosition(bomb.getPosition() * _scale);
                    bombNode->setID(bomb.getId());
                    _scaleNode(bombNode);
                    bombNode->setScale(bombNode->getScale() * 1.5f);
                    _bombs.push_back(bombNode);
                    irr::core::vector3df effectPosition = bombNode->getPosition();
                    effectPosition.Y = effectPosition.Y + 2;
                    effectPosition.X = effectPosition.X;
                    _specialEffectManager.addEffect<InternalExplosion>(effectPosition, bomb.getTimer());
                }
            }

        }
    }
//    std::cout << "-------------------" << std::endl;
//    // REMOVE POWERUPS
//    std::cout << "ref : ";
//    for (auto & powerup : _referee.getBonuses()) {
//        std::cout << " " << powerup.getId();
//    }
//    std::cout << std::endl;
//    std::cout << "irr : ";
//    for (auto & powerup : _powerups) {
//        std::cout << " " << powerup.getId();
//    }
//    std::cout << std::endl;
    // ADD NEW POWERUPS
    for (auto const & pos : _referee.getExplosions())
        _specialEffectManager.addEffect<Spawn>(_scale * pos, 25, 1.0);
    for (auto & powerup : _referee.getBonuses()) {
        bool f = false;
        for (auto & node : _powerups) {
            f = f || node.getId() == powerup.getId();
        }
        if (!f) {
            _addPowerUp(powerup);
        }
    }
    for (auto & powerup : _powerups) {
        powerup.update(_referee.getBonuses(), _players);
    }
    _powerups.erase(std::remove_if(_powerups.begin(), _powerups.end(), [](PowerUpNode const & e){ return e.isToBeRemoved(); }), _powerups.end());
//    std::cout << "ref : ";
//    for (auto & powerup : _referee.getBonuses()) {
//        std::cout << " " << powerup.getId();
//    }
//    std::cout << std::endl;
//    std::cout << "irr : ";
//    for (auto & powerup : _powerups) {
//        std::cout << " " << powerup.getId();
//    }
//    std::cout << "-------------------" << std::endl;
    // CHANGE PLAYER POSITION
    for (auto & player : _players) {
        auto c = std::find_if(_referee.getCharacters().begin(), _referee.getCharacters().end(), [&player](Character const & character) -> bool { return character.getId() == player->getId();});
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
            //ResourceManager::device()->getGUIEnvironment()->clear();
            //ResourceManager::guiEnvironment()->drawAll();
            Save::save(this->_referee);
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
    _specialEffectManager.clear();
    _camera->remove();
    _th.reset();
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

void SceneGame::_addPowerUp(PowerUp const & powerup) {
    std::string powerUpName;
    switch (powerup.getType()) {
        case AEntity::SPEED:
            powerUpName = "speed";
            break ;
        case AEntity::STRENGTH:
            powerUpName = "strength";
            break ;
        case AEntity::SHORTFUSE:
            powerUpName = "shortfuse";
            break ;
        case AEntity::CAPACITY:
            powerUpName = "capacity";
            break ;
        default:
            throw std::runtime_error("The given power up is not taken into account");
    }
    irr::scene::IAnimatedMesh   *powerupMesh = ResourceManager::getAnimatedMesh("powerup_" + powerUpName + ".obj");
    irr::scene::ISceneNode      *powerupNode = nullptr;
    if (powerupMesh) {
        powerupNode = ResourceManager::sceneManager()->addOctreeSceneNode(powerupMesh->getMesh(0));
        if (powerupNode) {
            powerupNode->setMaterialFlag(irr::video::EMF_LIGHTING, true);
            powerupNode->addAnimator(ResourceManager::sceneManager()->createRotationAnimator(irr::core::vector3df(0, 1, 0)));
            powerupNode->setPosition((powerup.getPosition() + irr::core::vector3df(0, 0, 0)) * _scale);
            powerupNode->setID(powerup.getId());
            _scaleNode(powerupNode);
            _powerups.push_back(PowerUpNode(powerupNode));
        }
    }
}
