//
// Created by kevin on 09/06/17.
//

#ifndef INDIESTUDIO_SPECIALEFFECTMANAGER_HH
#define INDIESTUDIO_SPECIALEFFECTMANAGER_HH

#include <vector>
#include <memory>

#include "irrlicht.h"
#include "IEffect.hh"
#include "UniformExplosion.hh"

class SpecialEffectManager {
public:
    SpecialEffectManager();
    ~SpecialEffectManager();

    SpecialEffectManager(SpecialEffectManager const & other)                = delete;
    SpecialEffectManager(SpecialEffectManager &&other)                      = delete;
    SpecialEffectManager &operator = (SpecialEffectManager const & other)   = delete;

    template <class T> void addEffect(irr::core::vector3df const & at, float duration = 1.0f) {
        (void)duration;
        _effects.push_back(std::move(std::make_unique<UniformExplosion>(at, 10.0f/*duration*/)));
//        _effects.push_back(std::move(std::make_unique<T>(at, duration)));
    }

    void refresh();
    void clear();
private:
    std::vector<std::unique_ptr<IEffect>> _effects;
    static bool isOver(std::unique_ptr<IEffect> const &x);
};


#endif //INDIESTUDIO_SPECIALEFFECTMANAGER_HH
