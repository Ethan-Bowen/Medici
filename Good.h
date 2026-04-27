#pragma once
// ============================================================
//  good.h  -  Good type enum and helper functions
// ============================================================

#include <string>
#include <vector>

enum class Good { GRAIN, CLOTH, SPICE, WINE, GOLD };

// All goods in a fixed order used for iteration
extern const std::vector<Good> ALL_GOODS;

std::string goodName(Good g);
std::string goodTag(Good g);
