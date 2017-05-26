//
// Created by vincent on 5/15/17.
//

#ifndef INDIESTUDIO_SCENEGAME_HH
#define INDIESTUDIO_SCENEGAME_HH

#include "IScene.hh"
#include "Player.hh"
#include "Map.hh"
#include "Referee.hh"

class                                   SceneGame : public IScene {
public:
    explicit SceneGame();
    virtual ~SceneGame();

    bool                                setScene();
    int                                 refresh(int & id);
    void                                unsetScene();

    irr::gui::IGUIButton                * _bg;

private:
    void                                  _createWalls();
    void                                  _createGround();
    void                                  _createBoxes();
    void                                  _scaleNode(irr::scene::ISceneNode * node);

    irr::core::vector3df                  _scale;
    std::vector<Player>                   _players;
    irr::scene::ICameraSceneNode *        _camera;
    Map                                   _map;
    Referee                               _referee;
    std::vector<irr::scene::ISceneNode *> _boxes;
    std::vector<irr::scene::ISceneNode *> _walls;
    std::vector<irr::scene::ISceneNode *> _bombs;
};


#endif //INDIESTUDIO_SCENEGAME_HH
