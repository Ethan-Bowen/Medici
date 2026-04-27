#pragma once
// ============================================================
//  game.h  -  MediciGame class declaration
// ============================================================

#include <vector>
#include "player.h"
#include "deck.h"

// Returned by runAuction()
struct AuctionResult {
    int winnerIndex;   // -1 = no winner
    int winningBid;
};

class MediciGame {
    int                 numPlayers_;
    std::vector<Player> players_;
    Deck                deck_;

    // Display
    void showAllPlayers() const;
    void showLot(const std::vector<Card>& lot) const;

    // Core game flow
    AuctionResult runAuction(int auctioneerIdx);
    void conductRound(int roundNum);
    void scoreRound();
    void finalResults();

public:
    MediciGame();

    void setup();
    void run();
};
