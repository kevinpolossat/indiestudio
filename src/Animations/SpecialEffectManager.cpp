//
// Created by kevin on 09/06/17.
//

#include <algorithm>
#include "SpecialEffectManager.hh"

SpecialEffectManager::SpecialEffectManager() {

}

SpecialEffectManager::~SpecialEffectManager() {

}

void SpecialEffectManager::refresh() {
    _effects.erase(std::remove_if(_effects.begin(), _effects.end(), isOver), _effects.end());
    std::for_each(_effects.begin(), _effects.end(), [](std::unique_ptr<IEffect> const &e){ e->update(); });
}

bool SpecialEffectManager::isOver(const std::unique_ptr<IEffect> &x) {
    return x->isOver();
}

void SpecialEffectManager::clear() {
    _effects.clear();
}