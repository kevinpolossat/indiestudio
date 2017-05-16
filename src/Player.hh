#ifndef _PLAYER_HH__
#define _PLAYER_HH__

#include <irrlicht.h>
#include <array>
#include "EventHandler.hh"

class Player {
    enum AnimType {
        RUN,
        STAND,
        JUMP
    };

public:
    Player(irr::scene::ISceneManager *sceneManager,
           irr::video::IVideoDriver *driver, uint8_t const id,
           std::array<irr::EKEY_CODE, 5> keyMap);
    ~Player();

    void        addAnimator(irr::scene::ISceneNodeAnimator * animator);
    void        move(EventHandler const & receiver);
    void        setCtrllrId(irr::u8 const &);
    void        setUsingCtrllr(const bool);

    irr::scene::IAnimatedMeshSceneNode * getMesh() const;
    irr::core::vector3df                 getPosition() const;
    irr::s8                              getCtrllrId() const;
    bool                                 getIsUsingCtrllr() const;

private:
    irr::scene::IAnimatedMeshSceneNode          *_mesh;
    AnimType                                     _anim;
    uint8_t                                      _id;
    std::array<irr::EKEY_CODE, 5>                _keyMap;
    irr::s8                                      _ctrllrId;
    bool                                        _isUsingCtrllr;
};

#endif /*_PLAYER_HH__*/
