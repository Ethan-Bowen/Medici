// ============================================================
//  main.cpp  -  Entry point for Medici
// ============================================================
#include "game.h"
#include "exceptions.h"
#include <iostream>

int main() {
    try {
        MediciGame game;
        game.run();
    }
    catch (const MediciException& e) {
        std::cerr << "\n" << e.what() << "\n";
        return 1;
    }
    catch (const std::exception& e) {
        std::cerr << "\n[Error] " << e.what() << "\n";
        return 1;
    }
    return 0;
}
