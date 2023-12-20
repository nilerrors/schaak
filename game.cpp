//  Student:
//  Rolnummer:
//  Opmerkingen:
///              * i.p.v. de "schaak" functie direct te gebruiken
///                 heb ik ervoor gekozen om een aparte functie "causesSchaak" te maken die
///                 die een schaakstuk* en een positie (r, k) krijgt en gebaseerd daarop
///                 teruggeeft of dat het schaak is.

#include "game.h"

Game::Game() {
    for (int i = 0; i < BORD_SIZE; i++) {
        bord.push_back(nullptr);
    }
    setStartBord();
}

// Copy constructor
Game::Game(const Game& game) {
    for (int i = 0; i < BORD_SIZE; i++) {
        bord.push_back(nullptr);
    }

    turn = game.turn;
    movePosition = game.movePosition;
    for (auto &stuk : game.bord) {
        if (stuk == nullptr) continue;

        SchaakStuk* schaakStuk = nullptr;
        switch (stuk->piece().type()) {
            case Piece::Pawn:
                schaakStuk = new Pion(stuk->getKleur());
                break;
            case Piece::King:
                schaakStuk = new Koning(stuk->getKleur());
                break;
            case Piece::Bishop:
                schaakStuk = new Loper(stuk->getKleur());
                break;
            case Piece::Knight:
                schaakStuk = new Paard(stuk->getKleur());
                break;
            case Piece::Queen:
                schaakStuk = new Koningin(stuk->getKleur());
                break;
            case Piece::Rook:
                schaakStuk = new Toren(stuk->getKleur());
                break;
        }
        schaakStuk->setPositie(stuk->getPositie());
        setPiece(stuk->getPositie().first, stuk->getPositie().second, schaakStuk);
    }
}

Game::~Game() {
    for (auto &stuk : bord) {
        delete stuk;
        stuk = nullptr;
    }
}

// Zet het bord klaar; voeg de stukken op de juiste plaats toe
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

    std::pair<int, int> stukPositie = s->getPositie();

    if (stukPositie.first == r && stukPositie.second == k) return false;

    std::vector<std::pair<int, int>> zetten = s->geldige_zetten(*this);
//    for (const auto& zet : zetten) {
//        if (zet.first == r && zet.second == k) {
//            setPiece(stukPositie.first, stukPositie.second, nullptr);
//            setPiece(r, k, s);
//
//            return true;
//        }
//    }

    setPiece(r, k, nullptr);
    setPiece(r, k, s);
    setPiece(stukPositie.first, stukPositie.second, nullptr);

    return true;

//    return false;
}

// Geeft true als kleur schaak staat
bool Game::schaak(zw kleur) {
    std::pair<int, int> koningPosition = getKoningPosition(kleur);
    zw kleurComplement = kleur == zw::wit ? zw::zwart : zw::wit;

    for (const auto &stuk : bord) {
        if (stuk == nullptr) continue;
        if (stuk->getKleur() == kleurComplement) {
            for (const auto &zet : stuk->alle_mogelijke_zetten(*this)) {
                if (outOfBounds(zet.first, zet.second)) continue;
                if (zet.first == koningPosition.first && zet.second == koningPosition.second) {
                    return true;
                }
            }
        }
    }

    return false;
}

// Geeft true als kleur schaakmat staat
bool Game::schaakmat(zw kleur) { return false; }

// Geeft true als kleur pat staat
// (pat = geen geldige zet mogelijk, maar kleur staat niet schaak;
// dit resulteert in een gelijkspel)
bool Game::pat(zw kleur) { return false; }

// Geeft een pointer naar het schaakstuk dat op rij r, kolom k staat
// Als er geen schaakstuk staat op deze positie, geef nullptr terug
SchaakStuk* Game::getPiece(int r, int k) const {
    if (outOfBounds(r, k)) return nullptr;
    return bord[r * COL_SIZE + k];
}

// Zet het schaakstuk waar s naar verwijst neer op rij r, kolom k.
// Als er al een schaakstuk staat, wordt het overschreven.
// Bewaar in jouw datastructuur de *pointer* naar het schaakstuk,
// niet het schaakstuk zelf.
void Game::setPiece(int r, int k, SchaakStuk* s) {
    if (outOfBounds(r, k)) return;
    if (s != nullptr) {
        s->setPositie(r, k);
    }
    bord[r * COL_SIZE + k] = s;
}

bool Game::outOfBounds(int r, int k) const {
    return r < 0 || k < 0 || r >= ROW_SIZE || k >= COL_SIZE;
}

bool Game::getTurn() const { return turn; }

const std::pair<int, int>& Game::getMovePosition() const {
    return movePosition;
}

void Game::changeTurn() {
    if (turn == zw::wit)
        turn = zw::zwart;
    else
        turn = zw::wit;
}

void Game::clearMovePosition() { movePosition = std::make_pair(-1, -1); }

void Game::setMovePosition(int r, int k) {
    movePosition = std::make_pair(r, k);
}

bool Game::movePositionUnset() const {
    return movePosition.first == -1 && movePosition.second == -1;
}

std::pair<int, int> Game::getKoningPosition(zw kleur) const {
    std::pair<int, int> position = std::make_pair(-1, -1);
    for (const auto &stuk : bord) {
        if (stuk == nullptr) continue;
        if (stuk->piece().type() == Piece::King && stuk->getKleur() == kleur) {
            position = std::make_pair(stuk->getPositie().first, stuk->getPositie().second);
        }
    }

    return position;
}

bool Game::causesSchaak(SchaakStuk *s, int r, int k) const {
    if (s == nullptr) return false;
    std::pair<int, int> stukPositie = s->getPositie();
    if (stukPositie.first == r && stukPositie.second == k) return false;

    // Nieuw spel die de huidige spel data meekrijgt,
    // zodat we niet alle functies non-const moeten maken
    // en ook de huidige data niet overschrijven
    Game game(*this);
    SchaakStuk* gameSchaakstuk = game.getPiece(stukPositie.first, stukPositie.second);

    game.setPiece(r, k, gameSchaakstuk);
    game.setPiece(stukPositie.first, stukPositie.second, nullptr);

    return game.schaak(gameSchaakstuk->getKleur());
}
