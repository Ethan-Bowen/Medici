#pragma once
// ============================================================
//  utils.h  -  Console helper functions and scoring tables
// ============================================================

#include <string>
#include <vector>

// ── Display helpers ──────────────────────────────────────────

void separator(char ch = '-', int w = 64);
void header(const std::string& title);
void pause();

// Safe integer input in [lo, hi]; retries on bad input
int getInt(const std::string& prompt, int lo, int hi);

// ── Scoring ──────────────────────────────────────────────────

// VP awarded per cargo-total rank for a given player count
std::vector<int> cargoVPTable(int playerCount);

constexpr int GOOD_VP_1ST = 10;
constexpr int GOOD_VP_2ND = 5;
