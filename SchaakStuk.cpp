//  Student:
//  Rolnummer:
//  Opmerkingen: (bvb aanpassingen van de opgave)
//

#include "SchaakStuk.h"

#include "game.h"

std::vector<std::pair<int, int>> Pion::geldige_zetten(const Game& game) const {
    std::vector<std::pair<int, int>> zetten;

    int currentRow = this->getPositie().first;
    int currentCol = this->getPositie().second;

    if (getKleur() == zw::wit) {
        if (currentRow == 6) {
            if (game.getPiece(currentRow - 2, currentCol) == nullptr) {
                zetten.push_back(std::make_pair(currentRow - 2, currentCol));
            }
        }
        if (game.getPiece(currentRow - 1, currentCol) == nullptr) {
            zetten.push_back(std::make_pair(currentRow - 1, currentCol));
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
        if (currentRow == 1) {
            if (game.getPiece(currentRow + 2, currentCol) == nullptr) {
                zetten.push_back(std::make_pair(currentRow + 2, currentCol));
            }
        }
        if (game.getPiece(currentRow + 1, currentCol) == nullptr) {
            zetten.push_back(std::make_pair(currentRow + 1, currentCol));
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

    // filteration; remove all invalid positions; out of bounds
    std::vector<std::pair<int, int>> validZetten;
    for (const auto& pos : zetten) {
        SchaakStuk* stuk = game.getPiece(pos.first, pos.second);
        if (!game.outOfBounds(pos.first, pos.second) || (stuk != nullptr && stuk->getKleur() != getKleur())) {
            validZetten.push_back(pos);
        }
    }
    zetten = validZetten;

    return zetten;
}

std::vector<std::pair<int, int>> Toren::geldige_zetten(const Game& game) const {
    std::vector<std::pair<int, int>> zetten;

    int currentRow = this->getPositie().first;
    int currentCol = this->getPositie().second;

    // alle mogelijke verticale zetten
    for (int i = 0; i < ROW_SIZE; i++) {
        if (i == currentCol) continue;
        if (game.getPiece(i, currentCol) == nullptr) {
            zetten.push_back(std::make_pair(i, currentCol));
        } else if (game.getPiece(i, currentCol)->getKleur() != getKleur()) {
            zetten.push_back(std::make_pair(i, currentCol));
            break;
        } else {
            break;
        }
    }
    // alle mogelijke horizontale zetten
    for (int i = 0; i < COL_SIZE; i++) {
        if (i == currentCol) continue;
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

std::vector<std::pair<int, int>> Paard::geldige_zetten(const Game& game) const {
    std::vector<std::pair<int, int>> zetten;

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

    // filteration; remove all invalid positions; out of bounds
    std::vector<std::pair<int, int>> validZetten;
    for (const auto& pos : zetten) {
        SchaakStuk* stuk = game.getPiece(pos.first, pos.second);
        if (!game.outOfBounds(pos.first, pos.second) || (stuk != nullptr && stuk->getKleur() != getKleur())) {
            validZetten.push_back(pos);
        }
    }
    zetten = validZetten;

    return zetten;
}

std::vector<std::pair<int, int>> Loper::geldige_zetten(const Game& game) const {
    std::vector<std::pair<int, int>> zetten;

    int currentRow = this->getPositie().first;
    int currentCol = this->getPositie().second;

    // alle mogelijke zetten naar links boven
    for (int i = 1; i < ROW_SIZE; i++) {
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

    // filteration; remove all invalid positions; out of bounds
    std::vector<std::pair<int, int>> validZetten;
    for (const auto& pos : zetten) {
        SchaakStuk* stuk = game.getPiece(pos.first, pos.second);
        if (!game.outOfBounds(pos.first, pos.second) || (stuk != nullptr && stuk->getKleur() != getKleur())) {
            validZetten.push_back(pos);
        }
    }
    zetten = validZetten;

    return zetten;
}

std::vector<std::pair<int, int>> Koning::geldige_zetten(
    const Game& game) const {
    std::vector<std::pair<int, int>> zetten;

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

    // filteration; remove all invalid positions; out of bounds
    std::vector<std::pair<int, int>> validZetten;
    for (const auto& pos : zetten) {
        SchaakStuk* stuk = game.getPiece(pos.first, pos.second);
        if (!game.outOfBounds(pos.first, pos.second) || (stuk != nullptr && stuk->getKleur() != getKleur())) {
            validZetten.push_back(pos);
        }
    }
    zetten = validZetten;

    return zetten;
}

std::vector<std::pair<int, int>> Koningin::geldige_zetten(
    const Game& game) const {
    std::vector<std::pair<int, int>> zetten;

    int currentRow = this->getPositie().first;
    int currentCol = this->getPositie().second;

    // alle mogelijke verticale zetten
    for (int i = 0; i < ROW_SIZE; i++) {
        if (i == currentRow) continue;
        if (game.getPiece(i, currentCol) == nullptr) {
            zetten.push_back(std::make_pair(i, currentCol));
        } else if (game.getPiece(i, currentCol)->getKleur() != getKleur()) {
            zetten.push_back(std::make_pair(i, currentCol));
            break;
        } else {
            break;
        }
    }
    // alle mogelijke horizontale zetten
    for (int i = 0; i < COL_SIZE; i++) {
        if (i == currentCol) continue;
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

    // filteration; remove all invalid positions; out of bounds
    std::vector<std::pair<int, int>> validZetten;
    for (const auto& pos : zetten) {
        SchaakStuk* stuk = game.getPiece(pos.first, pos.second);
        if (!game.outOfBounds(pos.first, pos.second) || (stuk != nullptr && stuk->getKleur() != getKleur())) {
            validZetten.push_back(pos);
        }
    }
    zetten = validZetten;

    return zetten;
}
