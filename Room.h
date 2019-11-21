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
};

struct Furniture {
    Coordinates startPoint;
    vector<string> shape;
};

class Room {
    vector<vector<char> > terrain;
    int length, width;
    int numFurniture,  numPaintSpots;
    Coordinates tom, jerry;
    vector<Furniture> furniture;
    vector<Coordinates> paintSpots;

    void buildRoom(); //function which creates a matrix with the information we need

public:
    void createRoom(string fileName);
    vector<vector<char> > getTerrain();
    void print();

};


#endif //TOM_JERRY_ROOM_H
