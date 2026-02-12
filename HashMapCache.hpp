/*
** EPITECH PROJECT, 2026
** nanotekspice
** File description:
** HashMapCache
*/

#ifndef INCLUDED_HASHMAPCACHE_HPP
    #define INCLUDED_HASHMAPCACHE_HPP

#include "IComponent.hpp"
#include <cstdint>

namespace nts {

    extern size_t g_current_tick; //our global variable



struct CacheKey { //component to a key
    IComponent* comp;
    size_t pin;
    bool operator==(CacheKey const& o) const noexcept {
        return comp == o.comp && pin == o.pin;
    }
};

enum CacheState {
    CS_None = 0,
    CS_InProgress = 1,
    CS_Done = 2
};

struct CacheKeyHash { //had to look this up ngl, don't really get it
    size_t operator()(CacheKey const& k) const noexcept {
        size_t h1 = std::hash<void*>{}(k.comp); //generate rand num from comp
        size_t h2 = std::hash<size_t>{}(k.pin); //generate random num from pin
        return h1 ^ (h2 << 1); //xor to combine
    }
};

struct CacheEntry {//this what the cashe holds
    size_t tick = 0;
    CacheState state = CS_None;
    Tristate value = Undefined;
};

Tristate compute_hashmap(IComponent* comp, size_t pin);


}

#endif
