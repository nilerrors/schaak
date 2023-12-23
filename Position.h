//
// Created by nilerrors on 21/12/2023.
//

#ifndef SCHAKEN_POSITION_H
#define SCHAKEN_POSITION_H

#include <utility>
#include <vector>

class SchaakStuk;

enum MoveType {
    none,
    normal,
    en_passant
};

//typedef std::pair<int, int> Position;

class Position : public std::pair<int, int> {
public:
    MoveType type;
    Position() : std::pair<int, int>(-1, -1), type(MoveType::none) {}
    Position(int x, int y) : std::pair<int, int>(x, y), type(MoveType::none) {}
    Position(int x, int y, MoveType type) : std::pair<int, int>(x, y), type(type) {}
};

typedef std::vector<Position> Positions;


struct FromTo {
    SchaakStuk* val;
    Position from;
    Position to;
    MoveType type;
    // Dit is gebruikt om de waarden van de speciale moves te bewaren
    // bv. bij en passant, moeten we weten welke schaakstuk er verwijderd is,
    // zodat bij undoMove, dit hersteld kan worden.
    std::vector<SchaakStuk*> pieces;

    FromTo(SchaakStuk* s, const Position& f, const Position& t) {
        val = s;
        from = f;
        to = t;
        type = MoveType::normal;
    }

    FromTo(SchaakStuk* s, const Position& f, const Position& t, MoveType typ) {
        val = s;
        from = f;
        to = t;
        type = typ;
    }
};

#endif //SCHAKEN_POSITION_H
