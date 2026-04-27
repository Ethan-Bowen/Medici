#pragma once
// ============================================================
//  deck.h  -  Deck class declaration
// ============================================================

#include <vector>
#include <random>
#include "card.h"

class Deck {
    std::vector<Card> cards_;
    std::mt19937      rng_;

public:
    Deck();

    // Rebuild and reshuffle a fresh 26-card deck
    void reset();

    // Draw the top card; throws EmptyDeckException if empty
    Card draw();

    bool empty() const;
    int  size()  const;
};
