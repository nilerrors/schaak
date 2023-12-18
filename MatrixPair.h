//
// Created by nilerrors on 18/12/2023.
//

// Opmerking: Deze klasse is gemaakt omdat er misconfiguraties
//            (exit code; 0xC0000139) ontstaan
//            bij het gebruik van de standard library.
//

#ifndef SCHAKEN_MATRIXPAIR_H
#define SCHAKEN_MATRIXPAIR_H

class MatrixPair {
    int row;
    int column;
public:
    MatrixPair() { row = -1; column = -1; }
    MatrixPair(int r, int c) { row = r; column = c; }

    int getRow() const { return row; }
    int getColumn() const { return column; }

    void setRow(int r) { row = r; }
    void setColumn(int c) { column = c; }
};

#endif //SCHAKEN_MATRIXPAIR_H
