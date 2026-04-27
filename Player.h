#pragma once
// ============================================================
//  player.h  -  Player class declaration
// ============================================================

#include <iostream>
#include <string>
#include <vector>
#include "card.h"
#include "good.h"

class Player {
    std::string       name_;
    int               gold_;
    int               vp_;
    std::vector<Card> ship_;

    static constexpr int MAX_SHIP = 5;

public:
    explicit Player(const std::string& name, int startGold = 30);

    // Accessors
    const std::string& getName()  const;
    int                      getGold()  const;
    int                      getVP()    const;
    const std::vector<Card>& getShip()  const;
    bool                     shipFull() const;
    int                      shipSize() const;

    // Actions
    // Deducts amount from gold; throws InvalidBidException if invalid
    void spendGold(int amount);

    // Adds card to ship; throws ShipFullException if full
    void addToShip(const Card& c);

    void clearShip();
    void addVP(int vp);

    // Returns sum of all card values on the ship
    int cargoValue() const;

    // Returns how many cards of the given good type are on the ship
    int goodCount(Good g) const;

    // Operator overloads
    bool operator<(const Player& o)  const;
    bool operator==(const Player& o) const;

    friend std::ostream& operator<<(std::ostream& os, const Player& p);
};
