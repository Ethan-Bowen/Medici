#pragma once
// ============================================================
//  card.h  -  Card class declaration
// ============================================================

#include <iostream>
#include "good.h"

class Card {
    Good type_;
    int  value_;   // 0-5

public:
    Card(Good t, int v);

    Good getType()  const;
    int  getValue() const;

    bool operator<(const Card& o)  const;
    bool operator==(const Card& o) const;

    friend std::ostream& operator<<(std::ostream& os, const Card& c);
};
