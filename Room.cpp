//
// Created by pon on 21.11.19.
//

#include "Room.h"
#include <fstream>

void Room::createRoom(string fileName) {
    ifstream file;
    file.open(fileName);
    file >> this->width >>  this->length >>
    this->jerry.x >>  this->jerry.y >>
    this->tom.x >> this->jerry.y >>
    this->numFurniture >> this->numPaintSpots;

    for(int i = 0; i < this->numFurniture; i++) {
        Furniture newFurniture;
        file >> newFurniture.startPoint.x >> newFurniture.startPoint.y;

        string line;
        while(line != "===") {
            getline(file, line);
            if(line != "===")
                newFurniture.shape.push_back(line);
        }
        this->furniture.push_back(newFurniture);
    }

    for(int i = 0; i < this->numPaintSpots; i++) {
        Coordinates newCoordinate;
        file >> newCoordinate.x >> newCoordinate.y;
        this->paintSpots.push_back(newCoordinate);
    }
    this->buildRoom();
}

void Room::print() {
    for(int i = 0; i < terrain.size(); i++) {
        for(int j = 0; j < terrain[i].size(); i++) {
            cout << terrain[i][j] << " ";
        }
        cout << endl;
    }
}

void Room::buildRoom() {
    this->terrain.resize(this->length);
    for(int i = 0; i < this->length; i++) {
        this->terrain[i].resize(this->width, ' ');
    }
    //putting the furniture
    for(int i = 0; i < this->numFurniture; i++) {
        for(int j = furniture[i].startPoint.x; j < furniture[i].shape.size(); j++) {
            for(int k = furniture[i].startPoint.y; k < furniture[i].shape[j].size(); k++) {
                terrain[j][k] = furniture[i].shape[j][k];
            }
        }
    }
    //putting the places which can be splatted with paint
    for(int i = 0; i < numPaintSpots; i++) {
        int X = paintSpots[i].x;
        int Y = paintSpots[i].y;
        terrain[X][Y] = 'P';
    }
    //putting the kitty
    terrain[tom.x][tom.y] = 'T';
    //putting the mouse
    terrain[jerry.x][jerry.y] = 'J';
}