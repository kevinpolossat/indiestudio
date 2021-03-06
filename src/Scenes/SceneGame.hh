//
// Created by vincent on 5/15/17.
//

#ifndef INDIESTUDIO_SCENEGAME_HH
#define INDIESTUDIO_SCENEGAME_HH

#include <ThreadPool.hh>
#include <SFML/Audio/Sound.hpp>
#include "PowerUpNode.hh"
#include "IScene.hh"
#include "Player.hh"
#include "Map.hh"
#include "Referee.hh"
#include "IA.hh"
#include "SpecialEffectManager.hh"

class                                   SceneGame : public IScene {
public:
    enum Mode {
        PAUSE,
        INTRO,
        GAME,
        END
    };

    explicit SceneGame();
    virtual ~SceneGame();

    SceneGame(SceneGame const & other)              = delete;
    SceneGame(SceneGame && other)                   = delete;
    SceneGame &operator = (SceneGame const & other) = delete;

    bool                                setScene();
    int                                 refresh(int & id);
    void                                unsetScene();
    irr::gui::IGUIButton                * _bg;
    irr::video::ITexture                *_HUD;
    irr::video::ITexture                *_deadBlue;
    irr::video::ITexture                *_deadOrange;
    irr::video::ITexture                *_deadGreen;
    irr::video::ITexture                *_deadPurple;
    std::vector<irr::video::ITexture*>  _numbers;

private:
    void                                  _createWalls();
    void                                  _createGround();
    void                                  _createBoxes();
    void                                  _scaleNode(irr::scene::ISceneNode * node);
    void                                  _drawMenu() const;

    void                                  _addPowerUp(PowerUp const & powerup);

    int                                   _pauseMode(int &menuState);
    int                                   _idx;
    void                                  _gameMode();
    int                                   _endMode();
    void                                  _introMode();

    Mode                                  _mode;

    ThreadPool                            _threadPool;
    irr::core::vector3df                  _scale;
    std::vector<std::shared_ptr<IPlayer>> _players;
    irr::scene::ICameraSceneNode *        _camera;
    Map                                   _map;
    Referee                               _referee;
    std::vector<irr::scene::ISceneNode *> _boxes;
    std::vector<irr::scene::ISceneNode *> _walls;
    std::vector<irr::scene::ISceneNode *> _bombs;
//    irr::scene::ISceneNode *              _ground;
    std::vector<PowerUpNode>              _powerups;
    bool                                  _echapTimer;

    irr::gui::IGUIButton *                _menuBg;
    irr::gui::IGUIButton *                _menuResume;
    irr::gui::IGUIButton *                _menuSave;
    irr::gui::IGUIButton *                _menuQuit;

    irr::video::ITexture *                _win;
    irr::video::ITexture *                _lose;

    SpecialEffectManager                  _specialEffectManager;
    irr::u32                            _time;

#ifdef SOUND
    int                                 _once;
    sf::Sound                           _music;
    sf::Sound                           _soundWin;
    sf::Sound                           _soundLose;
    sf::Sound                           _soundBoom;
    sf::Sound                           _soundDead;
#endif

};


#endif //INDIESTUDIO_SCENEGAME_HH
