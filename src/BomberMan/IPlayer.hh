//
// Created by vincent on 5/31/17.
//

#ifndef INDIESTUDIO_IPLAYER_HH
#define INDIESTUDIO_IPLAYER_HH

#include "Referee.hh"
#include "EventHandler.hh"
#include "PlayerNode.hh"

class IPlayer {
public:
    virtual ~IPlayer() {};

    virtual Action             move(EventHandler const & receiver, Referee & referee) = 0;
    virtual PlayerNode &       getNode() = 0;
    virtual uint32_t           getId() const = 0;
    virtual bool               isHuman() = 0;
};


#endif //INDIESTUDIO_IPLAYER_HH
