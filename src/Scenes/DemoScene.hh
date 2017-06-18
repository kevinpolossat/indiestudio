//
// Created by vincent on 6/18/17.
//

#ifndef INDIESTUDIO_DEMOSCENE_HH
#define INDIESTUDIO_DEMOSCENE_HH

#include <Settings.hh>
#include <Save.hh>
#include <ThreadPool.hh>
#include <IPlayer.hh>
#include <PowerUpNode.hh>
#include <SpecialEffectManager.hh>
#include <SFML/Audio/Sound.hpp>
#include "Spawn.hh"
#include "Explosion.hh"
#include "DemoScene.hh"
#include "Save.hh"

class DemoScene : public IScene {
public:
    explicit DemoScene();
    virtual ~DemoScene();

    DemoScene(DemoScene const & other)              = delete;
    DemoScene(DemoScene && other)                   = delete;
    DemoScene &operator = (DemoScene const & other) = delete;

    bool                                setScene();
    int                                 refresh(int & id);
    void                                unsetScene();

private:
    void                                  _createWalls();
    void                                  _createGround();
    void                                  _createBoxes();
    void                                  _scaleNode(irr::scene::ISceneNode * node);

    void                                  _addPowerUp(PowerUp const & powerup);

    ThreadPool                            _threadPool;
    irr::core::vector3df                  _scale;
    std::vector<std::shared_ptr<IPlayer>> _players;
    irr::scene::ICameraSceneNode *        _camera;
    Map                                   _map;
    Referee                               _referee;
    std::vector<irr::scene::ISceneNode *> _boxes;
    std::vector<irr::scene::ISceneNode *> _walls;
    std::vector<irr::scene::ISceneNode *> _bombs;
    std::vector<PowerUpNode>              _powerups;

    SpecialEffectManager                  _specialEffectManager;
    irr::u32                              _time;

#ifdef SOUND
    int                                 _once;
    sf::Sound                           _music;
    sf::Sound                           _soundWin;
    sf::Sound                           _soundLose;
    sf::Sound                           _soundBoom;
    sf::Sound                           _soundDead;
#endif
};


#endif //INDIESTUDIO_DEMOSCENE_HH
