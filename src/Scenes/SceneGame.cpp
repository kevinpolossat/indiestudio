//
// Created by vincent on 5/15/17.
//

#include <Settings.hh>
#include <Save.hh>
#include "Spawn.hh"
#include "Explosion.hh"
#include "SceneGame.hh"
#include "Save.hh"

SceneGame::SceneGame()
        : _mode(GAME),
          _threadPool(4),
          _scale(2.f, 2.f, 2.f),
          _map(ResourceManager::assets_rela + "maps/Basic.map"),
          _referee(_map, 4, true),
          _echapTimer(-1) {
    ResourceManager::loadAnimatedMesh("box.obj", ResourceManager::assets_rela + "box/");
    ResourceManager::loadAnimatedMesh("wall.obj", ResourceManager::assets_rela + "wall/");
    ResourceManager::loadAnimatedMesh("CryoMine.obj", ResourceManager::assets_rela + "bomb/CryoMineGlove/");
    ResourceManager::loadAnimatedMesh("powerup_capacity.obj", ResourceManager::assets_rela + "powerup/");
    ResourceManager::loadAnimatedMesh("powerup_shortfuse.obj", ResourceManager::assets_rela + "powerup/");
    ResourceManager::loadAnimatedMesh("powerup_speed.obj", ResourceManager::assets_rela + "powerup/");
    ResourceManager::loadAnimatedMesh("powerup_strength.obj", ResourceManager::assets_rela + "powerup/");
    ResourceManager::loadAnimatedMesh("city.obj", ResourceManager::assets_rela + "city/");
    this->_HUD = ResourceManager::videoDriver()->getTexture((ResourceManager::assets_rela + "HUD.png").c_str());
    this->_deadBlue = ResourceManager::videoDriver()->getTexture((ResourceManager::assets_rela + "playerBlue_dead.png").c_str());
    this->_deadOrange = ResourceManager::videoDriver()->getTexture((ResourceManager::assets_rela + "playerOrange_dead.png").c_str());
    this->_deadGreen = ResourceManager::videoDriver()->getTexture((ResourceManager::assets_rela + "playerGreen_dead.png").c_str());
    this->_deadPurple = ResourceManager::videoDriver()->getTexture((ResourceManager::assets_rela + "playerPurple_dead.png").c_str());
    this->_numbers.push_back(ResourceManager::videoDriver()->getTexture((ResourceManager::assets_rela + "numbers/0.png").c_str()));
    this->_numbers.push_back(ResourceManager::videoDriver()->getTexture((ResourceManager::assets_rela + "numbers/1.png").c_str()));
    this->_numbers.push_back(ResourceManager::videoDriver()->getTexture((ResourceManager::assets_rela + "numbers/2.png").c_str()));
    this->_numbers.push_back(ResourceManager::videoDriver()->getTexture((ResourceManager::assets_rela + "numbers/3.png").c_str()));
    this->_numbers.push_back(ResourceManager::videoDriver()->getTexture((ResourceManager::assets_rela + "numbers/4.png").c_str()));
    this->_numbers.push_back(ResourceManager::videoDriver()->getTexture((ResourceManager::assets_rela + "numbers/5.png").c_str()));
    this->_numbers.push_back(ResourceManager::videoDriver()->getTexture((ResourceManager::assets_rela + "numbers/6.png").c_str()));
    this->_numbers.push_back(ResourceManager::videoDriver()->getTexture((ResourceManager::assets_rela + "numbers/7.png").c_str()));
    this->_numbers.push_back(ResourceManager::videoDriver()->getTexture((ResourceManager::assets_rela + "numbers/8.png").c_str()));
    this->_numbers.push_back(ResourceManager::videoDriver()->getTexture((ResourceManager::assets_rela + "numbers/9.png").c_str()));
    this->_numbers.push_back(ResourceManager::videoDriver()->getTexture((ResourceManager::assets_rela + "numbers/10.png").c_str()));
#ifdef SOUND
    ResourceManager::loadSound("Boom.ogg");
    ResourceManager::loadSound("Dead.ogg");
    ResourceManager::loadSound("Lose.ogg");
    ResourceManager::loadSound("Win.ogg");
#endif
}

SceneGame::~SceneGame() {
}

bool SceneGame::setScene() {
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
    this->_idx = 0;
    if (Settings::refereePath().size()) {
        Referee ref;
        Save::load(ref, Settings::refereePath());
        this->_referee = ref;
        for (auto const & player : _referee.getCharacters()) {
            if (player.getId() == 0 || (player.getId() == 1 && !_referee.getP2IsAI())) {
                _players.push_back(std::make_shared<Player>(Player(player.getId(), {irr::KEY_UP , irr::KEY_RIGHT, irr::KEY_DOWN, irr::KEY_LEFT, irr::KEY_END}, _scale)));
            } else {
                _players.push_back(std::make_shared<IA>(IA(player.getId(), _scale)));
            }
        }
    } else {
        _map.clearMap();
        _map.loadFromFile(ResourceManager::assets_rela + "maps/Basic.map");
        _referee = Referee(_map, 4, Settings::p2isAI());
        for (auto const & spawn : _referee.getMap().getSpawns()) {
            _specialEffectManager.addEffect<Spawn>(spawn.getPosition() * _scale, 20);
        }
        _players.push_back(std::make_shared<Player>(Player(0, {irr::KEY_UP , irr::KEY_RIGHT, irr::KEY_DOWN, irr::KEY_LEFT, irr::KEY_END}, _scale)));
        if (Settings::p2isAI()) {
            _players.push_back(std::make_shared<IA>(IA(1, _scale)));
        } else {
            _players.push_back(std::make_shared<Player>(Player(1, {irr::KEY_KEY_Z , irr::KEY_KEY_D, irr::KEY_KEY_S, irr::KEY_KEY_Q, irr::KEY_SPACE}, _scale)));
        }
        _players.push_back(std::make_shared<IA>(IA(2, _scale)));
        _players.push_back(std::make_shared<IA>(IA(3, _scale)));
    }
    for (auto & player : _players) {
        player->getNode().init(player->getId());
    }
    _createGround();
    _createWalls();
    _createBoxes();
    _camera = ResourceManager::sceneManager()->addCameraSceneNode(
            0,
            _scale * irr::core::vector3df(7.f, 13.f, 9.5),
            _scale * irr::core::vector3df(7.f, 0.f, 6.5f));
//    irr::SKeyMap keyMap[8];
//    keyMap[0].Action = irr::EKA_MOVE_FORWARD;
//    keyMap[0].KeyCode = irr::KEY_UP;
//
//    keyMap[1].Action = irr::EKA_MOVE_BACKWARD;
//    keyMap[1].KeyCode = irr::KEY_DOWN;
//
//    keyMap[2].Action = irr::EKA_STRAFE_LEFT;
//    keyMap[2].KeyCode = irr::KEY_LEFT;
//
//    keyMap[3].Action = irr::EKA_STRAFE_RIGHT;
//    keyMap[3].KeyCode = irr::KEY_RIGHT;
//    _camera = ResourceManager::sceneManager()->addCameraSceneNodeFPS(0, 100, 0.5f, -1, keyMap, 4);
    int verticalSize = 100;
    int horizontalSize = 500 - 100;
    float verticalPadding = (1080 - 400 - (verticalSize * 4)) / 5;
//    float horizontalPadding = 50;
    _menuBg = ResourceManager::device()->getGUIEnvironment()->addButton( irr::core::rect<irr::s32>(710, 200, 500 + 710, 1080 - 200), 0, -1, NULL);
    _menuBg->setImage(ResourceManager::device()->getVideoDriver()->getTexture((ResourceManager::assets_rela + "BG.png").c_str()));
    _menuBg->setUseAlphaChannel(true);
    _menuBg->setDrawBorder(false);
    _menuBg->setEnabled(false);

    _menuResume = ResourceManager::guiEnvironment()->addButton(irr::core::rect<irr::s32>(760 , 200 + verticalPadding, 760 + horizontalSize, 200 + verticalPadding + verticalSize), 0, 42, NULL);
    _menuResume->setImage(ResourceManager::device()->getVideoDriver()->getTexture((ResourceManager::assets_rela + "Fonts/ResumeFat_400x100.png").c_str()));
    _menuResume->setUseAlphaChannel(true);
    _menuResume->setDrawBorder(false);

    _menuSave = ResourceManager::guiEnvironment()->addButton(irr::core::rect<irr::s32>(760 , 1080 / 2 - verticalSize / 2, 760 + horizontalSize, 1080 / 2 + verticalSize / 2), 0, 42, NULL);
    _menuSave->setImage(ResourceManager::device()->getVideoDriver()->getTexture((ResourceManager::assets_rela + "Fonts/Save_400x100.png").c_str()));
    _menuSave->setUseAlphaChannel(true);
    _menuSave->setDrawBorder(false);

    _menuQuit = ResourceManager::guiEnvironment()->addButton(irr::core::rect<irr::s32>(760 , 200 + verticalSize * 3 + verticalPadding * 4, 760 + horizontalSize, 200 + verticalSize * 4 + verticalPadding * 4), 0, 42, NULL);
    _menuQuit->setImage(ResourceManager::device()->getVideoDriver()->getTexture((ResourceManager::assets_rela + "Fonts/Exit_400x100.png").c_str()));
    _menuQuit->setUseAlphaChannel(true);
    _menuQuit->setDrawBorder(false);

    _win = ResourceManager::device()->getVideoDriver()->getTexture((ResourceManager::assets_rela + "win.png").c_str());
    _lose = ResourceManager::device()->getVideoDriver()->getTexture((ResourceManager::assets_rela + "lose.png").c_str());
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
        for (auto const & box : _referee.getMap().getBoxes()) {
            boxNode = ResourceManager::sceneManager()->addOctreeSceneNode(boxMesh->getMesh(0));
            if (boxNode) {
                boxNode->setMaterialFlag(irr::video::EMF_LIGHTING, true);
                boxNode->setMaterialTexture(0, ResourceManager::videoDriver()->getTexture((ResourceManager::assets_rela + "box/SciFiCrateTextures/SciFiCrate-Emit.png").c_str()));
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
                wallNode->setMaterialTexture(0, ResourceManager::videoDriver()->getTexture((ResourceManager::assets_rela + "box/SciFiCrateTextures/SciFiCrate1-AO.png").c_str()));
                _scaleNode(wallNode);
                _walls.push_back(wallNode);
            }
        }
    }
}

void SceneGame::_createGround() {
    irr::scene::IAnimatedMesh * groundMesh = ResourceManager::getAnimatedMesh("city.obj");
    irr::scene::ISceneNode *    groundNode = nullptr;
    if (groundMesh) {
        groundMesh->setMaterialFlag(irr::video::EMF_LIGHTING, false);
        groundNode = ResourceManager::sceneManager()->addOctreeSceneNode(groundMesh->getMesh(0));
        if (groundNode) {
            groundNode->setMaterialTexture(0, ResourceManager::videoDriver()->getTexture((ResourceManager::assets_rela + "city/textures/diffuse_map.jpg").c_str()));
            groundNode->setPosition(irr::core::vector3df(-7, -131.5f, -41));
            groundNode->setScale(irr::core::vector3df(0.3, 0.3, 0.3));
//            _ground = groundNode;
        }
    }
}

int SceneGame::refresh(int &menuState) {
    auto firstController = ResourceManager::eventHandler().getJoystick(ResourceManager::getControllers()[0]);
    int ret;
//    if (ResourceManager::eventHandler().isKeyDown(irr::KEY_LEFT)) {
//        _ground->setPosition(_ground->getPosition() + irr::core::vector3df(-1, 0, 0));
//    }
//    if (ResourceManager::eventHandler().isKeyDown(irr::KEY_RIGHT)) {
//        _ground->setPosition(_ground->getPosition() + irr::core::vector3df(1, 0, 0));
//    }
//    if (ResourceManager::eventHandler().isKeyDown(irr::KEY_UP)) {
//        _ground->setPosition(_ground->getPosition() + irr::core::vector3df(0, 0, -1));
//    }
//    if (ResourceManager::eventHandler().isKeyDown(irr::KEY_DOWN)) {
//        _ground->setPosition(_ground->getPosition() + irr::core::vector3df(0, 0, 1));
//    }
//    if (ResourceManager::eventHandler().isKeyDown(irr::KEY_KEY_A)) {
//        _ground->setPosition(_ground->getPosition() + irr::core::vector3df(0, 1, 0));
//    }
//    if (ResourceManager::eventHandler().isKeyDown(irr::KEY_KEY_Q)) {
//        _ground->setPosition(_ground->getPosition() + irr::core::vector3df(0, -1, 0));
//    }
//    std::cout << _ground->getPosition().X << " " << _ground->getPosition().Y << " " << _ground->getPosition().Z << std::endl;
    switch (_mode) {
        case PAUSE:
            ResourceManager::sceneManager()->drawAll();
            ret = _pauseMode(menuState);
//            ResourceManager::guiEnvironment()->drawAll();
            if (ret) {
                return ret;
            }
            break;
        case GAME:
            _gameMode();
            break;
        case END:
            ResourceManager::sceneManager()->drawAll();
            ret = _endMode();
            if (ret) {
                menuState = MENUMAINPAGE;
                unsetScene();
                return 1;
            }
            break;
    }
    // CHECK FOR PAUSE MENU
    if (_mode != END && (ResourceManager::eventHandler().isKeyDown(irr::KEY_ESCAPE) || firstController.ButtonStates == 512)) {
        if (_echapTimer) {
            _echapTimer = !_echapTimer;
            _mode = _mode == GAME ? PAUSE : GAME;
        }
    } else {
        if (!_echapTimer) {
            _echapTimer = !_echapTimer;
        }
    }
    ResourceManager::videoDriver()->endScene();
    return 2;
}

int SceneGame::_pauseMode(int &menuState) {
    auto firstController = ResourceManager::eventHandler().getJoystick(ResourceManager::getControllers()[0]);
    if (_menuResume->isPressed() || (_idx == 0 && ResourceManager::eventHandler().isKeyDown(irr::KEY_RETURN))) {
        _mode = GAME;
        _echapTimer = -1;
    } else if (_menuSave->isPressed() || (_idx == 1 && ResourceManager::eventHandler().isKeyDown(irr::KEY_RETURN))) {
        //ResourceManager::device()->getGUIEnvironment()->clear();
        //ResourceManager::guiEnvironment()->drawAll();
        Save::save(this->_referee);
        _echapTimer = -1;
    } else if (_menuQuit->isPressed() || (_idx == 2 && ResourceManager::eventHandler().isKeyDown(irr::KEY_RETURN))) {
        menuState = MENUMAINPAGE;
        unsetScene();
        return 1;
    } else if (ResourceManager::eventHandler().isKeyDown(irr::KEY_DOWN) || firstController.Axis[1] > 0) {
        _idx += 1;
        if (_idx > 2)
            _idx = 0;
    } else if (ResourceManager::eventHandler().isKeyDown(irr::KEY_UP) || firstController.Axis[1] < 0) {
        _idx -= 1;
        if (_idx < 0)
            _idx = 2;
    }
    _drawMenu();
    return 0;
}

void SceneGame::_gameMode() {
    _specialEffectManager.refresh();
    int before = _players.size();
    _players.erase(std::remove_if(_players.begin(), _players.end(), [&](auto & player) {
        return std::find_if(_referee.getCharacters().begin(), _referee.getCharacters().end(), [&player](Character const & c) -> bool { return c.getId() == player->getId();}) == _referee.getCharacters().end();
    }), _players.end());
    int after = _players.size();
    if (before - after > 0) {
        this->_soundDead.play();
    }
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
                    this->_soundBoom.play();
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
    if (_players.size() < 2) {
        _mode = END;
        ResourceManager::eventHandler().resetLastKeyPressed();
    }
    auto characters = this->_referee.getCharacters();
    std::array<std::array<int, 4>, 4> players;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            players[i][j] = 0;
        }
    }
    std::array<int, 4>  alive = {0};
    for (auto c : characters) {
        players[c.getId()][0] = c.getCapacity();
        players[c.getId()][1] = c.getPower();
        players[c.getId()][2] = c.getSpeedTaken();
        players[c.getId()][3] = c.getFuseTaken();
        alive[c.getId()] = 1;
    }
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (players[i][j] > 10)
                players[i][j] = 10;
        }
    }
    ResourceManager::sceneManager()->drawAll();
    ResourceManager::videoDriver()->draw2DImage(this->_HUD, irr::core::position2d<irr::s32>(0, 0),
                                                irr::core::rect<irr::s32>(0, 0, 1920, 1030), 0,
                                                irr::video::SColor(255, 255, 255, 255), true);
    if (!alive[0]) {
        ResourceManager::videoDriver()->draw2DImage(this->_deadBlue, irr::core::position2d<irr::s32>(0, 0),
                                                    irr::core::rect<irr::s32>(0, 0, 100, 199), 0,
                                                    irr::video::SColor(255, 255, 255, 255), true);
    }
    if (!alive[1]) {
        ResourceManager::videoDriver()->draw2DImage(this->_deadOrange, irr::core::position2d<irr::s32>(1819, 0),
                                                    irr::core::rect<irr::s32>(0, 0, 100, 199), 0,
                                                    irr::video::SColor(255, 255, 255, 255), true);
    }
    if (!alive[2]) {
        ResourceManager::videoDriver()->draw2DImage(this->_deadGreen, irr::core::position2d<irr::s32>(0, 798),
                                                    irr::core::rect<irr::s32>(0, 0, 100, 199), 0,
                                                    irr::video::SColor(255, 255, 255, 255), true);
    }
    if (!alive[3]) {
        ResourceManager::videoDriver()->draw2DImage(this->_deadPurple, irr::core::position2d<irr::s32>(1820, 799),
                                                    irr::core::rect<irr::s32>(0, 0, 100, 199), 0,
                                                    irr::video::SColor(255, 255, 255, 255), true);
    }
    ResourceManager::videoDriver()->draw2DImage(this->_numbers[players[0][0]], irr::core::position2d<irr::s32>(137, 11),
                                                irr::core::rect<irr::s32>(0, 0, 50, 50), 0,
                                                irr::video::SColor(255, 255, 255, 255), true);
    ResourceManager::videoDriver()->draw2DImage(this->_numbers[players[0][1]], irr::core::position2d<irr::s32>(137, 54),
                                                irr::core::rect<irr::s32>(0, 0, 50, 50), 0,
                                                irr::video::SColor(255, 255, 255, 255), true);
    ResourceManager::videoDriver()->draw2DImage(this->_numbers[players[0][2]], irr::core::position2d<irr::s32>(137, 95),
                                                irr::core::rect<irr::s32>(0, 0, 50, 50), 0,
                                                irr::video::SColor(255, 255, 255, 255), true);
    ResourceManager::videoDriver()->draw2DImage(this->_numbers[players[0][3]], irr::core::position2d<irr::s32>(137, 137),
                                                irr::core::rect<irr::s32>(0, 0, 50, 50), 0,
                                                irr::video::SColor(255, 255, 255, 255), true);

    ResourceManager::videoDriver()->draw2DImage(this->_numbers[players[1][0]], irr::core::position2d<irr::s32>(1735, 11),
                                                irr::core::rect<irr::s32>(0, 0, 50, 50), 0,
                                                irr::video::SColor(255, 255, 255, 255), true);
    ResourceManager::videoDriver()->draw2DImage(this->_numbers[players[1][1]], irr::core::position2d<irr::s32>(1735, 54),
                                                irr::core::rect<irr::s32>(0, 0, 50, 50), 0,
                                                irr::video::SColor(255, 255, 255, 255), true);
    ResourceManager::videoDriver()->draw2DImage(this->_numbers[players[1][2]], irr::core::position2d<irr::s32>(1735, 95),
                                                irr::core::rect<irr::s32>(0, 0, 50, 50), 0,
                                                irr::video::SColor(255, 255, 255, 255), true);
    ResourceManager::videoDriver()->draw2DImage(this->_numbers[players[1][3]], irr::core::position2d<irr::s32>(1735, 137),
                                                irr::core::rect<irr::s32>(0, 0, 50, 50), 0,
                                                irr::video::SColor(255, 255, 255, 255), true);

    ResourceManager::videoDriver()->draw2DImage(this->_numbers[players[2][0]], irr::core::position2d<irr::s32>(137, 825),
                                                irr::core::rect<irr::s32>(0, 0, 50, 50), 0,
                                                irr::video::SColor(255, 255, 255, 255), true);
    ResourceManager::videoDriver()->draw2DImage(this->_numbers[players[2][1]], irr::core::position2d<irr::s32>(137, 868),
                                                irr::core::rect<irr::s32>(0, 0, 50, 50), 0,
                                                irr::video::SColor(255, 255, 255, 255), true);
    ResourceManager::videoDriver()->draw2DImage(this->_numbers[players[2][2]], irr::core::position2d<irr::s32>(137, 909),
                                                irr::core::rect<irr::s32>(0, 0, 50, 50), 0,
                                                irr::video::SColor(255, 255, 255, 255), true);
    ResourceManager::videoDriver()->draw2DImage(this->_numbers[players[2][3]], irr::core::position2d<irr::s32>(137, 951),
                                                irr::core::rect<irr::s32>(0, 0, 50, 50), 0,
                                                irr::video::SColor(255, 255, 255, 255), true);

    ResourceManager::videoDriver()->draw2DImage(this->_numbers[players[3][0]], irr::core::position2d<irr::s32>(1735, 825),
                                                irr::core::rect<irr::s32>(0, 0, 50, 50), 0,
                                                irr::video::SColor(255, 255, 255, 255), true);
    ResourceManager::videoDriver()->draw2DImage(this->_numbers[players[3][1]], irr::core::position2d<irr::s32>(1735, 868),
                                                irr::core::rect<irr::s32>(0, 0, 50, 50), 0,
                                                irr::video::SColor(255, 255, 255, 255), true);
    ResourceManager::videoDriver()->draw2DImage(this->_numbers[players[3][2]], irr::core::position2d<irr::s32>(1735, 909),
                                                irr::core::rect<irr::s32>(0, 0, 50, 50), 0,
                                                irr::video::SColor(255, 255, 255, 255), true);
    ResourceManager::videoDriver()->draw2DImage(this->_numbers[players[3][3]], irr::core::position2d<irr::s32>(1735, 951),
                                                irr::core::rect<irr::s32>(0, 0, 50, 50), 0,
                                                irr::video::SColor(255, 255, 255, 255), true);

}

int SceneGame::_endMode() {
    // DRAW SCREEN
    irr::video::ITexture * screen = NULL;
    if (_players.size()) {
        screen = _players[0]->isHuman() ? _win : _lose;
    } else {
        screen = _lose;

    }
    ResourceManager::videoDriver()->draw2DImage(screen, irr::core::position2d<irr::s32>(0, 0),
                                                irr::core::rect<irr::s32>(0, 0, 1920, 1080), 0,
                                                irr::video::SColor(255, 255, 255, 255), true);
#ifdef SOUND
    if (!this->_once) {
        if (screen == _win) {
            this->_soundWin.play();
        } else {
            this->_soundLose.play();
        }
        _once = true;
    }
#endif    // CHECK QUIT
    if (ResourceManager::eventHandler().getKeyPressed() != irr::KEY_CANCEL ||
        ResourceManager::eventHandler().getJoystick(ResourceManager::getControllers()[0]).ButtonStates) {
        return 1;
    }
    return 0;
}

void SceneGame::unsetScene() {
    _mode = GAME;
    _players.clear();
    _boxes.clear();
    _powerups.clear();
    _walls.clear();
    _bombs.clear();
    _specialEffectManager.clear();
    _camera->remove();
    ResourceManager::device()->getGUIEnvironment()->clear();
    ResourceManager::device()->getSceneManager()->clear();
}

void SceneGame::_drawMenu() const {
    _menuBg->draw();
    if (!_idx) {
        _menuResume->setImage(ResourceManager::device()->getVideoDriver()->getTexture((ResourceManager::assets_rela + "Fonts/ResumeFat_400x100.png").c_str()));
        _menuSave->setImage(ResourceManager::device()->getVideoDriver()->getTexture((ResourceManager::assets_rela + "Fonts/Save_400x100.png").c_str()));
        _menuQuit->setImage(ResourceManager::device()->getVideoDriver()->getTexture((ResourceManager::assets_rela + "Fonts/Exit_400x100.png").c_str()));
        _menuQuit->setUseAlphaChannel(true);
    } else if (_idx == 1) {
        _menuResume->setImage(ResourceManager::device()->getVideoDriver()->getTexture((ResourceManager::assets_rela + "Fonts/Resume_400x100.png").c_str()));
        _menuSave->setImage(ResourceManager::device()->getVideoDriver()->getTexture((ResourceManager::assets_rela + "Fonts/SaveFat_400x100.png").c_str()));
        _menuQuit->setImage(ResourceManager::device()->getVideoDriver()->getTexture((ResourceManager::assets_rela + "Fonts/Exit_400x100.png").c_str()));
    } else {
        _menuResume->setImage(ResourceManager::device()->getVideoDriver()->getTexture((ResourceManager::assets_rela + "Fonts/Resume_400x100.png").c_str()));
        _menuSave->setImage(ResourceManager::device()->getVideoDriver()->getTexture((ResourceManager::assets_rela + "Fonts/Save_400x100.png").c_str()));
        _menuQuit->setImage(ResourceManager::device()->getVideoDriver()->getTexture((ResourceManager::assets_rela + "Fonts/ExitFat_400x100.png").c_str()));
    }
    _menuResume->draw();
    _menuQuit->draw();
    _menuSave->draw();
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
            powerupNode->setPosition((powerup.getPosition() + irr::core::vector3df(0, 0.5f, 0)) * _scale);
            powerupNode->addAnimator(ResourceManager::sceneManager()->createFlyStraightAnimator(powerupNode->getPosition(), powerupNode->getPosition() + irr::core::vector3df(0, 1.f, 0), 2000, true, true));
//            powerupNode->addAnimator(ResourceManager::sceneManager()->createRotationAnimator(irr::core::vector3df(0, 0, 1)));
            powerupNode->setRotation(irr::core::vector3df(-45, 0, 0));
            powerupNode->setID(powerup.getId());
            _scaleNode(powerupNode);
            _powerups.push_back(PowerUpNode(powerupNode));
        }
    }
}
