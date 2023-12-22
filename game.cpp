//  Student:
//  Rolnummer:
//  Opmerkingen:
///              * i.p.v. de "schaak" functie direct te gebruiken
///                 heb ik ervoor gekozen om een aparte functie "causesSchaak" te maken die
///                 die een schaakstuk* en een positie (r, k) krijgt en gebaseerd daarop
///                 teruggeeft of dat het schaak is.

#include <iostream>
#include "game.h"

std::string pieceToString(Piece piece) {
    switch (piece.type()) {
        case Piece::Pawn:
            return "Pion";
        case Piece::King:
            return "Koning";
        case Piece::Bishop:
            return "Loper";
        case Piece::Knight:
            return "Paard";
        case Piece::Queen:
            return "Koningin";
        case Piece::Rook:
            return "Toren";
    }
    return "Niets";
}

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
bool Game::move(SchaakStuk* s, int r, int k, bool saveMove) {
    // Deze functie gaat ervan uit dat de gegeven
    // positie een geldige positie is om naar te bewegen
    // met het gegeven schaakstuk

    if (outOfBounds(r, k)) return false;
    if (s == nullptr) return false;

    Position stukPositie = s->getPositie();

    if (stukPositie.first == r && stukPositie.second == k) return false;

    if (saveMove) {
        currentMove++;
        // als het de "eerste" move is,
        // overschrijf alle moves,
        // zodat je niet meer terug kan gaan,
        // naar de vorige "verwijderde" moves
        if (currentMove == 0) {
            moves.clear();
        }
        moves.emplace(moves.cbegin() + currentMove,
                      FromTo<SchaakStuk*>{
            s,
            std::make_pair(stukPositie.first, stukPositie.second),
            std::make_pair(r, k)
        });
    }

    setPiece(r, k, nullptr);
    setPiece(r, k, s);
    setPiece(stukPositie.first, stukPositie.second, nullptr);

    return true;
}

// Geeft true als kleur schaak staat
bool Game::schaak(zw kleur) {
    Position koningPosition = getKoningPosition(kleur);
    zw kleurComplement = kleur == zw::wit ? zw::zwart : zw::wit;

    for (const auto &stuk : bord) {
        if (stuk == nullptr) continue;
        if (stuk->getKleur() == kleurComplement) {
            for (const auto &zet : stuk->alle_mogelijke_zetten(*this)) {
                if (outOfBounds(zet.first, zet.second)) continue;
                if (zet.first == koningPosition.first && zet.second == koningPosition.second) {
                    std::cout << (kleurComplement == zw::wit ? "Witte " : "Zwarte ")
                    << pieceToString(stuk->piece())
                    << " (" << stuk->getPositie().first << ", " << stuk->getPositie().second << ")"
                    << " staat in schaak positie tegenover de "
                    << (kleur == zw::wit ? "witte " : "zwarte ") << "Koning"
                    << " (" << koningPosition.first << ", " << koningPosition.second << ") "
                    << std::endl;

                    return true;
                }
            }
        }
    }

    return false;
}

// Geeft true als kleur schaakmat staat
bool Game::schaakmat(zw kleur) {
    // Nieuw spel die de huidige spel data meekrijgt,
    // zodat we niet alle functies non-const moeten maken
    // en ook de huidige data niet overschrijven
    Game game(*this);
    if (game.pat(kleur)) return false;

    for (auto &s : game.bord) {
        if (s == nullptr) continue;
        if (s->getKleur() != kleur) continue;
        Position stukPositie = s->getPositie();

        for (auto &zet : s->geldige_zetten(game)) {
            SchaakStuk* gameSchaakstuk = game.getPiece(stukPositie.first, stukPositie.second);

            game.setPiece(zet.first, zet.second, gameSchaakstuk);
            game.setPiece(stukPositie.first, stukPositie.second, nullptr);

            if (!game.schaak(gameSchaakstuk->getKleur())) {
                return false;
            }
            std::cout << "als "
            << (gameSchaakstuk->getKleur() == zw::wit ? "wit " : "zwart ")
            << pieceToString(gameSchaakstuk->piece())
            << " (" << stukPositie.first << ", " << stukPositie.second << ") "
            << "bewogen wordt naar (" << zet.first << ", " << zet.second << ")"
            << std::endl;

            // herstel originele positie
            game.setPiece(stukPositie.first, stukPositie.second, gameSchaakstuk);
            game.setPiece(zet.first, zet.second, nullptr);
        }
    }

    return true;
}

// Geeft true als kleur pat staat
// (pat = geen geldige zet mogelijk, maar kleur staat niet schaak;
// dit resulteert in een gelijkspel)
bool Game::pat(zw kleur) {
    // Nieuw spel die de huidige spel data meekrijgt,
    // zodat we niet alle functies non-const moeten maken
    // en ook de huidige data niet overschrijven
    Game game(*this);

    if (schaak(kleur)) return false;

    for (auto &s : game.bord) {
        if (s == nullptr) continue;
        if (s->getKleur() != kleur) continue;
        if (!s->geldige_zetten(game).empty()) return false;
    }

    return true;
}

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

zw Game::getTurn() const { return turn; }

const Position& Game::getMovePosition() const {
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

Position Game::getKoningPosition(zw kleur) const {
    Position kingPosition = std::make_pair(-1, -1);
    for (const auto &stuk : bord) {
        if (stuk == nullptr) continue;
        if (stuk->piece().type() == Piece::King && stuk->getKleur() == kleur) {
            kingPosition = std::make_pair(stuk->getPositie().first, stuk->getPositie().second);
        }
    }

    return kingPosition;
}

bool Game::causesSchaak(SchaakStuk *s, int r, int k) const {
    if (s == nullptr) return false;
    Position stukPositie = s->getPositie();
    if (stukPositie.first == r && stukPositie.second == k) return false;

    // Nieuw spel die de huidige spel data meekrijgt,
    // zodat we niet alle functies non-const moeten maken
    // en ook de huidige data niet overschrijven
    Game game(*this);
    SchaakStuk* gameSchaakstuk = game.getPiece(stukPositie.first, stukPositie.second);

    game.setPiece(r, k, gameSchaakstuk);
    game.setPiece(stukPositie.first, stukPositie.second, nullptr);

    if (game.schaak(gameSchaakstuk->getKleur())) {
        std::cout << "\tals "
                  << (gameSchaakstuk->getKleur() == zw::wit ? "wit " : "zwart ")
                  << pieceToString(gameSchaakstuk->piece())
                  << " (" << stukPositie.first << ", " << stukPositie.second << ") "
                  << "bewogen wordt naar (" << r << ", " << k << ")"
                  << std::endl;

        return true;
    }

    return false;
}

Positions Game::threats() const {
    // geeft alle bedreigde schaakstukken
    Positions all_threats;
    for (auto &stuk : bord) {
        if (stuk == nullptr) continue;
        for (const auto &zet : stuk->geldige_zetten(*this)) {
            SchaakStuk* opPositie = getPiece(zet.first, zet.second);
            if (opPositie == nullptr) continue;
            if (opPositie->getKleur() != stuk->getKleur()) {
                all_threats.push_back(zet);
            }
        }
    }

    return all_threats;
}

Positions Game::kills(SchaakStuk* s) const {
    // pair van position en schaakstuk is bewaard voor de output onder
    std::vector<std::pair<Position, SchaakStuk*>> all_kills;
    auto sGeldigeZetten = s->geldige_zetten(*this);

    for (auto &stuk : alleSchaakstukken(
            s->getKleur() == zw::wit ? zw::zwart : zw::wit)) {
        for (const auto &zet : stuk->geldige_zetten(*this)) {
            if (stuk->piece().type() == Piece::Pawn && stuk->getPositie().second == zet.second) {
                // de pion kan niet recht voor hem iemand vermoorden
                // die zetten moeten we skippen
                if (stuk->getKleur() == zw::wit &&
                    (stuk->getPositie().first - 1 == zet.first ||
                        stuk->getPositie().first - 2 == zet.first)) {
                    continue;
                } else if (stuk->getKleur() == zw::zwart &&
                            (stuk->getPositie().first + 1 == zet.first ||
                            stuk->getPositie().first + 2 == zet.first))
                    continue;
            }

            SchaakStuk* opPositie = getPiece(zet.first, zet.second);
            for (const auto &sZet : sGeldigeZetten) {
                if (sZet.first == zet.first && sZet.second == zet.second) {
                    all_kills.push_back(std::make_pair(zet, stuk));
                }
            }
        }
    }

    std::cout << "Totaal aantal kills van "
    << (s->getKleur() == zw::wit ? "wit " : "zwart ")
    << pieceToString(s->piece()) << " : "
    << all_kills.size()
    << std::endl;
    for (auto zet : all_kills) {
        std::cout << "\t(" << zet.first.first << ", " << zet.first.second << ")"
        << " door " << (zet.second->getKleur() == zw::wit ? "wit " : "zwart ")
        << pieceToString(zet.second->piece())
        << " (" << zet.second->getPositie().first << ", " << zet.second->getPositie().second << ") "
        << std::endl;
    }

    Positions kills;
    for (const auto &kill : all_kills) {
        kills.push_back(kill.first);
    }

    return kills;
}

std::vector<SchaakStuk *> Game::alleSchaakstukken(zw kleur) const {
    std::vector<SchaakStuk *> alleStukken;
    for (auto &stuk : bord) {
        if (stuk == nullptr) continue;
        if (stuk->getKleur() == kleur) {
            alleStukken.push_back(stuk);
        }
    }
    return alleStukken;
}

bool Game::undoMove() {
    if (currentMove < 0) {
        return false;
    }

    move(moves[currentMove].val, moves[currentMove].from.first, moves[currentMove].from.second, false);

    currentMove--;

    changeTurn();

    return true;
}

bool Game::redoMove() {
    if (moves.empty() || currentMove + 1 >= moves.size()) {
        return false;
    }

    currentMove++;

    move(moves[currentMove].val, moves[currentMove].to.first, moves[currentMove].to.second, false);

    changeTurn();

    return true;
}

FromTo<SchaakStuk *> Game::lastMove() const {
    if (currentMove < 0 || moves.size() == 0) {
        return FromTo<SchaakStuk *>{
                nullptr,
                std::make_pair(-1, -1),
                std::make_pair(-1, -1)
        };
    }
    return moves[currentMove];
}
