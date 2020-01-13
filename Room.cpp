//
// Created by pon on 21.11.19.
//

#include "Room.h"
#include <fstream>
#include <queue>

void Room::readRoom(string fileName) {
    ifstream file;
    file.open(fileName);
    file >> this->width >>  this->length >>
    this->jerry.x >>  this->jerry.y >>
    this->tom.x >> this->tom.y >>
    this->numFurniture >> this->numPaintSpots;

    for(int i = 0; i < this->numFurniture; i++) {
        Furniture newFurniture;
        file >> newFurniture.startPoint.x >> newFurniture.startPoint.y;

        string line;
        getline(file, line);
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

    this->buildTerrain();
}

void Room::print() {
    for(int i = 0; i < terrain.size(); i++) {
        for(int j = 0; j < terrain[i].size(); j++) {
            cout << terrain[i][j] << " ";
        }
        cout << endl;
    }
}

/**
 * Private function used after reading the input from a file (in readRoom).
 * It arranges all of the objects from the input into one terrain.
 **/
void Room::buildTerrain() {
    this->terrain.resize(this->length);
    for(int i = 0; i < this->length; i++) {
        this->terrain[i].resize(this->width, '_');
    }

    //putting the furniture
    for(int i = 0; i < this->numFurniture; i++) {
        int startX = furniture[i].startPoint.x;
        int startY = furniture[i].startPoint.y;
        for(int j = startX; j < furniture[i].shape.size() + startX ; j++) {
            for(int k = startY; k < furniture[i].shape[j - startX].size() + startY ; k++) {
                terrain[j][k] = furniture[i].shape[j - startX][k - startY];
            }
        }
    }
    //replacing any blank spots
    for(int i = 0; i < terrain.size(); i++) {
        for(int j = 0; j < terrain[i].size(); j++) {
            if(terrain[i][j] == ' ')
                terrain[i][j] = '_';
        }
    }

    //putting the places which can be splatered with paint
    for(int i = 0; i < numPaintSpots; i++) {
        int X = paintSpots[i].x;
        int Y = paintSpots[i].y;
        if(terrain[X][Y] != '1')
            terrain[X][Y] = 'P';
    }

    //putting the cat
    terrain[tom.x][tom.y] = 'T';

    //putting the mouse
    terrain[jerry.x][jerry.y] = 'J';
}

bool Room::possibleStep(Coordinates possition) {
    int X = possition.x;
    int Y = possition.y;
    return (X >= 0 && Y >= 0 && X < length && Y < width && terrain[X][Y] != '1');

}

