//
// Created by vincent on 5/15/17.
//

#ifndef INDIESTUDIO_SCENEGAME_HH
#define INDIESTUDIO_SCENEGAME_HH

#include "IScene.hh"

class SceneGame : Scene{
public:
    explicit SceneGame(irr::IrrlichtDevice * device);
    virtual ~SceneGame();

    bool                setScene(irr::IrrlichtDevice * device);
    int                 refresh(irr::IrrlichtDevice * device, int * id, EventReceiver * event);
    void                unsetScene();
};


#endif //INDIESTUDIO_SCENEGAME_HH
