// ============================================================
//  game.cpp  -  MediciGame class implementation
// ============================================================

#include "game.h"
#include "utils.h"
#include "exceptions.h"
#include "good.h"

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <numeric>
#include <string>

// ── Constructor ──────────────────────────────────────────────

MediciGame::MediciGame() : numPlayers_(0) {}

// ── Display ──────────────────────────────────────────────────

void MediciGame::showAllPlayers() const {
    separator();
    for (const auto& p : players_) std::cout << "  " << p << "\n";
    separator();
}

void MediciGame::showLot(const std::vector<Card>& lot) const {
    std::cout << "  Lot: ";
    if (lot.empty()) { std::cout << "(empty)\n"; return; }
    int total = 0;
    for (const auto& c : lot) { std::cout << c << "  "; total += c.getValue(); }
    std::cout << " >> Total value: " << total << "\n";
}

// ── Auction ──────────────────────────────────────────────────

/*
 * English ascending auction, clockwise from the auctioneer.
 * Passing is permanent. Gold is NOT deducted here — the caller
 * deducts after the result is returned.
 */
AuctionResult MediciGame::runAuction(int auctioneerIdx) {
    int n = numPlayers_;
    int highBid = 0;
    int highBidder = -1;

    std::vector<bool> passed(n, false);

    // Players with full ships cannot bid
    int eligible = 0;
    for (int i = 0; i < n; i++) {
        if (players_[i].shipFull()) passed[i] = true;
        else ++eligible;
    }

    if (eligible == 0) {
        std::cout << "  All ships are full - lot discarded.\n";
        return { -1, 0 };
    }

    bool anyRaise = true;
    while (anyRaise) {
        anyRaise = false;

        for (int offset = 0; offset < n; offset++) {
            int i = (auctioneerIdx + offset) % n;
            if (passed[i]) continue;

            // Count other active bidders
            int others = 0;
            for (int j = 0; j < n; j++)
                if (!passed[j] && j != i) ++others;

            // Current high bidder is the only one left — they win
            if (others == 0 && highBidder == i) {
                anyRaise = false;
                goto auction_done;
            }

            {
                int maxCanBid = players_[i].getGold();
                int minBid = highBid + 1;

                std::cout << "\n  " << players_[i].getName()
                    << "'s turn  |  Gold: " << maxCanBid
                    << "  |  High bid: " << highBid
                    << " (by "
                    << (highBidder == -1 ? "nobody"
                        : players_[highBidder].getName())
                    << ")\n";

                if (maxCanBid < minBid) {
                    std::cout << "  " << players_[i].getName()
                        << " cannot afford to bid - forced to pass.\n";
                    passed[i] = true;
                    --eligible;
                    continue;
                }

                std::cout << "  Bid (" << minBid << "-" << maxCanBid
                    << "), or 0 to pass: ";

                int bid = -1;
                while (bid < 0) {
                    std::string line;
                    std::getline(std::cin, line);
                    try {
                        if (line.empty()) throw InvalidInputException("No input.");
                        size_t pos;
                        bid = std::stoi(line, &pos);
                        if (pos != line.size()) throw InvalidInputException("Not a number.");
                        if (bid != 0 && bid < minBid) {
                            std::cout << "  [!] Must bid at least " << minBid
                                << " or 0 to pass: ";
                            bid = -1; continue;
                        }
                        if (bid > maxCanBid) {
                            std::cout << "  [!] You only have " << maxCanBid
                                << " gold: ";
                            bid = -1; continue;
                        }
                    }
                    catch (const InvalidInputException& e) {
                        std::cout << "  [!] " << e.what() << " Try again: ";
                        bid = -1;
                    }
                    catch (const std::invalid_argument&) {
                        std::cout << "  [!] Enter a whole number: ";
                        bid = -1;
                    }
                }

                if (bid == 0) {
                    passed[i] = true;
                    --eligible;
                    std::cout << "  " << players_[i].getName() << " passes.\n";
                }
                else {
                    highBid = bid;
                    highBidder = i;
                    anyRaise = true;
                    std::cout << "  " << players_[i].getName()
                        << " bids " << bid << "!\n";
                }

                if (eligible == 1) {
                    anyRaise = false;
                    goto auction_done;
                }
            }
        }
    }

auction_done:
    return { highBidder, highBid };
}

// ── Round ────────────────────────────────────────────────────

void MediciGame::conductRound(int roundNum) {
    header("ROUND " + std::to_string(roundNum) + " / 3");
    deck_.reset();

    for (int turn = 0; turn < numPlayers_; turn++) {
        if (deck_.empty()) break;

        std::cout << "\n";
        separator();
        std::cout << "  AUCTIONEER: " << players_[turn].getName()
            << "   (Deck: " << deck_.size() << " cards left)\n";
        separator();
        showAllPlayers();

        // -- Draw phase --
        std::vector<Card> lot;
        Card c1 = deck_.draw();
        lot.push_back(c1);
        std::cout << "\n  Drew: " << c1 << "\n";
        showLot(lot);

        if (!deck_.empty() && !players_[turn].shipFull()) {
            int choice = getInt("\n  Draw a second card? (1=Yes / 0=No): ", 0, 1);
            if (choice == 1) {
                Card c2 = deck_.draw();
                lot.push_back(c2);
                std::cout << "  Also drew: " << c2 << "\n";
                showLot(lot);
            }
        }

        // -- Auction phase --
        std::cout << "\n  --- AUCTION ---\n";
        AuctionResult result = runAuction(turn);

        if (result.winnerIndex == -1) {
            std::cout << "\n  No winner - lot discarded.\n";
        }
        else {
            Player& winner = players_[result.winnerIndex];
            try {
                winner.spendGold(result.winningBid);
            }
            catch (const InvalidBidException& e) {
                std::cerr << "\n  [!] " << e.what() << " - lot discarded.\n";
                continue;
            }

            std::cout << "\n  " << winner.getName()
                << " wins the lot for " << result.winningBid << " gold!\n";

            for (const auto& c : lot) {
                try {
                    winner.addToShip(c);
                    std::cout << "  + Loaded: " << c << "\n";
                }
                catch (const ShipFullException&) {
                    std::cout << "  [!] Ship full - discarded: " << c << "\n";
                }
            }
        }
    }

    scoreRound();
    for (auto& p : players_) p.clearShip();
}

// ── Scoring ──────────────────────────────────────────────────

void MediciGame::scoreRound() {
    header("ROUND SCORING");

    // 1. Cargo total ranking
    std::cout << "\n  [Cargo Total Bonuses]\n\n";

    std::vector<std::pair<int, int>> cargoRank;
    for (int i = 0; i < numPlayers_; i++)
        cargoRank.push_back({ players_[i].cargoValue(), i });
    std::sort(cargoRank.begin(), cargoRank.end(),
        [](auto& a, auto& b) { return a.first > b.first; });

    auto vpTable = cargoVPTable(numPlayers_);

    int rank = 0;
    while (rank < numPlayers_) {
        int tieEnd = rank + 1;
        while (tieEnd < numPlayers_ &&
            cargoRank[tieEnd].first == cargoRank[rank].first)
            ++tieEnd;

        int vpPool = 0;
        for (int k = rank; k < tieEnd && k < (int)vpTable.size(); k++)
            vpPool += vpTable[k];
        int vpEach = (tieEnd > rank) ? vpPool / (tieEnd - rank) : 0;

        for (int k = rank; k < tieEnd; k++) {
            int pi = cargoRank[k].second;
            players_[pi].addVP(vpEach);
            std::cout << "  " << std::left << std::setw(14) << players_[pi].getName()
                << "cargo=" << std::setw(3) << cargoRank[k].first
                << "  -> +" << vpEach << " VP\n";
        }
        rank = tieEnd;
    }

    // 2. Good majorities
    std::cout << "\n  [Good Majority Bonuses]\n\n";

    for (Good g : ALL_GOODS) {
        std::vector<std::pair<int, int>> gRank;
        for (int i = 0; i < numPlayers_; i++)
            gRank.push_back({ players_[i].goodCount(g), i });
        std::sort(gRank.begin(), gRank.end(),
            [](auto& a, auto& b) { return a.first > b.first; });

        if (gRank[0].first == 0) continue;   // nobody has this good

        int firstCount = gRank[0].first;
        std::vector<int> firstGroup;
        for (auto& pr : gRank)
            if (pr.first == firstCount) firstGroup.push_back(pr.second);

        if (firstGroup.size() == 1) {
            int p1 = firstGroup[0];
            players_[p1].addVP(GOOD_VP_1ST);
            std::cout << "  " << std::left << std::setw(6) << goodName(g)
                << " 1st: " << std::setw(14) << players_[p1].getName()
                << "(" << firstCount << ") -> +" << GOOD_VP_1ST << " VP\n";

            // 2nd place
            int secondCount = -1;
            for (auto& pr : gRank)
                if (pr.second != p1 && pr.first > 0) { secondCount = pr.first; break; }

            if (secondCount > 0) {
                std::vector<int> secondGroup;
                for (auto& pr : gRank)
                    if (pr.first == secondCount) secondGroup.push_back(pr.second);
                int vpEach = GOOD_VP_2ND / static_cast<int>(secondGroup.size());
                for (int pi : secondGroup) {
                    players_[pi].addVP(vpEach);
                    std::cout << "  " << std::left << std::setw(6) << goodName(g)
                        << " 2nd: " << std::setw(14) << players_[pi].getName()
                        << "(" << secondCount << ") -> +" << vpEach << " VP\n";
                }
            }
        }
        else {
            // Tie for 1st: split 1st + 2nd VP pool
            int pool = (GOOD_VP_1ST + GOOD_VP_2ND)
                / static_cast<int>(firstGroup.size());
            for (int pi : firstGroup) {
                players_[pi].addVP(pool);
                std::cout << "  " << std::left << std::setw(6) << goodName(g)
                    << " tie: " << std::setw(14) << players_[pi].getName()
                    << "(" << firstCount << ") -> +" << pool << " VP\n";
            }
        }
    }

    std::cout << "\n  [Scoreboard]\n\n";
    showAllPlayers();
}

// ── Final Results ────────────────────────────────────────────

void MediciGame::finalResults() {
    header("FINAL RESULTS");

    std::vector<int> order(numPlayers_);
    std::iota(order.begin(), order.end(), 0);
    std::sort(order.begin(), order.end(),
        [&](int a, int b) { return players_[a].getVP() > players_[b].getVP(); });

    std::cout << "\n  FINAL STANDINGS:\n\n";
    for (int r = 0; r < numPlayers_; r++) {
        int pi = order[r];
        std::cout << "  " << (r + 1) << ".  "
            << std::left << std::setw(14) << players_[pi].getName()
            << players_[pi].getVP() << " VP"
            << "  (gold left: " << players_[pi].getGold() << ")\n";
    }

    std::cout << "\n";
    separator('*');
    std::cout << "  WINNER:  " << players_[order[0]].getName()
        << "  with  " << players_[order[0]].getVP() << " VP!\n";
    separator('*');
    std::cout << "\n  Thanks for playing Medici!\n\n";
}

// ── Setup ────────────────────────────────────────────────────

void MediciGame::setup() {
    header("WELCOME TO MEDICI");
    std::cout << R"(
  Medici is an auction game set in Renaissance Florence.
  Players spend gold to buy goods and load them onto ships.
 
  HOW TO PLAY:
    - The game lasts 3 rounds.
    - Each round every player takes a turn as Auctioneer.
    - The Auctioneer draws 1 card (optionally a 2nd) to form
      the lot, then all players bid in clockwise order.
    - The winner pays their bid and loads the cards onto their
      ship (max 5 cards per round). Passing is permanent.
    - At round end, VP are awarded for:
        * Cargo-total ranking  (who loaded the most value)
        * Good majorities      (most/2nd-most of each good)
    - Most total VP after 3 rounds wins!
 
  GOODS & VALUES:
    Grain [GRN] 1-5    Cloth [CLT] 1-5    Spice [SPC] 1-5
    Wine  [WIN] 1-5    Gold  [GLD] 0-5
 
  Each player starts with 30 gold. Spent gold is gone!
 
)";
    numPlayers_ = getInt("  How many players? (2-6): ", 2, 6);
    std::cout << "\n";

    for (int i = 0; i < numPlayers_; i++) {
        std::cout << "  Name for Player " << (i + 1) << ": ";
        std::string name;
        std::getline(std::cin, name);
        if (name.empty()) name = "Player" + std::to_string(i + 1);
        players_.emplace_back(name, 30);
    }

    std::cout << "\n  Players registered (each starts with 30 gold):\n";
    for (const auto& p : players_)
        std::cout << "    - " << p.getName() << "\n";

    pause();
}

// ── Main Loop ────────────────────────────────────────────────

void MediciGame::run() {
    setup();
    for (int r = 1; r <= 3; r++) {
        conductRound(r);
        if (r < 3) pause();
    }
    finalResults();
}
