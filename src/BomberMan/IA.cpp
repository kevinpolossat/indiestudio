//
// Created by vincent on 5/31/17.
//

#include "IA.hh"

static IA *ref[4] = {nullptr};

IA::IA() : _node(irr::core::vector3df(0.f, 0.f, 0.f)) {
    this->_id = 0;
    this->_mem = Action::WAIT;
    this->_dist = 0.f;
    this->initBinding();
    ref[this->_id] = this;
}

IA::IA(uint32_t id, irr::core::vector3df const & scale)
        : _node(scale),
          _id(id) {
    this->_mem = Action::WAIT;
    this->_dist = 0.f;
    this->initBinding();
    ref[this->_id] = this;
}

IA::IA(IA const &&other)
        : _node(other._node),
          _id(other._id) {
    this->_mem = Action::WAIT;
    this->_dist = other._dist;
    this->_lua = other._lua;
    ref[this->_id] = this;
}

IA::IA(IA const &other) : _node(other._node) {
    this->_id = other._id;
    this->_mem = Action::WAIT;
    this->_dist = other._dist;
    this->_lua = other._lua;
    ref[this->_id] = this;
}

IA::~IA() {
}

size_t copy(size_t me, size_t id) {
    return ref[me]->copyFromRefereeId(id);
}

bool amIDead(size_t me, size_t id) {
    return ref[me]->amIDeadFromId(id);
}

size_t getNumberOfBoxes(size_t me, size_t id) {
    return ref[me]->getNumberOfBoxesFromId(id);
}

size_t getNumberOfPlayer(size_t me, size_t id) {
    return ref[me]->getNumberOfPlayerFromId(id);
}

void doAction(size_t me, size_t id, size_t action) {
    ref[me]->doActionFromId(id, action);
}

void doUpdate(size_t me, size_t id, size_t nums) {
    ref[me]->doUpdateFromId(id, nums);
}

size_t getNumberOfPowerUp(size_t me, size_t id) {
    return ref[me]->getNumberOfPowerUpFromId(id);
}

size_t getMaxDepth(size_t me) {
    return ref[me]->getMaxDepth();
}

bool isActionPossible(size_t me, size_t id, size_t action) {
    return ref[me]->isActionPossible(id, action);
}

void IA::initBinding() {
    this->_lua = luaL_newstate();
    luaL_openlibs(this->_lua);
    luaL_dofile(this->_lua, "./src/BomberMan/brain_logic.lua");
    lua_pcall(this->_lua, 0, 0, 0);
    luabridge::getGlobalNamespace(this->_lua)
            .addFunction("copy", copy)
            .addFunction("amIDead", amIDead)
            .addFunction("getNumberOfBoxes", getNumberOfBoxes)
            .addFunction("getNumberOfPlayer", getNumberOfPlayer)
            .addFunction("doAction", doAction)
            .addFunction("doUpdate", doUpdate)
            .addFunction("getNumberOfPowerUp", getNumberOfPowerUp)
            .addFunction("getMaxDepth", ::getMaxDepth)
            .addFunction("isActionPossible", ::isActionPossible);
}

void IA::move(EventHandler const &, Referee & referee) {
    if (this->_dist == 0.f) {
        this->_referees.clear();
        this->_referees.push_back(referee);

        luabridge::LuaRef func = luabridge::getGlobal(this->_lua, "brain");
        luabridge::LuaRef ret = func(this->_id);
        int result = ret.cast<int>();
        switch (result) {
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
}

PlayerNode & IA::getNode() {
    return _node;
}

uint32_t IA::getId() const {
    return _id;
}

size_t IA::copyFromRefereeId(size_t id) {
    this->_referees.push_back(this->_referees[id]);
    return this->_referees.size() - 1;
}

bool IA::amIDeadFromId(size_t id) const {
    auto c = this->_referees[id].getCharacters();
    return std::find_if(c.begin(), c.end(), [this](Character const &elem){ return elem.getId() == this->getId(); }) == c.end();
}

size_t IA::getNumberOfBoxesFromId(size_t id) const {
    return this->_referees[id].getMap().getBoxes().size();
}

size_t IA::getNumberOfPlayerFromId(size_t id) const {
    return this->_referees[id].getCharacters().size();
}

void IA::doActionFromId(size_t id, size_t action) {
    switch (action) {
        case 0:
            this->_referees[id].doAction(Action(this->getId(), Action::BOMB, 0));
            break;
        case 1:
            this->_referees[id].doAction(Action(this->getId(), Action::UP, 1));
            break;
        case 2:
            this->_referees[id].doAction(Action(this->getId(), Action::RIGHT, 1));
            break;
        case 3:
            this->_referees[id].doAction(Action(this->getId(), Action::DOWN, 1));
            break;
        case 4:
            this->_referees[id].doAction(Action(this->getId(), Action::LEFT, 1));
            break;
        default:
            break;
    }
}

void IA::doUpdateFromId(size_t id, size_t nums) {
    auto c = this->_referees[id].getCharacters();
    auto me = std::find_if(c.begin(), c.end(), [this](Character const &elem){ return elem.getId() == this->getId(); });
    if (nums == 0)
        this->_referees[id].update(false, 1 / (me->getSpeed() * SPEED_UNIT) + 10);
    else
        this->_referees[id].update(false, nums);
}

size_t IA::getNumberOfPowerUpFromId(size_t id) const {
    auto c = this->_referees[id].getCharacters();
    auto me = std::find_if(c.begin(), c.end(), [this](Character const &elem){ return elem.getId() == this->getId(); });
    return me->getBonusTaken();
}

size_t IA::getMaxDepth() const {
    return 4; //TODO: may vary
}

bool IA::isActionPossible(size_t id, size_t action) const {
    auto c = this->_referees[id].getCharacters();
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
    return this->_referees[id].isCellAvailable(pos);
}

bool IA::isHuman() {
    return false;
}
