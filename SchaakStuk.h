//  Student:
//  Rolnummer:
//  Opmerkingen: (bvb aanpassingen van de opgave)
//

#ifndef SCHAKEN_SCHAAKSTUK_H
#define SCHAKEN_SCHAAKSTUK_H
#include <guicode/chessboard.h>

class Game;

enum zw { zwart, wit };

class SchaakStuk {
public:
    SchaakStuk(zw kleur) : kleur(kleur) {}

    virtual Piece piece() const = 0;  // Verander deze functie niet!
                                      // Deze functie wordt gebruikt door
                                      // setItem(x,y,SchaakStuk*) van
                                      // SchaakGUI

    zw getKleur() const { return kleur; }

    std::vector<std::pair<int, int>> geldige_zetten(const Game& game);

    const std::pair<int, int>& getPositie() const { return positie; }
    void setPositie(const std::pair<int, int>& newPositie) {
        positie = newPositie;
    }
    void setPositie(int rij, int kolom) {
        positie = std::make_pair(rij, kolom);
    }

//protected:
    virtual std::vector<std::pair<int, int>> alle_mogelijke_zetten(const Game& game) const = 0;

private:
    zw kleur;
    std::pair<int, int> positie = std::make_pair(-1, -1);
};

class Pion : public SchaakStuk {
public:
    Pion(zw kleur) : SchaakStuk(kleur) {}
    virtual Piece piece() const override {
        return Piece(Piece::Pawn,
                     getKleur() == wit ? Piece::White : Piece::Black);
    }

    virtual std::vector<std::pair<int, int>> alle_mogelijke_zetten(
        const Game& game) const;
};

class Toren : public SchaakStuk {
public:
    Toren(zw kleur) : SchaakStuk(kleur) {}

    Piece piece() const override {
        return Piece(Piece::Rook,
                     getKleur() == wit ? Piece::White : Piece::Black);
    }

    virtual std::vector<std::pair<int, int>> alle_mogelijke_zetten(
        const Game& game) const;
};

class Paard : public SchaakStuk {
public:
    Paard(zw kleur) : SchaakStuk(kleur) {}

    Piece piece() const override {
        return Piece(Piece::Knight,
                     getKleur() == wit ? Piece::White : Piece::Black);
    }

    virtual std::vector<std::pair<int, int>> alle_mogelijke_zetten(
        const Game& game) const;
};

class Loper : public SchaakStuk {
public:
    Loper(zw kleur) : SchaakStuk(kleur) {}

    Piece piece() const override {
        return Piece(Piece::Bishop,
                     getKleur() == wit ? Piece::White : Piece::Black);
    }

    virtual std::vector<std::pair<int, int>> alle_mogelijke_zetten(
        const Game& game) const;
};

class Koning : public SchaakStuk {
public:
    Koning(zw kleur) : SchaakStuk(kleur) {}

    Piece piece() const override {
        return Piece(Piece::King,
                     getKleur() == wit ? Piece::White : Piece::Black);
    }

    virtual std::vector<std::pair<int, int>> alle_mogelijke_zetten(
        const Game& game) const;
};

class Koningin : public SchaakStuk {
public:
    Koningin(zw kleur) : SchaakStuk(kleur) {}

    Piece piece() const override {
        return Piece(Piece::Queen,
                     getKleur() == wit ? Piece::White : Piece::Black);
    }

    virtual std::vector<std::pair<int, int>> alle_mogelijke_zetten(
        const Game& game) const;
};

#endif  // SCHAKEN_SCHAAKSTUK_H
