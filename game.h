//  Student:
//  Rolnummer:
//  Opmerkingen: (bvb aanpassingen van de opgave)
//

#ifndef SCHAAK_GAME_H
#define SCHAAK_GAME_H

#include "consts.h"
#include "SchaakStuk.h"
#include "ArrayList.h"
#include "MatrixPair.h"

class Game {
    zw turn = zw::wit;
    MatrixPair movePosition = MatrixPair(-1, -1); // -1, -1; niet geselecteerd.

public:
    Game();
    ~Game();

    bool move(SchaakStuk* s,int r, int k); // Verplaats stuk s naar rij r en kolom k

    bool schaak(zw kleur);
    bool schaakmat(zw kleur);
    bool pat(zw kleur);
    void setStartBord();

    bool outOfBounds(int r, int k) const;

    SchaakStuk* getPiece(int r, int k) const;
    void setPiece(int r, int k, SchaakStuk* s);

    bool getTurn() const;
    const MatrixPair& getMovePosition() const;
    bool movePositionUnset() const;
    void changeTurn();
    void clearMovePosition();
    void setMovePosition(int r, int k);

private:
    // 8 rijen, 8 kolommen = 64 plaatsen
    // het aantal plaatsen is statisch en kan veranderen
    //
    // Array zorgt voor effecientie.
    // Een element op een bepaalde plaats kan geraadpleegd worden,
    // door de volgende formule toe te passen:
    // rij * COL_SIZE + kolom
    SchaakStuk* bord[64];
};

#endif //SCHAKEN_GAME_H


