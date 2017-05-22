//
// Created by vincent on 5/15/17.
//

#ifndef INDIESTUDIO_SCENEGAME_HH
#define INDIESTUDIO_SCENEGAME_HH

#include "IScene.hh"
#include "Player.hh"
#include "Map.hh"

class                                   SceneGame : public IScene {
public:
    explicit SceneGame();
    virtual ~SceneGame();

    bool                                setScene();
    int                                 refresh(int * id);
    void                                unsetScene();
    irr::gui::IGUIButton                *_bg;

private:
    Player                       * player;
    irr::scene::ICameraSceneNode * camera;
};


#endif //INDIESTUDIO_SCENEGAME_HH
