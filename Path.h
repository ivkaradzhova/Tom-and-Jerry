//
// Created by pon on 21.11.19.
//

#ifndef TOM_JERRY_PATH_H
#define TOM_JERRY_PATH_H
#include <iostream>
#include <string>
using namespace std;

struct Path {
    int length;
    int numPaintSpots;
    string commands;
    Path (): length (0),numPaintSpots (0), commands("") {}
    void addStep(char direction) {
        commands.push_back(direction);
        length++;
    }
};


#endif //TOM_JERRY_PATH_H
