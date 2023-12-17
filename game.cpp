//  Student:
//  Rolnummer:
//  Opmerkingen: (bvb aanpassingen van de opgave)
//

#include "game.h"

Game::Game() {
    for (int i = 0; i < BORD_SIZE; i++) {
        bord[i] = nullptr;
    }
    setStartBord();
}

Game::~Game() {
    for (int i = 0; i < BORD_SIZE; i++) {
        delete bord[i];
        bord[i] = nullptr;
    }
}

// Zet het bord klaar; voeg de stukken op de jusite plaats toe
void Game::setStartBord() {
    // Zet de zwarte schaakstukken
    // in de eerste twee rijen
    // Zet de witte schaakstukken
    // in de laatste twee rijen
    //
    // Alle pionnen staan in de tweede en zevende rij

    for (int i = 0; i < COL_SIZE; i++) {
        // Alle pionnen in de tweede en zevende rij
        setPiece(1, i, new Pion(zw::zwart));
        setPiece(6, i, new Pion(zw::wit));

        // Zet ook alle legen rijen op nullptr
        setPiece(2, i, nullptr);
        setPiece(3, i, nullptr);
        setPiece(4, i, nullptr);
        setPiece(5, i, nullptr);
    }
    // Alle torens
    setPiece(0, 0, new Toren(zw::zwart));
    setPiece(0, 7, new Toren(zw::zwart));
    setPiece(7, 0, new Toren(zw::wit));
    setPiece(7, 7, new Toren(zw::wit));
    // Alle paarden
    setPiece(0, 1, new Paard(zw::zwart));
    setPiece(0, 6, new Paard(zw::zwart));
    setPiece(7, 1, new Paard(zw::wit));
    setPiece(7, 6, new Paard(zw::wit));
    // Alle lopers
    setPiece(0, 2, new Loper(zw::zwart));
    setPiece(0, 5, new Loper(zw::zwart));
    setPiece(7, 2, new Loper(zw::wit));
    setPiece(7, 5, new Loper(zw::wit));
    // De koninginnen
    setPiece(0, 3, new Koningin(zw::zwart));
    setPiece(7, 3, new Koningin(zw::wit));
    // De koningen
    setPiece(0, 4, new Koning(zw::zwart));
    setPiece(7, 4, new Koning(zw::wit));
}

// Verplaats stuk s naar positie (r,k)
// Als deze move niet mogelijk is, wordt false teruggegeven
// en verandert er niets aan het schaakbord.
// Anders wordt de move uitgevoerd en wordt true teruggegeven
bool Game::move(SchaakStuk* s, int r, int k) {
    if (outOfBounds(r, k)) return false;
    if (s == nullptr) return false;
    if (s->getPositie().first == r && s->getPositie().second == k) return false;

    std::vector<std::pair<int, int>> zetten = s->geldige_zetten(*this);
    for (const auto& zet : zetten) {
        if (zet.first == r && zet.second == k) {
            setPiece(s->getPositie().first, s->getPositie().second, nullptr);
            setPiece(r, k, s);
            return true;
        }
    }

    return false;
}

// Geeft true als kleur schaak staat
bool Game::schaak(zw kleur) { return false; }

// Geeft true als kleur schaakmat staat
bool Game::schaakmat(zw kleur) { return false; }

// Geeft true als kleur pat staat
// (pat = geen geldige zet mogelijk, maar kleur staat niet schaak;
// dit resulteert in een gelijkspel)
bool Game::pat(zw kleur) { return false; }

// Geeft een pointer naar het schaakstuk dat op rij r, kolom k staat
// Als er geen schaakstuk staat op deze positie, geef nullptr terug
SchaakStuk* Game::getPiece(int r, int k) const {
    // Hier komt jouw code om op te halen welk stuk op rij r, kolom k staat
    if (outOfBounds(r, k)) return nullptr;
    return bord[r * COL_SIZE + k];
}

// Zet het schaakstuk waar s naar verwijst neer op rij r, kolom k.
// Als er al een schaakstuk staat, wordt het overschreven.
// Bewaar in jouw datastructuur de *pointer* naar het schaakstuk,
// niet het schaakstuk zelf.
void Game::setPiece(int r, int k, SchaakStuk* s) {
    // Hier komt jouw code om een stuk neer te zetten op het bord
    if (outOfBounds(r, k)) return;
    delete bord[r * COL_SIZE + k];
    bord[r * COL_SIZE + k] = nullptr;

    s->setPositie(r, k);
    bord[r * COL_SIZE + k] = s;
}

bool Game::outOfBounds(int r, int k) const {
    return r < 0 || k < 0 || r >= ROW_SIZE || k >= COL_SIZE;
}

bool Game::getTurn() const { return turn; }

const std::pair<int, int>& Game::getMovePosition() const {
    return movePosition;
}

// int Game::getMovePositionRij() const { return movePositionRij; }

// int Game::getMovePositionKolom() const { return movePositionKolom; }

void Game::changeTurn() {
    if (turn == zw::wit)
        turn = zw::zwart;
    else
        turn = zw::wit;
}

void Game::clearMovePosition() {
    movePosition = std::make_pair(-1, -1);
    // movePositionRij = -1;
    // movePositionKolom = -1;
}

void Game::setMovePosition(int r, int k) {
    movePosition = std::make_pair(r, k);
    // movePositionRij = r;
    // movePositionKolom = r;
}

bool Game::movePositionUnset() const {
    return movePosition.first == -1 && movePosition.second == -1;
    // return movePositionRij == -1 && movePositionKolom == -1;
}
