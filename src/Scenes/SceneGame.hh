//
// Created by vincent on 5/15/17.
//

#ifndef INDIESTUDIO_SCENEGAME_HH
#define INDIESTUDIO_SCENEGAME_HH

#include <ThreadPool.hh>
#include "PowerUpNode.hh"
#include "IScene.hh"
#include "Player.hh"
#include "Map.hh"
#include "Referee.hh"
#include "IA.hh"
#include "SpecialEffectManager.hh"

class                                   SceneGame : public IScene {
public:
    explicit SceneGame();
    virtual ~SceneGame();

    SceneGame(SceneGame const & other)              = delete;
    SceneGame(SceneGame && other)                   = delete;
    SceneGame &operator = (SceneGame const & other) = delete;

    bool                                setScene();
    int                                 refresh(int & id);
    void                                unsetScene();
    irr::gui::IGUIButton                * _bg;

private:
    void                                  _createWalls();
    void                                  _createGround();
    void                                  _createBoxes();
    void                                  _scaleNode(irr::scene::ISceneNode * node);
    void                                  _drawMenu() const;

    void                                  _addPowerUp(PowerUp const & powerup);

    irr::core::vector3df                  _scale;
    std::vector<std::shared_ptr<IPlayer>> _players;
    irr::scene::ICameraSceneNode *        _camera;
    Map                                   _map;
    Referee                               _referee;
    std::vector<irr::scene::ISceneNode *> _boxes;
    std::vector<irr::scene::ISceneNode *> _walls;
    std::vector<irr::scene::ISceneNode *> _bombs;
    std::vector<PowerUpNode>              _powerups;
    bool                                  _isPaused;
    bool                                  _echapTimer;

    irr::gui::IGUIButton *                _menuBg;
    irr::gui::IGUIButton *                _menuResume;
    irr::gui::IGUIButton *                _menuSave;
    irr::gui::IGUIButton *                _menuSettings;
    irr::gui::IGUIButton *                _menuQuit;

    SpecialEffectManager                  _specialEffectManager;
    std::unique_ptr<ThreadPool>           _th;
};


#endif //INDIESTUDIO_SCENEGAME_HH
