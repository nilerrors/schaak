//
// Created by nilerrors on 1/10/24.
//

#ifndef SCHAKEN_LOGGING_H
#define SCHAKEN_LOGGING_H

#include <string>
#include <guicode/chessboard.h>
#include "Position.h"


std::string pieceToString(const Piece& piece);

void logTotalKills(const Piece& piece, size_t allKills);

void logSchaakPosities(const Piece& piece, Position piecePosition, Position kingPosition);

void logSchaakmatAls(Piece piece, Position piecePositie, Position move);

void logSchaakAls(Piece piece, Position piecePositie, Position move);

void logClickedPosition(int r, int k, Piece piece);

void logBeweegStuk(int r, int k, Piece piece);


#endif //SCHAKEN_LOGGING_H
