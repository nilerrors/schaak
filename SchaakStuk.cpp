//  Student:
//  Rolnummer:
//  Opmerkingen:
///              * geldige_zetten is een non-virtual functie
///                die de virtual functie alle_mogelijke_zetten
///                gebruikt
///

#include "SchaakStuk.h"

#include "game.h"

Positions Pion::alle_mogelijke_zetten(const Game& game) const {
    Positions zetten;

    int currentRow = this->getPositie().first;
    int currentCol = this->getPositie().second;

    if (getKleur() == zw::wit) {
        if (game.getPiece(currentRow - 1, currentCol) == nullptr) {
            zetten.push_back(std::make_pair(currentRow - 1, currentCol));
            if (currentRow == 6) {
                if (game.getPiece(currentRow - 2, currentCol) == nullptr) {
                    zetten.push_back(std::make_pair(currentRow - 2, currentCol));
                }
            }
        }
        if (game.getPiece(currentRow - 1, currentCol - 1) != nullptr &&
            game.getPiece(currentRow - 1, currentCol - 1)->getKleur() ==
                zw::zwart) {
            zetten.push_back(std::make_pair(currentRow - 1, currentCol - 1));
        }
        if (game.getPiece(currentRow - 1, currentCol + 1) != nullptr &&
            game.getPiece(currentRow - 1, currentCol + 1)->getKleur() ==
                zw::zwart) {
            zetten.push_back(std::make_pair(currentRow - 1, currentCol + 1));
        }
    } else {
        if (game.getPiece(currentRow + 1, currentCol) == nullptr) {
            zetten.push_back(std::make_pair(currentRow + 1, currentCol));
            if (currentRow == 1) {
                if (game.getPiece(currentRow + 2, currentCol) == nullptr) {
                    zetten.push_back(std::make_pair(currentRow + 2, currentCol));
                }
            }
        }
        if (game.getPiece(currentRow + 1, currentCol - 1) != nullptr &&
            game.getPiece(currentRow + 1, currentCol - 1)->getKleur() ==
                zw::wit) {
            zetten.push_back(std::make_pair(currentRow + 1, currentCol - 1));
        }
        if (game.getPiece(currentRow + 1, currentCol + 1) != nullptr &&
            game.getPiece(currentRow + 1, currentCol + 1)->getKleur() ==
                zw::wit) {
            zetten.push_back(std::make_pair(currentRow + 1, currentCol + 1));
        }
    }

    return zetten;
}

Positions Toren::alle_mogelijke_zetten(const Game& game) const {
    Positions zetten;

    int currentRow = this->getPositie().first;
    int currentCol = this->getPositie().second;

    // alle mogelijke zetten naar boven
    for (int i = currentRow - 1; i < ROW_SIZE; i--) {
        if (game.outOfBounds(i, currentCol)) break;
        if (game.getPiece(i, currentCol) == nullptr) {
            zetten.push_back(std::make_pair(i, currentCol));
        } else if (game.getPiece(i, currentCol)->getKleur() != getKleur()) {
            zetten.push_back(std::make_pair(i, currentCol));
            break;
        } else {
            break;
        }
    }
    // alle mogelijke zetten naar beneden
    for (int i = currentRow + 1; i < ROW_SIZE; i++) {
        if (game.outOfBounds(i, currentCol)) break;
        if (game.getPiece(i, currentCol) == nullptr) {
            zetten.push_back(std::make_pair(i, currentCol));
        } else if (game.getPiece(i, currentCol)->getKleur() != getKleur()) {
            zetten.push_back(std::make_pair(i, currentCol));
            break;
        } else {
            break;
        }
    }
    // alle mogelijke zetten naar links
    for (int i = currentCol - 1; i < COL_SIZE; i--) {
        if (game.outOfBounds(currentRow, i)) break;
        if (game.getPiece(currentRow, i) == nullptr) {
            zetten.push_back(std::make_pair(currentRow, i));
        } else if (game.getPiece(currentRow, i)->getKleur() != getKleur()) {
            zetten.push_back(std::make_pair(currentRow, i));
            break;
        } else {
            break;
        }
    }
    // alle mogelijke zetten naar rechts
    for (int i = currentCol + 1; i < COL_SIZE; i++) {
        if (game.outOfBounds(currentRow, i)) break;
        if (game.getPiece(currentRow, i) == nullptr) {
            zetten.push_back(std::make_pair(currentRow, i));
        } else if (game.getPiece(currentRow, i)->getKleur() != getKleur()) {
            zetten.push_back(std::make_pair(currentRow, i));
            break;
        } else {
            break;
        }
    }

    return zetten;
}

Positions Paard::alle_mogelijke_zetten(const Game& game) const {
    Positions zetten;

    int currentRow = this->getPositie().first;
    int currentCol = this->getPositie().second;

    // alle mogelijke zetten
    zetten.push_back(std::make_pair(currentRow - 2, currentCol - 1));
    zetten.push_back(std::make_pair(currentRow - 2, currentCol + 1));
    zetten.push_back(std::make_pair(currentRow - 1, currentCol - 2));
    zetten.push_back(std::make_pair(currentRow - 1, currentCol + 2));
    zetten.push_back(std::make_pair(currentRow + 1, currentCol - 2));
    zetten.push_back(std::make_pair(currentRow + 1, currentCol + 2));
    zetten.push_back(std::make_pair(currentRow + 2, currentCol - 1));
    zetten.push_back(std::make_pair(currentRow + 2, currentCol + 1));

    return zetten;
}

Positions Loper::alle_mogelijke_zetten(const Game& game) const {
    Positions zetten;

    int currentRow = this->getPositie().first;
    int currentCol = this->getPositie().second;

    // alle mogelijke zetten naar links boven
    for (int i = 1; i < ROW_SIZE; i++) {
        if (game.outOfBounds(currentRow - i, currentCol - i)) break;
        if (game.getPiece(currentRow - i, currentCol - i) == nullptr) {
            zetten.push_back(std::make_pair(currentRow - i, currentCol - i));
        } else if (game.getPiece(currentRow - i, currentCol - i)->getKleur() !=
                   getKleur()) {
            zetten.push_back(std::make_pair(currentRow - i, currentCol - i));
            break;
        } else {
            break;
        }
    }
    // alle mogelijke zetten naar rechts boven
    for (int i = 1; i < ROW_SIZE; i++) {
        if (game.outOfBounds(currentRow - i, currentCol + i)) break;
        if (game.getPiece(currentRow - i, currentCol + i) == nullptr) {
            zetten.push_back(std::make_pair(currentRow - i, currentCol + i));
        } else if (game.getPiece(currentRow - i, currentCol + i)->getKleur() !=
                   getKleur()) {
            zetten.push_back(std::make_pair(currentRow - i, currentCol + i));
            break;
        } else {
            break;
        }
    }
    // alle mogelijke zetten naar links beneden
    for (int i = 1; i < ROW_SIZE; i++) {
        if (game.outOfBounds(currentRow + i, currentCol - i)) break;
        if (game.getPiece(currentRow + i, currentCol - i) == nullptr) {
            zetten.push_back(std::make_pair(currentRow + i, currentCol - i));
        } else if (game.getPiece(currentRow + i, currentCol - i)->getKleur() !=
                   getKleur()) {
            zetten.push_back(std::make_pair(currentRow + i, currentCol - i));
            break;
        } else {
            break;
        }
    }
    // alle mogelijke zetten naar rechts beneden
    for (int i = 1; i < ROW_SIZE; i++) {
        if (game.outOfBounds(currentRow + i, currentCol + i)) break;
        if (game.getPiece(currentRow + i, currentCol + i) == nullptr) {
            zetten.push_back(std::make_pair(currentRow + i, currentCol + i));
        } else if (game.getPiece(currentRow + i, currentCol + i)->getKleur() !=
                   getKleur()) {
            zetten.push_back(std::make_pair(currentRow + i, currentCol + i));
            break;
        } else {
            break;
        }
    }

    return zetten;
}

Positions Koning::alle_mogelijke_zetten(const Game& game) const {
    Positions zetten;

    int currentRow = this->getPositie().first;
    int currentCol = this->getPositie().second;

    // alle mogelijke zetten
    zetten.push_back(std::make_pair(currentRow - 1, currentCol - 1));
    zetten.push_back(std::make_pair(currentRow - 1, currentCol));
    zetten.push_back(std::make_pair(currentRow - 1, currentCol + 1));
    zetten.push_back(std::make_pair(currentRow, currentCol - 1));
    zetten.push_back(std::make_pair(currentRow, currentCol + 1));
    zetten.push_back(std::make_pair(currentRow + 1, currentCol - 1));
    zetten.push_back(std::make_pair(currentRow + 1, currentCol));
    zetten.push_back(std::make_pair(currentRow + 1, currentCol + 1));

    return zetten;
}

Positions Koningin::alle_mogelijke_zetten(const Game& game) const {
    Positions zetten;

    int currentRow = this->getPositie().first;
    int currentCol = this->getPositie().second;

    // alle mogelijke zetten naar boven
    for (int i = currentRow - 1; i < ROW_SIZE; i--) {
        if (game.outOfBounds(i, currentCol)) break;
        if (game.getPiece(i, currentCol) == nullptr) {
            zetten.push_back(std::make_pair(i, currentCol));
        } else if (game.getPiece(i, currentCol)->getKleur() != getKleur()) {
            zetten.push_back(std::make_pair(i, currentCol));
            break;
        } else {
            break;
        }
    }
    // alle mogelijke zetten naar beneden
    for (int i = currentRow + 1; i < ROW_SIZE; i++) {
        if (game.outOfBounds(i, currentCol)) break;
        if (game.getPiece(i, currentCol) == nullptr) {
            zetten.push_back(std::make_pair(i, currentCol));
        } else if (game.getPiece(i, currentCol)->getKleur() != getKleur()) {
            zetten.push_back(std::make_pair(i, currentCol));
            break;
        } else {
            break;
        }
    }
    // alle mogelijke zetten naar links
    for (int i = currentCol - 1; i < COL_SIZE; i--) {
        if (game.outOfBounds(currentRow, i)) break;
        if (game.getPiece(currentRow, i) == nullptr) {
            zetten.push_back(std::make_pair(currentRow, i));
        } else if (game.getPiece(currentRow, i)->getKleur() != getKleur()) {
            zetten.push_back(std::make_pair(currentRow, i));
            break;
        } else {
            break;
        }
    }
    // alle mogelijke zetten naar rechts
    for (int i = currentCol + 1; i < COL_SIZE; i++) {
        if (game.outOfBounds(currentRow, i)) break;
        if (game.getPiece(currentRow, i) == nullptr) {
            zetten.push_back(std::make_pair(currentRow, i));
        } else if (game.getPiece(currentRow, i)->getKleur() != getKleur()) {
            zetten.push_back(std::make_pair(currentRow, i));
            break;
        } else {
            break;
        }
    }
    // alle mogelijke zetten naar links boven
    for (int i = 1; i < ROW_SIZE; i++) {
        if (game.outOfBounds(currentRow - i, currentCol - i)) break;
        if (game.getPiece(currentRow - i, currentCol - i) == nullptr) {
            zetten.push_back(std::make_pair(currentRow - i, currentCol - i));
        } else if (game.getPiece(currentRow - i, currentCol - i)->getKleur() !=
                   getKleur()) {
            zetten.push_back(std::make_pair(currentRow - i, currentCol - i));
            break;
        } else {
            break;
        }
    }
    // alle mogelijke zetten naar rechts boven
    for (int i = 1; i < ROW_SIZE; i++) {
        if (game.outOfBounds(currentRow - i, currentCol + i)) break;
        if (game.getPiece(currentRow - i, currentCol + i) == nullptr) {
            zetten.push_back(std::make_pair(currentRow - i, currentCol + i));
        } else if (game.getPiece(currentRow - i, currentCol + i)->getKleur() !=
                   getKleur()) {
            zetten.push_back(std::make_pair(currentRow - i, currentCol + i));
            break;
        } else {
            break;
        }
    }
    // alle mogelijke zetten naar links beneden
    for (int i = 1; i < ROW_SIZE; i++) {
        if (game.outOfBounds(currentRow + i, currentCol - i)) break;
        if (game.getPiece(currentRow + i, currentCol - i) == nullptr) {
            zetten.push_back(std::make_pair(currentRow + i, currentCol - i));
        } else if (game.getPiece(currentRow + i, currentCol - i)->getKleur() !=
                   getKleur()) {
            zetten.push_back(std::make_pair(currentRow + i, currentCol - i));
            break;
        } else {
            break;
        }
    }
    // alle mogelijke zetten naar rechts beneden
    for (int i = 1; i < ROW_SIZE; i++) {
        if (game.outOfBounds(currentRow + i, currentCol + i)) break;
        if (game.getPiece(currentRow + i, currentCol + i) == nullptr) {
            zetten.push_back(std::make_pair(currentRow + i, currentCol + i));
        } else if (game.getPiece(currentRow + i, currentCol + i)->getKleur() !=
                   getKleur()) {
            zetten.push_back(std::make_pair(currentRow + i, currentCol + i));
            break;
        } else {
            break;
        }
    }

    return zetten;
}

Positions SchaakStuk::geldige_zetten(const Game& game) {
    // filteration; remove all invalid positions; out of bounds
    Positions validZetten;
    for (const auto& pos : alle_mogelijke_zetten(game)) {
        if (game.outOfBounds(pos.first, pos.second)) continue;
        if (game.causesSchaak(this, pos.first, pos.second)) continue;
        SchaakStuk* stuk = game.getPiece(pos.first, pos.second);
        if (stuk == nullptr || (stuk != nullptr && stuk->getKleur() != getKleur())) {
            validZetten.push_back(pos);
        }
    }

    return validZetten;
}
