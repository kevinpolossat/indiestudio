#ifndef _PLAYER_HH__
#define _PLAYER_HH__

#include <irrlicht.h>
#include <array>
#include "EventHandler.hh"
#include "ResourceManager.hh"
#include "Referee.hh"
#include "IPlayer.hh"
#include "PlayerNode.hh"

class Player : public IPlayer {
public:
    Player(uint8_t const id,
           std::array<irr::EKEY_CODE, 5> keyMap,
           irr::core::vector3df const & scale);
    Player(Player const & other);
    Player(Player const && other);
    ~Player();

    bool        isHuman() const;
    Action      move(EventHandler const & receiver, Referee & referee);
    void        setCtrllrId(int32_t const);
    void        setUsingCtrllr(const bool);

    int32_t            getCtrllrId() const;
    bool               getIsUsingCtrllr() const;
    PlayerNode &       getNode();
    uint32_t           getId() const;

private:
    PlayerNode                                   _node;
    uint32_t                                     _id;
    std::array<irr::EKEY_CODE, 5>                _keyMap; //UP, RIGHT, DOWN, LEFT, BOMB
    int32_t                                      _ctrllrId;
    bool                                         _isUsingCtrllr;
};

#endif /*_PLAYER_HH__*/
