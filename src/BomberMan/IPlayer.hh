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

    virtual void move(EventHandler const & receiver, Referee & referee) = 0;
    virtual PlayerNode &                         getNode() = 0;
    virtual PlayerNode const &                   getNode() const = 0;
};


#endif //INDIESTUDIO_IPLAYER_HH
