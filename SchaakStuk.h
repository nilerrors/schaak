//  Student:
//  Rolnummer:
//  Opmerkingen: (bvb aanpassingen van de opgave)
//

#ifndef SCHAKEN_SCHAAKSTUK_H
#define SCHAKEN_SCHAAKSTUK_H
#include <guicode/chessboard.h>

#include "Position.h"

class Game;

enum zw {
    zwart, wit
};

class SchaakStuk {
public:
    SchaakStuk(zw kleur) : kleur(kleur) {}

    virtual ~SchaakStuk() {}

    virtual Piece piece() const = 0;  // Verander deze functie niet!
                                      // Deze functie wordt gebruikt door
                                      // setItem(x,y,SchaakStuk*) van
                                      // SchaakGUI

    zw getKleur() const { return kleur; }

    Positions geldige_zetten(const Game& game) const;

    const Position& getPositie() const { return positie; }
    void setPositie(const Position& newPositie) {
        positie = newPositie;
    }
    void setPositie(int rij, int kolom) {
        positie = Position(rij, kolom);
    }

//protected:
    virtual Positions alle_mogelijke_zetten(const Game& game) const = 0;

private:
    zw kleur;
    Position positie = Position(-1, -1);
};

class Pion : public SchaakStuk {
public:
    Pion(zw kleur) : SchaakStuk(kleur) {}
    virtual Piece piece() const override {
        return Piece(Piece::Pawn,
                     getKleur() == wit ? Piece::White : Piece::Black);
    }

    Positions alle_mogelijke_zetten(const Game& game) const override;
};

class Toren : public SchaakStuk {
public:
    Toren(zw kleur) : SchaakStuk(kleur) {}

    Piece piece() const override {
        return Piece(Piece::Rook,
                     getKleur() == wit ? Piece::White : Piece::Black);
    }

    Positions alle_mogelijke_zetten(const Game& game) const override;
};

class Paard : public SchaakStuk {
public:
    Paard(zw kleur) : SchaakStuk(kleur) {}

    Piece piece() const override {
        return Piece(Piece::Knight,
                     getKleur() == wit ? Piece::White : Piece::Black);
    }

    Positions alle_mogelijke_zetten(const Game& game) const override;
};

class Loper : public SchaakStuk {
public:
    Loper(zw kleur) : SchaakStuk(kleur) {}

    Piece piece() const override {
        return Piece(Piece::Bishop,
                     getKleur() == wit ? Piece::White : Piece::Black);
    }

    Positions alle_mogelijke_zetten(const Game& game) const override;
};

class Koning : public SchaakStuk {
public:
    Koning(zw kleur) : SchaakStuk(kleur) {}

    Piece piece() const override {
        return Piece(Piece::King,
                     getKleur() == wit ? Piece::White : Piece::Black);
    }

    Positions alle_mogelijke_zetten(const Game& game) const override;
};

class Koningin : public SchaakStuk {
public:
    Koningin(zw kleur) : SchaakStuk(kleur) {}

    Piece piece() const override {
        return Piece(Piece::Queen,
                     getKleur() == wit ? Piece::White : Piece::Black);
    }

    Positions alle_mogelijke_zetten(const Game& game) const override;
};

#endif  // SCHAKEN_SCHAAKSTUK_H
