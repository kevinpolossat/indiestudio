//
// Created by vincent on 5/31/17.
//

#include "IA.hh"

IA::IA(uint32_t id, irr::core::vector3df const & scale)
        : _node(scale), _id(id) {

}

IA::~IA() {

}

void IA::move(EventHandler const &, Referee & referee) {

}

PlayerNode & IA::getNode() {
    return _node;
}

PlayerNode const &IA::getNode() const {
    return _node;
}


