//  Student:
//  Rolnummer:
//  Opmerkingen: (bvb aanpassingen van de opgave)
//

#ifndef SCHAAK_GAME_H
#define SCHAAK_GAME_H

#include <vector>
#include "consts.h"
#include "SchaakStuk.h"
#include "Position.h"

class Game {
    // variabelen om de status van het spel/bord te bewaren
    zw turn = zw::wit;
    Position movePosition = Position(-1, -1); // -1, -1; niet geselecteerd.
    bool gameEnded = false;
    std::vector<FromTo> moves;
    int currentMove = -1;

    bool AI_GAME = true;

public:
    Game();
    ~Game();
    Game(const Game& game);  // copy constructor

    bool isAI_game() const { return AI_GAME; }
    void AI_move();

    bool move(SchaakStuk* s, Position into, bool saveMove = true);  // Verplaats stuk s naar rij r en kolom k

    const std::vector<FromTo>& allMoves() const { return moves; }
    int currentMoveIndex() const { return currentMove; }
    void clearMoves() { moves.clear(); currentMove = -1; }

    // Voor rokade
//    bool hasMoved(const SchaakStuk* stuk) const;

    bool undoMove();
    bool redoMove();

    bool causesSchaak(const SchaakStuk* stuk, Position into) const { return causesSchaak(stuk, into, stuk->getKleur()); }
    bool causesSchaak(const SchaakStuk* stuk, Position into, zw kant) const;
    bool causesSchaakmat(const SchaakStuk* stuk, Position into, zw kant) const;
    bool schaak(zw kleur) const;
    bool schaakmat(zw kleur) const;
    bool pat(zw kleur) const;
    void setStartBord();

    // threats and kills
    Positions threats() const;
    Positions kills(SchaakStuk* stuk) const;

    std::vector<SchaakStuk *> alleSchaakstukken(zw kleur) const;
    const FromTo* lastMove() const;

    void endGame() { gameEnded = true; }
    bool getGameEnded() { return gameEnded; }

    bool outOfBounds(int r, int k) const;

    SchaakStuk* getPiece(int r, int k) const;
    void setPiece(int r, int k, SchaakStuk* s);

    zw getTurn() const;
    const Position& getMovePosition() const;
    bool movePositionUnset() const;
    void changeTurn();
    void clearMovePosition();
    void setMovePosition(int r, int k);

    Position getKoningPosition(zw kleur) const;

private:
    // 8 rijen, 8 kolommen = 64 plaatsen
    // het aantal plaatsen is statisch en kan veranderen
    //
    // Een element op een bepaalde plaats kan geraadpleegd worden,
    // door de volgende formule toe te passen:
    // rij * COL_SIZE + kolom
    std::vector<SchaakStuk *> bord;
};

#endif  // SCHAKEN_GAME_H
