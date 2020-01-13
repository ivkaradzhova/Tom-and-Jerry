//
// Created by pon on 16.12.19.
//

#ifndef TOM_JERRY_2_COMMANDS_H
#define TOM_JERRY_2_COMMANDS_H

#include "Tree.h"
#include <cmath>

struct Path {
    vector<Coordinates> steps;
    int length;
    int turns;
    int numPaintSpots;
    string commands;
    Path() {
        length = 0;
        turns = 0;
        numPaintSpots = 0;
    }
    void countTurns();
    void addStep(Coordinates newStep);
    void printPath();
};


class Commands {
    Room room;
    vector<Path> shortestPaths;

public:

    void getPathFromRoot(Node *current, Path &pathFromCurrent);
    void getShortestPaths(string filename);

    void printShortestPaths();
};


#endif //TOM_JERRY_2_COMMANDS_H
