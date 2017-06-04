//
// Created by vincent on 5/31/17.
//

#include "IA.hh"

IA::IA(uint32_t id, irr::core::vector3df const & scale)
        : _node(scale),
          _id(id) {
}

IA::IA(IA const &&other)
        : _node(other._node),
          _id(other._id) {
}

IA::~IA() {

}

void IA::move(EventHandler const &, Referee &) {

}

PlayerNode & IA::getNode() {
    return _node;
}

uint32_t IA::getId() const {
    return _id;
}
