//
// Created by pon on 21.11.19.
//

#ifndef TOM_JERRY_ROOM_H
#define TOM_JERRY_ROOM_H

#include <iostream>
#include <vector>
#include <string>
using namespace std;


struct Coordinates {
    int x; //from north to south
    int y; //from west to east
    Coordinates(int _x = 0, int _y = 0): x(_x), y(_y) {}
    bool operator != (Coordinates &other) const {
        return this->y != other.y || this->x != other.x;
    }
    bool operator == (Coordinates &other) const {
        return this->y == other.y && this->x == other.x;
    }

};

struct Furniture {
    Coordinates startPoint;
    vector<string> shape;
    Furniture& operator= (Furniture const& other) {
        this->startPoint = other.startPoint;
        this->shape = other.shape;
    }
};

class Room {
    vector<vector<char> > terrain;
    int length, width;
    int numFurniture,  numPaintSpots;
    Coordinates tom, jerry;
    vector<Furniture> furniture;
    vector<Coordinates> paintSpots;

    void buildTerrain(); //function which creates a matrix with the information we need
    bool possibleStep(Coordinates possition);

    friend class ShortestPathTree;
    friend class Commands;

public:
    Room& operator=(Room const& other);
    void readRoom(string fileName);
    void print();

};

#endif //TOM_JERRY_ROOM_H
