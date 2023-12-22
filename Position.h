//
// Created by nilerrors on 21/12/2023.
//

#ifndef SCHAKEN_POSITION_H
#define SCHAKEN_POSITION_H

#include <utility>
#include <vector>

typedef std::pair<int, int> Position;

typedef std::vector<Position> Positions;


template<class T>
struct FromTo {
    T val;
    Position from;
    Position to;
};

#endif //SCHAKEN_POSITION_H
