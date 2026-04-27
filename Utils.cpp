// ============================================================
//  utils.cpp  -  Console helper functions and scoring tables
// ============================================================

#include "utils.h"
#include "exceptions.h"
#include <iostream>
#include <string>
#include <algorithm>

// ── Display helpers ──────────────────────────────────────────

void separator(char ch, int w) {
    std::cout << std::string(w, ch) << "\n";
}

void header(const std::string& title) {
    separator('=');
    int pad = std::max(0, (64 - static_cast<int>(title.size())) / 2);
    std::cout << std::string(pad, ' ') << title << "\n";
    separator('=');
}

void pause() {
    std::cout << "\n  [Press ENTER to continue...] ";
    std::string s;
    std::getline(std::cin, s);
}

// ── Input ────────────────────────────────────────────────────

int getInt(const std::string& prompt, int lo, int hi) {
    for (;;) {
        std::cout << prompt;
        std::string line;
        std::getline(std::cin, line);
        try {
            if (line.empty()) throw InvalidInputException("No input given.");
            size_t pos;
            int v = std::stoi(line, &pos);
            if (pos != line.size()) throw InvalidInputException("Extra characters found.");
            if (v < lo || v > hi)
                throw InvalidInputException("Please enter a value between "
                    + std::to_string(lo) + " and " + std::to_string(hi) + ".");
            return v;
        }
        catch (const std::invalid_argument&) {
            std::cout << "  [!] Please enter a whole number.\n";
        }
        catch (const InvalidInputException& e) {
            std::cout << "  [!] " << e.what() << "\n";
        }
    }
}

// ── Scoring ──────────────────────────────────────────────────

std::vector<int> cargoVPTable(int n) {
    switch (n) {
    case 2:  return { 10,  0 };
    case 3:  return { 10,  5,  0 };
    case 4:  return { 10,  7,  4,  0 };
    case 5:  return { 10,  7,  4,  2,  0 };
    default: return { 10,  7,  4,  2,  1,  0 };   // 6 players
    }
}
