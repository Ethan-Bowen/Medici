# Medici — Player's Guide & README

> *"Buy low, sell high — and pray your rivals don't corner the spice market."*

Medici is a 2–6 player Renaissance trading game by Reiner Knizia. Players bid gold to load goods onto their ships, competing for cargo-total dominance and good-type majorities across three rounds. The richest merchant at the end wins.

---

## Table of Contents

1. [Getting Started](#1-getting-started)
2. [Game Overview](#2-game-overview)
3. [The Cards](#3-the-cards)
4. [Turn Structure](#4-turn-structure)
5. [Bidding Rules](#5-bidding-rules)
6. [End-of-Round Scoring](#6-end-of-round-scoring)
7. [Winning the Game](#7-winning-the-game)
8. [Strategy Tips](#8-strategy-tips)
9. [Building & Running the Program](#9-building--running-the-program)
10. [Project File Reference](#10-project-file-reference)

---

## 1. Getting Started

### Requirements
- [Visual Studio Code](https://code.visualstudio.com/)
- The [C/C++ extension](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools) for VS Code (`ms-vscode.cpptools`)
- A C++17-compatible compiler:
  - **Windows:** [MinGW-w64](https://www.mingw-w64.org/) or [MSVC](https://visualstudio.microsoft.com/visual-cpp-build-tools/)
  - **macOS:** Xcode Command Line Tools (`xcode-select --install`)
  - **Linux:** `sudo apt install g++`

### Running in VS Code

1. Open the folder containing all source files in VS Code (**File → Open Folder**)
2. Open `main.cpp`
3. Press **Ctrl+Shift+B** (Windows/Linux) or **Cmd+Shift+B** (macOS) to build
4. Press **F5** to run with the integrated debugger, or **Ctrl+F5** to run without it

> **Note:** If prompted to select a compiler kit on first run, choose `g++` or your installed compiler. The integrated terminal will appear at the bottom of VS Code where you can interact with the game.

When the program starts, enter the number of players (2–6), then a name for each player. All players begin with **30 gold**.

---

## 2. Game Overview

| Detail | Value |
|---|---|
| Players | 2 – 6 |
| Rounds | 3 |
| Starting gold | 30 per player |
| Ship capacity | 5 cards per player per round |
| Victory points | Earned from cargo totals and good majorities |

The game is played over **3 rounds**. Each round, every player takes one turn as the **Auctioneer**. After all turns are complete, VP are awarded and ships are cleared for the next round. The player with the most VP after Round 3 wins.

---

## 3. The Cards

The deck contains **26 cards** across five good types:

| Good | Tag | Values Available |
|---|---|---|
| Grain | `[GRN]` | 1, 2, 3, 4, 5 |
| Cloth | `[CLT]` | 1, 2, 3, 4, 5 |
| Spice | `[SPC]` | 1, 2, 3, 4, 5 |
| Wine  | `[WIN]` | 1, 2, 3, 4, 5 |
| Gold  | `[GLD]` | 0, 1, 2, 3, 4, 5 |

- Every good except Gold has values **1 through 5** (5 cards each = 25 cards).
- Gold has an extra **0-value** card, giving it 6 cards total (26 cards in the deck).
- The deck is **freshly shuffled at the start of each round**.
- A card's **value** contributes to your ship's cargo total and determines which good-type majority you are competing for.

---

## 4. Turn Structure

Each player's turn as Auctioneer follows these steps:

### Step 1 — Draw
The Auctioneer draws **1 card** face-up from the deck. This card is automatically added to the auction lot.

### Step 2 — Optional Second Draw
The Auctioneer may choose to draw a **second card** and add it to the lot, making it more valuable (and more expensive). This is entirely optional. The Auctioneer cannot draw a second card if their ship is already full.

> **Tip:** Drawing two cards increases the lot's value but also raises the stakes — you may trigger a bidding war that costs more than you planned.

### Step 3 — Auction
All players (including the Auctioneer) may bid on the lot. Bidding proceeds **clockwise** starting from the Auctioneer. The highest bidder wins all cards in the lot.

### Step 4 — Load Ship
The winner loads each card from the lot onto their ship (max **5 cards** total per round). Any card that cannot fit because the ship is full is **discarded**.

Play then passes clockwise to the next Auctioneer.

---

## 5. Bidding Rules

- Bids must be **whole numbers** of gold.
- Each new bid must be **strictly higher** than the current high bid.
- Enter **0** to **pass**. Passing is **permanent** — you cannot re-enter that auction.
- You **cannot bid more gold than you currently have**.
- If you cannot afford the minimum bid, you are automatically passed.
- If your ship is **already full** (5 cards loaded), you are excluded from bidding entirely.
- If **nobody bids** (all pass), the lot is discarded with no gold changing hands.
- The winning bid is **immediately deducted** from the winner's gold. Spent gold is gone — it does not reset between rounds.

---

## 6. End-of-Round Scoring

At the end of each round, VP are awarded in two categories:

### Cargo Total Bonus

Each player's cargo total is the **sum of all card values** loaded that round. Players are ranked highest to lowest and awarded VP accordingly:

| Rank | 2 Players | 3 Players | 4 Players | 5 Players | 6 Players |
|---|---|---|---|---|---|
| 1st | 10 VP | 10 VP | 10 VP | 10 VP | 10 VP |
| 2nd |  0 VP |  5 VP |  7 VP |  7 VP |  7 VP |
| 3rd |  —    |  0 VP |  4 VP |  4 VP |  4 VP |
| 4th |  —    |  —    |  0 VP |  2 VP |  2 VP |
| 5th |  —    |  —    |  —    |  0 VP |  1 VP |
| 6th |  —    |  —    |  —    |  —    |  0 VP |

**Ties:** Tied players share the combined VP of the tied ranks, divided evenly (rounded down).

### Good Majority Bonus

For each of the five good types, VP are awarded based on who loaded the **most cards** of that type that round:

| Place | VP Awarded |
|---|---|
| 1st (most cards of that good) | 10 VP |
| 2nd (second most cards) | 5 VP |

**Ties:**
- If multiple players tie for **1st**, they share the combined 1st + 2nd pool (15 VP divided by the number of tied players, rounded down). No separate 2nd-place bonus is awarded.
- If multiple players tie for **2nd**, they share the 5 VP (rounded down).
- A good type with **zero cards** loaded by anyone awards no bonus at all.

> **Example:** Three players each load 2 Spice cards. They split 15 VP three ways = **5 VP each**.

---

## 7. Winning the Game

After Round 3 scoring, the player with the **highest total VP wins**. Gold remaining at the end of the game does not count toward victory — only accumulated VP matters.

In the event of a tied score, the tied players share the victory. The program displays the final standings clearly so players can determine the outcome.

---

## 8. Strategy Tips

**Manage your gold carefully.**
Gold spent is gone forever. Overpaying early can leave you unable to compete in later rounds. Sometimes the best move is to let your opponent win an expensive lot while you conserve resources for the next turn.

**Chase good majorities strategically.**
10 VP per good type per round adds up fast. If you are one card away from securing a majority, it may be worth overpaying. Conversely, if a rival is close to a majority, bidding them up forces them to overspend — or denies them the cards entirely.

**Think carefully before drawing a second card.**
Adding a second card raises the lot's total value — great if you win it, but it also means rivals get more value for their bid if they outbid you. Only draw a second card when you are confident you will win, or when you want to bait rivals into overspending.

**Ship space is finite — fill it wisely.**
You only have 5 slots per round. Filling your ship early with low-value cards locks you out of better lots later in the round. Prioritize high-value cards and cards that advance a good majority you are targeting.

**Think in VP-per-gold terms.**
A lot worth 3 cargo VP is probably not worth 15 gold. A lot that locks in a 10 VP good majority might be worth 12 gold. Always ask: "How many VP will this actually earn me at the end of the round?"

**Pass aggressively when the lot doesn't suit you.**
There is no shame in passing quickly. Staying in an auction to "drive up the price" costs you nothing — but make sure you can actually afford to win before making high bids, or a rival might call your bluff.

---

## 9. Building & Running the Program

### Running in VS Code

1. Install the [C/C++ extension](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools) if you haven't already
2. Open the project folder in VS Code (**File → Open Folder**)
3. Open `main.cpp`
4. Press **Ctrl+Shift+B** (Windows/Linux) or **Cmd+Shift+B** (macOS) to compile
5. Press **Ctrl+F5** to run — the game will launch in the integrated terminal at the bottom of the window

> **Tip:** Make sure your compiler is on your system PATH. On Windows with MinGW, this means adding the MinGW `bin` folder to your environment variables.

### In-Game Prompts Reference

| Prompt | What to enter |
|---|---|
| `How many players? (2-6)` | A whole number from 2 to 6 |
| `Name for Player N` | Any name, or press ENTER for a default |
| `Draw a second card? (1=Yes / 0=No)` | `1` to draw, `0` to skip |
| `Bid (X-Y), or 0 to pass` | A number in the shown range, or `0` to pass |
| `[Press ENTER to continue...]` | Press ENTER to advance to the next phase |

---

## 10. Project File Reference

| File | Description |
|---|---|
| `main.cpp` | Entry point; constructs and runs the game, handles top-level exceptions |
| `exceptions.h` | Custom exception hierarchy (`MediciException` and all subclasses) |
| `good.h` / `good.cpp` | `Good` enum and `goodName()` / `goodTag()` helper functions |
| `card.h` / `card.cpp` | `Card` class with operator overloads (`<<`, `<`, `==`) |
| `deck.h` / `deck.cpp` | `Deck` class — builds, shuffles, and deals the 26-card deck |
| `player.h` / `player.cpp` | `Player` class — ship management, gold, VP, bidding validation |
| `utils.h` / `utils.cpp` | Console display helpers (`header`, `separator`, `pause`, `getInt`) and VP scoring tables |
| `game.h` / `game.cpp` | `MediciGame` class — full game loop, auctions, round scoring, final results |
| `README.md` | This file |

---

*Based on Medici by Reiner Knizia. This is a fan-made console implementation for educational purposes.*
