//
// Created by nilerrors on 1/10/24.
//

#include <iostream>
#include "Logging.h"

std::string pieceToString(const Piece &piece) {
    std::string text = piece.color() == Piece::Color::White ? "wit " : "zwart ";
    switch (piece.type()) {
        case Piece::Pawn:
            text += "Pion";
            break;
        case Piece::King:
            text += "Koning";
            break;
        case Piece::Bishop:
            text += "Loper";
            break;
        case Piece::Knight:
            text += "Paard";
            break;
        case Piece::Queen:
            text += "Koningin";
            break;
        case Piece::Rook:
            text += "Toren";
            break;
        case Piece::None:
            return "Niets";
    }
    return text;
}

void logTotalKills(const Piece &piece, size_t allKillsSize) {
    std::cout << "Totaal aantal kills van "
              << pieceToString(piece) << " : "
              << allKillsSize
              << std::endl;
}

void logSchaakPosities(const Piece &piece, Position piecePosition, Position kingPosition) {
    std::cout << pieceToString(piece)
              << " (" << piecePosition.first << ", " << piecePosition.second << ")"
              << " staat in schaak positie tegenover de "
              << (piece.color() == Piece::Color::Black ? "witte " : "zwarte ") << "Koning"
              << " (" << kingPosition.first << ", " << kingPosition.second << ") "
              << std::endl;
}

void logSchaakmatAls(Piece piece, Position piecePositie, Position move) {
    std::cout << "als "
              << pieceToString(piece)
              << " (" << piecePositie.first << ", " << piecePositie.second << ") "
              << "bewogen wordt naar (" << move.first << ", " << move.second << ")"
              << std::endl;
}

void logSchaakAls(Piece piece, Position piecePositie, Position move) {
    std::cout << "\tals "
              << pieceToString(piece)
              << " (" << piecePositie.first << ", " << piecePositie.second << ") "
              << "bewogen wordt naar (" << move.first << ", " << move.second << ")"
              << std::endl;
}

void logClickedPosition(int r, int k, Piece piece) {
    std::cout << "Geklikte positie: (" << r << ", " << k << ")" << std::endl
              << "\tEr staat: " << (piece.type() == Piece::None ? "Niets" : pieceToString(piece))
              << std::endl;
}


void logBeweegStuk(int r, int k, Piece piece) {
    std::cout << "Beweeg stuk: "
              << pieceToString(piece)
              << " naar (" << r << ", " << k << ")"
              << std::endl;
}