// ============================================================
//  good.cpp  -  Good type enum and helper functions
// ============================================================

#include "good.h"

const std::vector<Good> ALL_GOODS = {
    Good::GRAIN, Good::CLOTH, Good::SPICE, Good::WINE, Good::GOLD
};

std::string goodName(Good g) {
    switch (g) {
    case Good::GRAIN: return "Grain";
    case Good::CLOTH: return "Cloth";
    case Good::SPICE: return "Spice";
    case Good::WINE:  return "Wine";
    case Good::GOLD:  return "Gold";
    }
    return "?";
}

std::string goodTag(Good g) {
    switch (g) {
    case Good::GRAIN: return "[GRN]";
    case Good::CLOTH: return "[CLT]";
    case Good::SPICE: return "[SPC]";
    case Good::WINE:  return "[WIN]";
    case Good::GOLD:  return "[GLD]";
    }
    return "[???]";
}
