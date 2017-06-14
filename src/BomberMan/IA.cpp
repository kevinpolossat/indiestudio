//
// Created by vincent on 5/31/17.
//

#include <boost/python.hpp>
#include "IA.hh"

static std::vector<Referee> referees;

IA::IA() : _node(irr::core::vector3df(0.f, 0.f, 0.f)) {
    this->_id = 0;
    this->_mem = Action::WAIT;
    this->_dist = 0.f;
}

IA::IA(uint32_t id, irr::core::vector3df const & scale)
        : _node(scale),
          _id(id) {
    this->_mem = Action::WAIT;
    this->_dist = 0.f;
}

IA::IA(IA const &&other)
        : _node(other._node),
          _id(other._id) {
    this->_mem = Action::WAIT;
    this->_dist = other._dist;
}

IA::IA(IA const &other) : _node(other._node) {
    this->_id = other._id;
    this->_mem = Action::WAIT;
    this->_dist = other._dist;
}

IA::~IA() {

}

void IA::move(EventHandler const &, Referee & referee) {
    referees.clear();
    referees.push_back(referee);

    try {
        if (this->_dist == 0.f) {
            boost::python::object module = boost::python::import("brain_logic");
            boost::python::object result = module.attr("execute")();
            switch (boost::python::extract<int>(result)()) {
                case 0:
                    this->_mem = Action::BOMB;
                    break;
                case 1:
                    this->_mem = Action::UP;
                    break;
                case 2:
                    this->_mem = Action::RIGHT;
                    break;
                case 3:
                    this->_mem = Action::DOWN;
                    break;
                case 4:
                    this->_mem = Action::LEFT;
                    break;
                default:
                    this->_mem = Action::WAIT;
            }
        }
        if (this->_mem != Action::WAIT) {
            auto c = referee.getCharacters();
            auto me = std::find_if(c.begin(), c.end(), [this](Character const &elem){ return elem.getId() == this->getId(); });
            this->_dist += me->getSpeed() * SPEED_UNIT;
            if (this->_dist >= 1.f)
                this->_dist = 0.f;
            referee.doAction(Action(this->getId(), this->_mem, 0));
        }
    } catch (const boost::python::error_already_set&) {
        PyErr_Print();
        exit(1);
    }
}

PlayerNode & IA::getNode() {
    return _node;
}

uint32_t IA::getId() const {
    return _id;
}

size_t IA::copyFromRefereeId(size_t id) {
    referees.push_back(referees[id]);
    return referees.size() - 1;
}

bool IA::amIDeadFromId(size_t id) const {
    auto c = referees[id].getCharacters();
    return std::find_if(c.begin(), c.end(), [this](Character const &elem){ return elem.getId() == this->getId(); }) == c.end();
}

size_t IA::getNumberOfBoxesFromId(size_t id) const {
    return referees[id].getMap().getBoxes().size();
}

size_t IA::getNumberOfPlayerFromId(size_t id) const {
    return referees[id].getCharacters().size();
}

void IA::doActionFromId(size_t id, size_t action) {
    switch (action) {
        case 0:
            referees[id].doAction(Action(this->getId(), Action::BOMB, 0));
            break;
        case 1:
            referees[id].doAction(Action(this->getId(), Action::UP, 1));
            break;
        case 2:
            referees[id].doAction(Action(this->getId(), Action::RIGHT, 1));
            break;
        case 3:
            referees[id].doAction(Action(this->getId(), Action::DOWN, 1));
            break;
        case 4:
            referees[id].doAction(Action(this->getId(), Action::LEFT, 1));
            break;
        default:
            break;
    }
}

void IA::doUpdateFromId(size_t id, size_t nums) {
    auto c = referees[id].getCharacters();
    auto me = std::find_if(c.begin(), c.end(), [this](Character const &elem){ return elem.getId() == this->getId(); });
    if (nums == 0)
        referees[id].update(false, 1 / (me->getSpeed() * SPEED_UNIT) + 10);
    else
        referees[id].update(false, nums);
}

size_t IA::getNumberOfPowerUpFromId(size_t id) const {
    auto c = referees[id].getCharacters();
    auto me = std::find_if(c.begin(), c.end(), [this](Character const &elem){ return elem.getId() == this->getId(); });
    return me->getBonusTaken();
}

size_t IA::getMaxDepth() const {
    return 4; //TODO: may vary
}

bool IA::isActionPossible(size_t id, size_t action) const {
    auto c = referees[id].getCharacters();
    auto me = std::find_if(c.begin(), c.end(), [this](Character const &elem){ return elem.getId() == this->getId(); });
    auto const &x = me->getPosition().X;
    auto const &y = me->getPosition().Y;
    auto const &z = me->getPosition().Z;

    irr::core::vector3df    pos;
    switch (action) {
        case 1:
            pos = irr::core::vector3df(x, y, z - 1);
            break;

        case 2:
            pos = irr::core::vector3df(x - 1, y, z);
            break;

        case 3:
            pos = irr::core::vector3df(x, y, z + 1);
            break;

        case 4:
            pos = irr::core::vector3df(x + 1, y, z);
            break;

        default:
            break;
    }
    return referees[id].isCellAvailable(pos);
}