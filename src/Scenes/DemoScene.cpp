//
// Created by vincent on 6/18/17.
//

#include <IA.hh>
#include <Player.hh>
#include "DemoScene.hh"

DemoScene::DemoScene()
        : _threadPool(4),
          _scale(2.f, 2.f, 2.f),
          _map(ResourceManager::assets_rela + "maps/Basic.map"),
          _referee(_map, 4, true) {
    ResourceManager::loadAnimatedMesh("box.obj", ResourceManager::assets_rela + "box/");
    ResourceManager::loadAnimatedMesh("wall.obj", ResourceManager::assets_rela + "wall/");
    ResourceManager::loadAnimatedMesh("CryoMine.obj", ResourceManager::assets_rela + "bomb/");
    ResourceManager::loadAnimatedMesh("powerup_capacity.obj", ResourceManager::assets_rela + "powerup/");
    ResourceManager::loadAnimatedMesh("powerup_shortfuse.obj", ResourceManager::assets_rela + "powerup/");
    ResourceManager::loadAnimatedMesh("powerup_speed.obj", ResourceManager::assets_rela + "powerup/");
    ResourceManager::loadAnimatedMesh("powerup_strength.obj", ResourceManager::assets_rela + "powerup/");
    ResourceManager::loadAnimatedMesh("city.obj", ResourceManager::assets_rela + "city/");
    ResourceManager::loadAnimatedMesh("ground.obj", ResourceManager::assets_rela + "ground/");
#ifdef SOUND
    ResourceManager::loadSound("Boom.ogg");
    ResourceManager::loadSound("Dead.ogg");
    ResourceManager::loadSound("Lose.ogg");
    ResourceManager::loadSound("Win.ogg");
    ResourceManager::loadSound("DiscWars.ogg");
#endif
}

DemoScene::~DemoScene() {
}

bool DemoScene::setScene() {
#ifdef SOUND
    this->_once = false;
    this->_soundBoom.setBuffer(ResourceManager::getSound("Boom.ogg"));
    this->_soundBoom.setVolume(Settings::sound_volume() * 10);
    this->_soundLose.setBuffer(ResourceManager::getSound("Lose.ogg"));
    this->_soundLose.setVolume(Settings::sound_volume() * 10);
    this->_soundDead.setBuffer(ResourceManager::getSound("Dead.ogg"));
    this->_soundDead.setVolume(Settings::sound_volume() * 10);
    this->_soundWin.setBuffer(ResourceManager::getSound("Win.ogg"));
    this->_soundWin.setVolume(Settings::sound_volume() * 10);
    this->_music.setBuffer(ResourceManager::getSound("DiscWars.ogg"));
    this->_music.setVolume(Settings::music_volume() * 10);
    this->_music.setLoop(true);
    this->_music.play();
#endif
    ResourceManager::sceneManager()->setAmbientLight(irr::video::SColorf(1.0,1.0,1.0,0.0));
    ResourceManager::sceneManager()->addLightSceneNode (0, irr::core::vector3df(7.f, 100.f, 11.5f) * _scale,
                                                        irr::video::SColorf(0.01f,0.01f,0.01f,0.0f), 5.0f);
    ResourceManager::sceneManager()->addSkyBoxSceneNode(
            ResourceManager::videoDriver()->getTexture((ResourceManager::assets_rela + "spacebox/Up_1K_TEX0.png").c_str()),
            ResourceManager::videoDriver()->getTexture((ResourceManager::assets_rela + "spacebox/Down_1K_TEX0.png").c_str()),
            ResourceManager::videoDriver()->getTexture((ResourceManager::assets_rela + "spacebox/Left_1K_TEX0.png").c_str()),
            ResourceManager::videoDriver()->getTexture((ResourceManager::assets_rela + "spacebox/Right_1K_TEX0.png").c_str()),
            ResourceManager::videoDriver()->getTexture((ResourceManager::assets_rela + "spacebox/Back_1K_TEX0.png").c_str()),
            ResourceManager::videoDriver()->getTexture((ResourceManager::assets_rela + "spacebox/Front_1K_TEX0.png").c_str())
    );
    for (auto const & spawn : _referee.getMap().getSpawns()) {
        _specialEffectManager.addEffect<Spawn>(spawn.getPosition() * _scale, 20);
    }
    _players.push_back(std::make_shared<IA>(IA(0, _scale, 3)));
    _players.push_back(std::make_shared<IA>(IA(1, _scale, 3)));
    _players.push_back(std::make_shared<IA>(IA(2, _scale, 3)));
    _players.push_back(std::make_shared<IA>(IA(3, _scale, 3)));

    for (auto & player : _players) {
        player->getNode().init(player->getId());
    }
    _createGround();
    _createWalls();
    _createBoxes();

    _camera = ResourceManager::sceneManager()->addCameraSceneNode(
            0,
            _scale * irr::core::vector3df(7.f, 13.f, 9.5f),
            _scale * irr::core::vector3df(7.f, 0.f, 6.5f));
    return true;
}

void DemoScene::_scaleNode(irr::scene::ISceneNode *node) {
    irr::core::vector3df boundingBox = node->getBoundingBox().getExtent();
    float maxVal = std::max(boundingBox.X, std::max(boundingBox.Y, boundingBox.Z));
    node->setScale(_scale / maxVal);
}

void DemoScene::_createBoxes() {
    irr::scene::IAnimatedMesh * boxMesh = ResourceManager::getAnimatedMesh("box.obj");
    irr::scene::ISceneNode *    boxNode = nullptr;
    irr::core::array<irr::video::ITexture*> textures;
    textures.push_back(ResourceManager::videoDriver()->getTexture((ResourceManager::assets_rela + "box/SciFiCrateTextures/SciFiCrate-EmitRed.png").c_str()));
    textures.push_back(ResourceManager::videoDriver()->getTexture((ResourceManager::assets_rela + "box/SciFiCrateTextures/SciFiCrate-Emit.png").c_str()));
    if (boxMesh) {
        for (auto const & box : _referee.getMap().getBoxes()) {
            boxNode = ResourceManager::sceneManager()->addOctreeSceneNode(boxMesh->getMesh(0));
            if (boxNode) {
                boxNode->setMaterialFlag(irr::video::EMF_LIGHTING, true);
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

void DemoScene::_createWalls() {
    irr::scene::IAnimatedMesh * wallMesh = ResourceManager::getAnimatedMesh("wall.obj");
    irr::scene::IAnimatedMesh * groundMesh = ResourceManager::getAnimatedMesh("ground.obj");
    irr::scene::ISceneNode *    wallNode = nullptr;
    irr::scene::ISceneNode *    groundNode = nullptr;
    if (wallMesh) {
        for (Cell const & wall : _referee.getMap().getWalls()) {
            if (wall.getPosition().Y > 0) {
                wallNode = ResourceManager::sceneManager()->addOctreeSceneNode(wallMesh->getMesh(0));
                if (wallNode) {
                    wallNode->setMaterialFlag(irr::video::EMF_LIGHTING, true);
                    wallNode->setPosition(_scale * wall.getPosition());
                    _scaleNode(wallNode);
                    _walls.push_back(wallNode);
                }
            }
            if (groundMesh) {
                groundMesh->setMaterialFlag(irr::video::EMF_LIGHTING, false);
                groundNode = ResourceManager::sceneManager()->addOctreeSceneNode(groundMesh->getMesh(0));
                if (groundNode) {
                    groundNode->setMaterialTexture(0, ResourceManager::videoDriver()->getTexture((ResourceManager::assets_rela + "ground/ground.png").c_str()));
                    groundNode->setPosition(irr::core::vector3df(wall.getPosition().X * _scale.X, _scale.Y, wall.getPosition().Z * _scale.Z));
                    irr::core::vector3df boundingBox = groundNode->getBoundingBox().getExtent();
                    float maxVal = std::max(boundingBox.X, boundingBox.Z);
                    groundNode->setScale(_scale / maxVal);
                }
            }

        }
    }
}

void DemoScene::_createGround() {
    irr::scene::IAnimatedMesh * groundMesh = ResourceManager::getAnimatedMesh("city.obj");
    if (groundMesh) {
        groundMesh->setMaterialFlag(irr::video::EMF_LIGHTING, false);
        irr::scene::ISceneNode * groundNode = ResourceManager::sceneManager()->addOctreeSceneNode(groundMesh->getMesh(0));
        if (groundNode) {
            groundNode->setMaterialTexture(0, ResourceManager::videoDriver()->getTexture((ResourceManager::assets_rela + "city/textures/diffuse_map.jpg").c_str()));
            groundNode->setPosition(irr::core::vector3df(-7, -131.5f, -41));
            groundNode->setScale(irr::core::vector3df(0.3, 0.3, 0.3));
        }
    }
}

int DemoScene::refresh(int &menuState) {
    _specialEffectManager.refresh();
    int before = _players.size();
    _players.erase(std::remove_if(_players.begin(), _players.end(), [&](auto & player) {
        return std::find_if(_referee.getCharacters().begin(), _referee.getCharacters().end(), [&player](Character const & c) -> bool { return c.getId() == player->getId();}) == _referee.getCharacters().end();
    }), _players.end());
    int after = _players.size();
#ifdef SOUND
    if (before - after > 0) {
        this->_soundDead.play();
    }
#endif
    std::for_each(_players.begin(), _players.end(), [this](auto & player) {
        if (std::dynamic_pointer_cast<Player>(player)) {
            player->move(ResourceManager::eventHandler(), _referee);
        }
    });
    std::vector<std::future<Action>> _aiActions;
    for (auto & player : _players) {
        if (std::dynamic_pointer_cast<IA>(player)) {
            _aiActions.push_back(_threadPool.submit([&player, this]() -> Action {
                return player->move(ResourceManager::eventHandler(), _referee);
            }));
        }
    }
    std::for_each(_aiActions.begin(), _aiActions.end(), [this](auto & fa){
        auto a = fa.get();
        _referee.doAction(a); });
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
#ifdef SOUND
                this->_soundBoom.play();
#endif
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
                }
            }

        }
    }
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
    // CHANGE PLAYER POSITION
    for (auto & player : _players) {
        auto c = std::find_if(_referee.getCharacters().begin(), _referee.getCharacters().end(), [&player](Character const & character) -> bool { return character.getId() == player->getId();});
        if (c != _referee.getCharacters().end()) {
            player->getNode().setPosition(c->getPosition() * _scale);
        }
    }
    ResourceManager::sceneManager()->drawAll();
    ResourceManager::videoDriver()->endScene();
    if (ResourceManager::eventHandler().isAnyKeyPressed() ||
        ResourceManager::eventHandler().getJoystick(ResourceManager::getControllers()[0]).ButtonStates) {
        menuState = MENUMAINPAGE;
        unsetScene();
        return 1;
    }
    return 2;
}

void DemoScene::unsetScene() {
    _players.clear();
    _boxes.clear();
    _powerups.clear();
    _walls.clear();
    _bombs.clear();
    _specialEffectManager.clear();
    _camera->remove();
#ifdef SOUND
    _music.stop();
#endif
    ResourceManager::device()->getGUIEnvironment()->clear();
    ResourceManager::device()->getSceneManager()->clear();
}

void DemoScene::_addPowerUp(PowerUp const & powerup) {
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
            powerupNode->setPosition((powerup.getPosition() + irr::core::vector3df(0, 0.5f, 0)) * _scale);
            powerupNode->addAnimator(ResourceManager::sceneManager()->createFlyStraightAnimator(powerupNode->getPosition(), powerupNode->getPosition() + irr::core::vector3df(0, 1.f, 0), 2000, true, true));
            powerupNode->setRotation(irr::core::vector3df(-45, 0, 0));
            powerupNode->setID(powerup.getId());
            _scaleNode(powerupNode);
            _powerups.push_back(PowerUpNode(powerupNode));
        }
    }
}
