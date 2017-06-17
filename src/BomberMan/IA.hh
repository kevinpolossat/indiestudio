//
// Created by vincent on 5/31/17.
//

#ifndef INDIESTUDIO_IA_HH
#define INDIESTUDIO_IA_HH

extern "C" {
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}
#include <LuaBridge.h>
#include "IPlayer.hh"

#define DEFAULT_AI_DEPTH 4

class IA : public IPlayer {
public:
    IA();
    explicit IA(uint32_t id, irr::core::vector3df const & scale, size_t depth = DEFAULT_AI_DEPTH);
    IA(IA const & other);
    IA(IA const && other);
    ~IA();

    void                initBinding();
    Action              move(EventHandler const & receiver, Referee & referee);

    bool                isHuman() const;
    PlayerNode &        getNode();
    uint32_t            getId() const;
    size_t              copyFromRefereeId(size_t id);
    bool                amIDeadFromId(size_t id) const;
    size_t              getNumberOfBoxesFromId(size_t id) const;
    size_t              getNumberOfPlayerFromId(size_t id) const;
    void                doActionFromId(size_t id, size_t action);
    void                doUpdateFromId(size_t id, size_t nums);
    size_t              getNumberOfPowerUpFromId(size_t id) const;
    size_t              getMaxDepth(void) const;
    bool                isActionPossible(size_t id, size_t action) const;

private:
    PlayerNode              _node;
    uint32_t                _id;
    lua_State               *_lua;
    Action::Type            _mem;
    float                   _dist;
    size_t                  _depth;
    std::vector<Referee>    _referees;
};

#endif //INDIESTUDIO_IA_HH
