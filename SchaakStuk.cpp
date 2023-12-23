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
            zetten.push_back(Position(currentRow - 1, currentCol));
            if (currentRow == 6) {
                if (game.getPiece(currentRow - 2, currentCol) == nullptr) {
                    zetten.push_back(Position(currentRow - 2, currentCol));
                }
            }
        }
        if (game.getPiece(currentRow - 1, currentCol - 1) != nullptr &&
            game.getPiece(currentRow - 1, currentCol - 1)->getKleur() ==
                zw::zwart) {
            zetten.push_back(Position(currentRow - 1, currentCol - 1));
        }
        if (game.getPiece(currentRow - 1, currentCol + 1) != nullptr &&
            game.getPiece(currentRow - 1, currentCol + 1)->getKleur() ==
                zw::zwart) {
            zetten.push_back(Position(currentRow - 1, currentCol + 1));
        }
    } else {
        if (game.getPiece(currentRow + 1, currentCol) == nullptr) {
            zetten.push_back(Position(currentRow + 1, currentCol));
            if (currentRow == 1) {
                if (game.getPiece(currentRow + 2, currentCol) == nullptr) {
                    zetten.push_back(Position(currentRow + 2, currentCol));
                }
            }
        }
        if (game.getPiece(currentRow + 1, currentCol - 1) != nullptr &&
            game.getPiece(currentRow + 1, currentCol - 1)->getKleur() ==
                zw::wit) {
            zetten.push_back(Position(currentRow + 1, currentCol - 1));
        }
        if (game.getPiece(currentRow + 1, currentCol + 1) != nullptr &&
            game.getPiece(currentRow + 1, currentCol + 1)->getKleur() ==
                zw::wit) {
            zetten.push_back(Position(currentRow + 1, currentCol + 1));
        }
    }

    // en passant
    const FromTo* lastMove = game.lastMove();
    if (lastMove != nullptr && lastMove->val->piece().type() == Piece::Pawn &&
        getKleur() != lastMove->val->getKleur()) {
        if (getKleur() == zw::wit) {
            if (lastMove->from.first == 1 && lastMove->to.first == 3 && currentRow == 3) {
                if (lastMove->to.second - 1 == currentCol || lastMove->to.second + 1 == currentCol) {
                    zetten.push_back(Position(lastMove->to.first - 1, lastMove->to.second, MoveType::en_passant));
                }
            }
        } else {
            if (lastMove->from.first == 6 && lastMove->to.first == 4 && currentRow == 4) {
                if (lastMove->to.second - 1 == currentCol || lastMove->to.second + 1 == currentCol) {
                    zetten.push_back(Position(lastMove->to.first + 1, lastMove->to.second, MoveType::en_passant));
                }
            }
        }
    }

    // promotie:
    //          gaat de pion direct naar een koningin veranderen,
    //          dus er kan niet gekozen worden
    // zoek naar alle promoties in de zetten en veranderen ze naar promoties
    for (auto &zet : zetten) {
        if (getKleur() == zw::wit && zet.first == 0) {
            zet.type = MoveType::pawn_promotion;
        } else if (getKleur() == zw::zwart && zet.first == 7) {
            zet.type = MoveType::pawn_promotion;
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
            zetten.push_back(Position(i, currentCol));
        } else if (game.getPiece(i, currentCol)->getKleur() != getKleur()) {
            zetten.push_back(Position(i, currentCol));
            break;
        } else {
            break;
        }
    }
    // alle mogelijke zetten naar beneden
    for (int i = currentRow + 1; i < ROW_SIZE; i++) {
        if (game.outOfBounds(i, currentCol)) break;
        if (game.getPiece(i, currentCol) == nullptr) {
            zetten.push_back(Position(i, currentCol));
        } else if (game.getPiece(i, currentCol)->getKleur() != getKleur()) {
            zetten.push_back(Position(i, currentCol));
            break;
        } else {
            break;
        }
    }
    // alle mogelijke zetten naar links
    for (int i = currentCol - 1; i < COL_SIZE; i--) {
        if (game.outOfBounds(currentRow, i)) break;
        if (game.getPiece(currentRow, i) == nullptr) {
            zetten.push_back(Position(currentRow, i));
        } else if (game.getPiece(currentRow, i)->getKleur() != getKleur()) {
            zetten.push_back(Position(currentRow, i));
            break;
        } else {
            break;
        }
    }
    // alle mogelijke zetten naar rechts
    for (int i = currentCol + 1; i < COL_SIZE; i++) {
        if (game.outOfBounds(currentRow, i)) break;
        if (game.getPiece(currentRow, i) == nullptr) {
            zetten.push_back(Position(currentRow, i));
        } else if (game.getPiece(currentRow, i)->getKleur() != getKleur()) {
            zetten.push_back(Position(currentRow, i));
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
    zetten.push_back(Position(currentRow - 2, currentCol - 1));
    zetten.push_back(Position(currentRow - 2, currentCol + 1));
    zetten.push_back(Position(currentRow - 1, currentCol - 2));
    zetten.push_back(Position(currentRow - 1, currentCol + 2));
    zetten.push_back(Position(currentRow + 1, currentCol - 2));
    zetten.push_back(Position(currentRow + 1, currentCol + 2));
    zetten.push_back(Position(currentRow + 2, currentCol - 1));
    zetten.push_back(Position(currentRow + 2, currentCol + 1));

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
            zetten.push_back(Position(currentRow - i, currentCol - i));
        } else if (game.getPiece(currentRow - i, currentCol - i)->getKleur() !=
                   getKleur()) {
            zetten.push_back(Position(currentRow - i, currentCol - i));
            break;
        } else {
            break;
        }
    }
    // alle mogelijke zetten naar rechts boven
    for (int i = 1; i < ROW_SIZE; i++) {
        if (game.outOfBounds(currentRow - i, currentCol + i)) break;
        if (game.getPiece(currentRow - i, currentCol + i) == nullptr) {
            zetten.push_back(Position(currentRow - i, currentCol + i));
        } else if (game.getPiece(currentRow - i, currentCol + i)->getKleur() !=
                   getKleur()) {
            zetten.push_back(Position(currentRow - i, currentCol + i));
            break;
        } else {
            break;
        }
    }
    // alle mogelijke zetten naar links beneden
    for (int i = 1; i < ROW_SIZE; i++) {
        if (game.outOfBounds(currentRow + i, currentCol - i)) break;
        if (game.getPiece(currentRow + i, currentCol - i) == nullptr) {
            zetten.push_back(Position(currentRow + i, currentCol - i));
        } else if (game.getPiece(currentRow + i, currentCol - i)->getKleur() !=
                   getKleur()) {
            zetten.push_back(Position(currentRow + i, currentCol - i));
            break;
        } else {
            break;
        }
    }
    // alle mogelijke zetten naar rechts beneden
    for (int i = 1; i < ROW_SIZE; i++) {
        if (game.outOfBounds(currentRow + i, currentCol + i)) break;
        if (game.getPiece(currentRow + i, currentCol + i) == nullptr) {
            zetten.push_back(Position(currentRow + i, currentCol + i));
        } else if (game.getPiece(currentRow + i, currentCol + i)->getKleur() !=
                   getKleur()) {
            zetten.push_back(Position(currentRow + i, currentCol + i));
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
    zetten.push_back(Position(currentRow - 1, currentCol - 1));
    zetten.push_back(Position(currentRow - 1, currentCol));
    zetten.push_back(Position(currentRow - 1, currentCol + 1));
    zetten.push_back(Position(currentRow, currentCol - 1));
    zetten.push_back(Position(currentRow, currentCol + 1));
    zetten.push_back(Position(currentRow + 1, currentCol - 1));
    zetten.push_back(Position(currentRow + 1, currentCol));
    zetten.push_back(Position(currentRow + 1, currentCol + 1));

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
            zetten.push_back(Position(i, currentCol));
        } else if (game.getPiece(i, currentCol)->getKleur() != getKleur()) {
            zetten.push_back(Position(i, currentCol));
            break;
        } else {
            break;
        }
    }
    // alle mogelijke zetten naar beneden
    for (int i = currentRow + 1; i < ROW_SIZE; i++) {
        if (game.outOfBounds(i, currentCol)) break;
        if (game.getPiece(i, currentCol) == nullptr) {
            zetten.push_back(Position(i, currentCol));
        } else if (game.getPiece(i, currentCol)->getKleur() != getKleur()) {
            zetten.push_back(Position(i, currentCol));
            break;
        } else {
            break;
        }
    }
    // alle mogelijke zetten naar links
    for (int i = currentCol - 1; i < COL_SIZE; i--) {
        if (game.outOfBounds(currentRow, i)) break;
        if (game.getPiece(currentRow, i) == nullptr) {
            zetten.push_back(Position(currentRow, i));
        } else if (game.getPiece(currentRow, i)->getKleur() != getKleur()) {
            zetten.push_back(Position(currentRow, i));
            break;
        } else {
            break;
        }
    }
    // alle mogelijke zetten naar rechts
    for (int i = currentCol + 1; i < COL_SIZE; i++) {
        if (game.outOfBounds(currentRow, i)) break;
        if (game.getPiece(currentRow, i) == nullptr) {
            zetten.push_back(Position(currentRow, i));
        } else if (game.getPiece(currentRow, i)->getKleur() != getKleur()) {
            zetten.push_back(Position(currentRow, i));
            break;
        } else {
            break;
        }
    }
    // alle mogelijke zetten naar links boven
    for (int i = 1; i < ROW_SIZE; i++) {
        if (game.outOfBounds(currentRow - i, currentCol - i)) break;
        if (game.getPiece(currentRow - i, currentCol - i) == nullptr) {
            zetten.push_back(Position(currentRow - i, currentCol - i));
        } else if (game.getPiece(currentRow - i, currentCol - i)->getKleur() !=
                   getKleur()) {
            zetten.push_back(Position(currentRow - i, currentCol - i));
            break;
        } else {
            break;
        }
    }
    // alle mogelijke zetten naar rechts boven
    for (int i = 1; i < ROW_SIZE; i++) {
        if (game.outOfBounds(currentRow - i, currentCol + i)) break;
        if (game.getPiece(currentRow - i, currentCol + i) == nullptr) {
            zetten.push_back(Position(currentRow - i, currentCol + i));
        } else if (game.getPiece(currentRow - i, currentCol + i)->getKleur() !=
                   getKleur()) {
            zetten.push_back(Position(currentRow - i, currentCol + i));
            break;
        } else {
            break;
        }
    }
    // alle mogelijke zetten naar links beneden
    for (int i = 1; i < ROW_SIZE; i++) {
        if (game.outOfBounds(currentRow + i, currentCol - i)) break;
        if (game.getPiece(currentRow + i, currentCol - i) == nullptr) {
            zetten.push_back(Position(currentRow + i, currentCol - i));
        } else if (game.getPiece(currentRow + i, currentCol - i)->getKleur() !=
                   getKleur()) {
            zetten.push_back(Position(currentRow + i, currentCol - i));
            break;
        } else {
            break;
        }
    }
    // alle mogelijke zetten naar rechts beneden
    for (int i = 1; i < ROW_SIZE; i++) {
        if (game.outOfBounds(currentRow + i, currentCol + i)) break;
        if (game.getPiece(currentRow + i, currentCol + i) == nullptr) {
            zetten.push_back(Position(currentRow + i, currentCol + i));
        } else if (game.getPiece(currentRow + i, currentCol + i)->getKleur() !=
                   getKleur()) {
            zetten.push_back(Position(currentRow + i, currentCol + i));
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
        if (game.causesSchaak(this, pos)) continue;
        SchaakStuk* stuk = game.getPiece(pos.first, pos.second);
        if (stuk == nullptr || (stuk != nullptr && stuk->getKleur() != getKleur())) {
            validZetten.push_back(pos);
        }
    }

    return validZetten;
}
