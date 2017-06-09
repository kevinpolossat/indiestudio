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
}

bool SpecialEffectManager::isOver(const std::unique_ptr<IEffect> &x) {
    return x->isOver();
}

void SpecialEffectManager::clear() {
    _effects.clear();
}

