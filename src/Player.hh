#ifndef _PLAYER_HH__
#define _PLAYER_HH__

#include <irrlicht.h>
#include <array>
#include "EventHandler.hh"
#include "ResourceManager.hh"
#include "Referee.hh"

class Player {
    enum AnimType {
        RUN,
        STAND
    };

public:
    Player(uint8_t const id,
           std::array<irr::EKEY_CODE, 5> keyMap);
    ~Player();

    void        addAnimator(irr::scene::ISceneNodeAnimator * animator);
    void        removeAnimators();
    void        move(EventHandler const & receiver, Referee & referee);
    void        setCtrllrId(int32_t const);
    void        setUsingCtrllr(const bool);

    irr::scene::IAnimatedMeshSceneNode * getMesh() const;
    irr::core::vector3df const &         getPosition() const;
    int32_t const                        getCtrllrId() const;
    bool const                           getIsUsingCtrllr() const;

    void                                setPosition(irr::core::vector3df const & pos);


private:
    irr::scene::IAnimatedMeshSceneNode          *_node;
    AnimType                                     _anim;
    uint32_t                                     _id;
    std::array<irr::EKEY_CODE, 5>                _keyMap;
    int32_t                                      _ctrllrId;
    bool                                         _isUsingCtrllr;
};

#endif /*_PLAYER_HH__*/
