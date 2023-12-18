//  Student:
//  Rolnummer:
//  Opmerkingen: (bvb aanpassingen van de opgave)
//

#include "SchaakStuk.h"

#include "game.h"

ArrayList<MatrixPair> Pion::geldige_zetten(const Game& game) const {
    ArrayList<MatrixPair> zetten = {};

    int currentRow = this->getPositie().getRow();
    int currentCol = this->getPositie().getColumn();

    if (getKleur() == zw::wit) {
        if (currentRow == 6) {
            if (game.getPiece(currentRow - 2, currentCol) == nullptr) {
                zetten.add(MatrixPair(currentRow - 2, currentCol));
            }
        }
        if (game.getPiece(currentRow - 1, currentCol) == nullptr) {
            zetten.add(MatrixPair(currentRow + 1, currentCol));
        }
        if (game.getPiece(currentRow - 1, currentCol - 1) != nullptr &&
            game.getPiece(currentRow - 1, currentCol - 1)->getKleur() ==
                zw::zwart) {
            zetten.add(MatrixPair(currentRow - 1, currentCol - 1));
        }
        if (game.getPiece(currentRow - 1, currentCol + 1) != nullptr &&
            game.getPiece(currentRow - 1, currentCol + 1)->getKleur() ==
                zw::zwart) {
            zetten.add(MatrixPair(currentRow - 1, currentCol + 1));
        }
    } else {
        if (currentRow == 1) {
            if (game.getPiece(currentRow + 2, currentCol) == nullptr) {
                zetten.add(MatrixPair(currentRow + 2, currentCol));
            }
        }
        if (game.getPiece(currentRow + 1, currentCol) == nullptr) {
            zetten.add(MatrixPair(currentRow + 1, currentCol));
        }
        if (game.getPiece(currentRow + 1, currentCol - 1) != nullptr &&
            game.getPiece(currentRow + 1, currentCol - 1)->getKleur() ==
                zw::zwart) {
            zetten.add(MatrixPair(currentRow + 1, currentCol - 1));
        }
        if (game.getPiece(currentRow + 1, currentCol + 1) != nullptr &&
            game.getPiece(currentRow + 1, currentCol + 1)->getKleur() ==
                zw::zwart) {
            zetten.add(MatrixPair(currentRow + 1, currentCol + 1));
        }
    }

    // filteration; remove all invalid positions; out of bounds
    ArrayList<MatrixPair> validZetten;
    for (int i = 0; i < zetten.getSize(); i++) {
        MatrixPair pos = zetten.getItem(i);
        if (!game.outOfBounds(pos.getRow(), pos.getColumn())) {
            validZetten.add(pos);
        }
    }
    zetten = validZetten;

    return zetten;
}

ArrayList<MatrixPair> Toren::geldige_zetten(const Game& game) const {
    ArrayList<MatrixPair> zetten = {};

    int currentRow = this->getPositie().getRow();
    int currentCol = this->getPositie().getColumn();

    // alle mogelijke verticale zetten
    for (int i = 0; i < ROW_SIZE; i++) {
        if (game.getPiece(i, currentCol) == nullptr) {
            zetten.add(MatrixPair(i, currentCol));
        } else if (game.getPiece(i, currentCol)->getKleur() != getKleur()) {
            zetten.add(MatrixPair(i, currentCol));
            break;
        } else {
            break;
        }
    }
    // alle mogelijke horizontale zetten
    for (int i = 0; i < COL_SIZE; i++) {
        if (game.getPiece(currentRow, i) == nullptr) {
            zetten.add(MatrixPair(currentRow, i));
        } else if (game.getPiece(currentRow, i)->getKleur() != getKleur()) {
            zetten.add(MatrixPair(currentRow, i));
            break;
        } else {
            break;
        }
    }

    return zetten;
}

ArrayList<MatrixPair> Paard::geldige_zetten(const Game& game) const {
    ArrayList<MatrixPair> zetten = {};

    int currentRow = this->getPositie().getRow();
    int currentCol = this->getPositie().getColumn();

    // alle mogelijke zetten
    zetten.add(MatrixPair(currentRow - 2, currentCol - 1));
    zetten.add(MatrixPair(currentRow - 2, currentCol + 1));
    zetten.add(MatrixPair(currentRow - 1, currentCol - 2));
    zetten.add(MatrixPair(currentRow - 1, currentCol + 2));
    zetten.add(MatrixPair(currentRow + 1, currentCol - 2));
    zetten.add(MatrixPair(currentRow + 1, currentCol + 2));
    zetten.add(MatrixPair(currentRow + 2, currentCol - 1));
    zetten.add(MatrixPair(currentRow + 2, currentCol + 1));

    // filteration; remove all invalid positions; out of bounds
    ArrayList<MatrixPair> validZetten;
    for (int i = 0; i < zetten.getSize(); i++) {
        MatrixPair pos = zetten.getItem(i);
        if (!game.outOfBounds(pos.getRow(), pos.getColumn())) {
            validZetten.add(pos);
        }
    }
    zetten = validZetten;

    return zetten;
}

ArrayList<MatrixPair> Loper::geldige_zetten(const Game& game) const {
    ArrayList<MatrixPair> zetten = {};

    int currentRow = this->getPositie().getRow();
    int currentCol = this->getPositie().getColumn();

    // alle mogelijke zetten naar links boven
    for (int i = 1; i < ROW_SIZE; i++) {
        if (game.getPiece(currentRow - i, currentCol - i) == nullptr) {
            zetten.add(MatrixPair(currentRow - i, currentCol - i));
        } else if (game.getPiece(currentRow - i, currentCol - i)->getKleur() !=
                   getKleur()) {
            zetten.add(MatrixPair(currentRow - i, currentCol - i));
            break;
        } else {
            break;
        }
    }
    // alle mogelijke zetten naar rechts boven
    for (int i = 1; i < ROW_SIZE; i++) {
        if (game.getPiece(currentRow - i, currentCol + i) == nullptr) {
            zetten.add(MatrixPair(currentRow - i, currentCol + i));
        } else if (game.getPiece(currentRow - i, currentCol + i)->getKleur() !=
                   getKleur()) {
            zetten.add(MatrixPair(currentRow - i, currentCol + i));
            break;
        } else {
            break;
        }
    }
    // alle mogelijke zetten naar links beneden
    for (int i = 1; i < ROW_SIZE; i++) {
        if (game.getPiece(currentRow + i, currentCol - i) == nullptr) {
            zetten.add(MatrixPair(currentRow + i, currentCol - i));
        } else if (game.getPiece(currentRow + i, currentCol - i)->getKleur() !=
                   getKleur()) {
            zetten.add(MatrixPair(currentRow + i, currentCol - i));
            break;
        } else {
            break;
        }
    }
    // alle mogelijke zetten naar rechts beneden
    for (int i = 1; i < ROW_SIZE; i++) {
        if (game.getPiece(currentRow + i, currentCol + i) == nullptr) {
            zetten.add(MatrixPair(currentRow + i, currentCol + i));
        } else if (game.getPiece(currentRow + i, currentCol + i)->getKleur() !=
                   getKleur()) {
            zetten.add(MatrixPair(currentRow + i, currentCol + i));
            break;
        } else {
            break;
        }
    }

    // filteration; remove all invalid positions; out of bounds
    ArrayList<MatrixPair> validZetten;
    for (int i = 0; i < zetten.getSize(); i++) {
        MatrixPair pos = zetten.getItem(i);
        if (!game.outOfBounds(pos.getRow(), pos.getColumn())) {
            validZetten.add(pos);
        }
    }
    zetten = validZetten;

    return zetten;
}

ArrayList<MatrixPair> Koning::geldige_zetten(const Game& game) const {
    ArrayList<MatrixPair> zetten = {};

    int currentRow = this->getPositie().getRow();
    int currentCol = this->getPositie().getColumn();

    // alle mogelijke zetten
    zetten.add(MatrixPair(currentRow - 1, currentCol - 1));
    zetten.add(MatrixPair(currentRow - 1, currentCol));
    zetten.add(MatrixPair(currentRow - 1, currentCol + 1));
    zetten.add(MatrixPair(currentRow, currentCol - 1));
    zetten.add(MatrixPair(currentRow, currentCol + 1));
    zetten.add(MatrixPair(currentRow + 1, currentCol - 1));
    zetten.add(MatrixPair(currentRow + 1, currentCol));
    zetten.add(MatrixPair(currentRow + 1, currentCol + 1));

    // filteration; remove all invalid positions; out of bounds
    ArrayList<MatrixPair> validZetten;
    for (int i = 0; i < zetten.getSize(); i++) {
        MatrixPair pos = zetten.getItem(i);
        if (!game.outOfBounds(pos.getRow(), pos.getColumn())) {
            validZetten.add(pos);
        }
    }
    zetten = validZetten;


    return zetten;
}

ArrayList<MatrixPair> Koningin::geldige_zetten(const Game& game) const {
    ArrayList<MatrixPair> zetten = {};

    int currentRow = this->getPositie().getRow();
    int currentCol = this->getPositie().getColumn();

    // alle mogelijke verticale zetten
    for (int i = 0; i < ROW_SIZE; i++) {
        if (game.getPiece(i, currentCol) == nullptr) {
            zetten.add(MatrixPair(i, currentCol));
        } else if (game.getPiece(i, currentCol)->getKleur() != getKleur()) {
            zetten.add(MatrixPair(i, currentCol));
            break;
        } else {
            break;
        }
    }
    // alle mogelijke horizontale zetten
    for (int i = 0; i < COL_SIZE; i++) {
        if (game.getPiece(currentRow, i) == nullptr) {
            zetten.add(MatrixPair(currentRow, i));
        } else if (game.getPiece(currentRow, i)->getKleur() != getKleur()) {
            zetten.add(MatrixPair(currentRow, i));
            break;
        } else {
            break;
        }
    }
    // alle mogelijke zetten naar links boven
    for (int i = 1; i < ROW_SIZE; i++) {
        if (game.getPiece(currentRow - i, currentCol - i) == nullptr) {
            zetten.add(MatrixPair(currentRow - i, currentCol - i));
        } else if (game.getPiece(currentRow - i, currentCol - i)->getKleur() !=
                   getKleur()) {
            zetten.add(MatrixPair(currentRow - i, currentCol - i));
            break;
        } else {
            break;
        }
    }
    // alle mogelijke zetten naar rechts boven
    for (int i = 1; i < ROW_SIZE; i++) {
        if (game.getPiece(currentRow - i, currentCol + i) == nullptr) {
            zetten.add(MatrixPair(currentRow - i, currentCol + i));
        } else if (game.getPiece(currentRow - i, currentCol + i)->getKleur() !=
                   getKleur()) {
            zetten.add(MatrixPair(currentRow - i, currentCol + i));
            break;
        } else {
            break;
        }
    }
    // alle mogelijke zetten naar links beneden
    for (int i = 1; i < ROW_SIZE; i++) {
        if (game.getPiece(currentRow + i, currentCol - i) == nullptr) {
            zetten.add(MatrixPair(currentRow + i, currentCol - i));
        } else if (game.getPiece(currentRow + i, currentCol - i)->getKleur() !=
                   getKleur()) {
            zetten.add(MatrixPair(currentRow + i, currentCol - i));
            break;
        } else {
            break;
        }
    }
    // alle mogelijke zetten naar rechts beneden
    for (int i = 1; i < ROW_SIZE; i++) {
        if (game.getPiece(currentRow + i, currentCol + i) == nullptr) {
            zetten.add(MatrixPair(currentRow + i, currentCol + i));
        } else if (game.getPiece(currentRow + i, currentCol + i)->getKleur() !=
                   getKleur()) {
            zetten.add(MatrixPair(currentRow + i, currentCol + i));
            break;
        } else {
            break;
        }
    }

    // filteration; remove all invalid positions; out of bounds
    ArrayList<MatrixPair> validZetten;
    for (int i = 0; i < zetten.getSize(); i++) {
        MatrixPair pos = zetten.getItem(i);
        if (!game.outOfBounds(pos.getRow(), pos.getColumn())) {
            validZetten.add(pos);
        }
    }
    zetten = validZetten;

    return zetten;
}
