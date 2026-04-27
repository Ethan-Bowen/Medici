// ============================================================
//  card.cpp  -  Card class implementation
// ============================================================

#include "card.h"
#include <iomanip>

Card::Card(Good t, int v) : type_(t), value_(v) {}

Good Card::getType()  const { return type_; }
int  Card::getValue() const { return value_; }

bool Card::operator<(const Card& o)  const { return value_ < o.value_; }
bool Card::operator==(const Card& o) const {
    return type_ == o.type_ && value_ == o.value_;
}

std::ostream& operator<<(std::ostream& os, const Card& c) {
    os << goodTag(c.type_)
        << std::left << std::setw(6) << goodName(c.type_)
        << "(v:" << c.value_ << ")";
    return os;
}
