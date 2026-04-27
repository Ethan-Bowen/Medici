#pragma once
// ============================================================
//  exceptions.h  -  Custom exception hierarchy for Medici
// ============================================================

#include <stdexcept>
#include <string>

class MediciException : public std::runtime_error {
public:
    explicit MediciException(const std::string& msg)
        : std::runtime_error("[Medici] " + msg) {}
};

class InvalidBidException : public MediciException {
public:
    explicit InvalidBidException(const std::string& msg)
        : MediciException("Invalid bid - " + msg) {
    }
};

class InvalidInputException : public MediciException {
public:
    explicit InvalidInputException(const std::string& msg)
        : MediciException("Invalid input - " + msg) {
    }
};

class ShipFullException : public MediciException {
public:
    ShipFullException()
        : MediciException("Ship is already full (max 5 cards).") {
    }
};

class EmptyDeckException : public MediciException {
public:
    EmptyDeckException()
        : MediciException("Tried to draw from an empty deck.") {
    }
};
