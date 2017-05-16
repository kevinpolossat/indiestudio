//
// Created by vincent on 5/15/17.
//

#ifndef INDIESTUDIO_SCENEGAME_HH
#define INDIESTUDIO_SCENEGAME_HH

#include "IScene.hh"

class SceneGame : public IScene {
public:
    explicit SceneGame(ResourceManager & rm);
    virtual ~SceneGame();

    bool                setScene();
    int                 refresh(int * id);
    void                unsetScene();

private:
    ResourceManager & rm;
};


#endif //INDIESTUDIO_SCENEGAME_HH
