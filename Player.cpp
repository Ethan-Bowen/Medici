// ============================================================
//  player.cpp  -  Player class implementation
// ============================================================

#include "player.h"
#include "exceptions.h"
#include <iomanip>

Player::Player(const std::string& name, int startGold)
    : name_(name), gold_(startGold), vp_(0) {
}

const std::string& Player::getName()  const { return name_; }
int                      Player::getGold()  const { return gold_; }
int                      Player::getVP()    const { return vp_; }
const std::vector<Card>& Player::getShip()  const { return ship_; }
bool                     Player::shipFull() const { return static_cast<int>(ship_.size()) >= MAX_SHIP; }
int                      Player::shipSize() const { return static_cast<int>(ship_.size()); }

void Player::spendGold(int amount) {
    if (amount < 0)
        throw InvalidBidException("Amount cannot be negative.");
    if (amount > gold_)
        throw InvalidBidException(name_ + " only has " + std::to_string(gold_) + " gold.");
    gold_ -= amount;
}

void Player::addToShip(const Card& c) {
    if (shipFull()) throw ShipFullException();
    ship_.push_back(c);
}

void Player::clearShip() { ship_.clear(); }
void Player::addVP(int vp) { vp_ += vp; }

int Player::cargoValue() const {
    int sum = 0;
    for (const auto& c : ship_) sum += c.getValue();
    return sum;
}

int Player::goodCount(Good g) const {
    int cnt = 0;
    for (const auto& c : ship_) if (c.getType() == g) ++cnt;
    return cnt;
}

bool Player::operator<(const Player& o)  const { return vp_ < o.vp_; }
bool Player::operator==(const Player& o) const { return name_ == o.name_; }

std::ostream& operator<<(std::ostream& os, const Player& p) {
    os << std::left << std::setw(14) << p.name_
        << "Gold:" << std::setw(4) << p.gold_
        << "VP:" << std::setw(5) << p.vp_
        << "Ship[" << p.ship_.size() << "/5]: ";
    for (const auto& c : p.ship_)
        os << goodTag(c.getType()) << c.getValue() << " ";
    return os;
}
