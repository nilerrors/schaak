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
    en_passant,
    pawn_promotion,
//    rochade
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
    // Dit is voor de stukken die er vroeger waren en weg zijn door een beweging te bewaren
    // bv. bij promotie de pion
    std::vector<SchaakStuk *> pieces;
    // Dit is om de stukken die opgegeten worden door een beweging van een schaakstuk te bewaren.
    // zodat bij undoMove, de schaakstuk herteld kan worden op zijn eigen positie.
    std::vector<SchaakStuk *> kills;

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
