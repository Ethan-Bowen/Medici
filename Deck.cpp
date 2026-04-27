// ============================================================
//  deck.cpp  -  Deck class implementation
// ============================================================

#include "deck.h"
#include "exceptions.h"
#include <algorithm>

Deck::Deck() : rng_(std::random_device{}()) {
    reset();
}

void Deck::reset() {
    cards_.clear();

    // Standard Medici deck (26 cards):
    //   Grain, Cloth, Spice, Wine : values 1-5 each
    //   Gold                      : values 0-5
    for (int v = 1; v <= 5; v++) {
        cards_.emplace_back(Good::GRAIN, v);
        cards_.emplace_back(Good::CLOTH, v);
        cards_.emplace_back(Good::SPICE, v);
        cards_.emplace_back(Good::WINE, v);
        cards_.emplace_back(Good::GOLD, v);
    }
    cards_.emplace_back(Good::GOLD, 0);   // one zero-value Gold card

    std::shuffle(cards_.begin(), cards_.end(), rng_);
}

Card Deck::draw() {
    if (cards_.empty()) throw EmptyDeckException();
    Card c = cards_.back();
    cards_.pop_back();
    return c;
}

bool Deck::empty() const { return cards_.empty(); }
int  Deck::size()  const { return static_cast<int>(cards_.size()); }
