//
// Created by vincent on 5/15/17.
//

#ifndef INDIESTUDIO_SCENEGAME_HH
#define INDIESTUDIO_SCENEGAME_HH

#include "IScene.hh"

class SceneGame : public IScene {
public:
    explicit SceneGame(irr::IrrlichtDevice * device);
    virtual ~SceneGame();

    bool                setScene(irr::IrrlichtDevice * device);
    int                 refresh(irr::IrrlichtDevice * device, int * id, EventHandler * event);
    void                unsetScene(irr::IrrlichtDevice *);
};


#endif //INDIESTUDIO_SCENEGAME_HH
