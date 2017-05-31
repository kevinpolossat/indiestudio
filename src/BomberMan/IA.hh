//
// Created by vincent on 5/31/17.
//

#ifndef INDIESTUDIO_IA_HH
#define INDIESTUDIO_IA_HH


#include "IPlayer.hh"

class IA : public IPlayer {
public:
    explicit IA(uint32_t id, irr::core::vector3df const & scale);
    IA(IA const & other) = delete;
    IA(IA const && other);
    ~IA();

    void        move(EventHandler const & receiver, Referee & referee);

    PlayerNode &       getNode();
    uint32_t           getId() const;

private:
    PlayerNode _node;
    uint32_t   _id;
};


#endif //INDIESTUDIO_IA_HH
