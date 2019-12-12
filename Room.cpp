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
        for(int j = startY; j < furniture[i].shape.size() + startY; j++) {
            for(int k = startX; k < furniture[i].shape[j - startY].size() + startX; k++) {
                terrain[j][k] = furniture[i].shape[j - startY][k - startX];
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
        terrain[Y][X] = 'P';
    }

    //putting the cat
    terrain[tom.y][tom.x] = 'T';

    //putting the mouse
    terrain[jerry.y][jerry.x] = 'J';
}

bool Room::possibleStep(Coordinates possition) {
    int X = possition.x;
    int Y = possition.y;
    return (X >= 0 && Y >= 0 && X < width && Y < length && terrain[Y][X] != '1');

}

void Room::bfs(vector<vector<int> >& matrixWithPaths) {
    Coordinates startPoint = this->tom;
    Coordinates endPoint = this->jerry;

    vector<vector<bool> > visited(length);
    for(int i = 0; i < this->length; i++) {
        visited[i].resize(this->width, 0);
    }
    queue<Coordinates> q;
    q.push(startPoint);

    matrixWithPaths[startPoint.y][startPoint.x] = 0;
    visited[startPoint.y][startPoint.x] = true;

    while(!q.empty()) {
        Coordinates top = q.front();
        q.pop();
        int X = top.x;
        int Y = top.y;
        if(X == endPoint.x && Y == endPoint.y ) {
            return;
        }

        Coordinates currentCoordinate(Y , X + 1);
        //East
        if( possibleStep( currentCoordinate ) && visited[Y][X + 1] == 0) {
            q.push(currentCoordinate);
            matrixWithPaths[Y][X + 1] = matrixWithPaths[Y][X] + 1;
            visited[Y][X + 1] = true;
        }
        currentCoordinate = Coordinates(Y - 1, X);
        //South
        if( possibleStep( currentCoordinate ) && visited[Y - 1][X] == 0) {
            q.push(currentCoordinate);
            matrixWithPaths[Y - 1][X] = matrixWithPaths[Y][X] + 1;
            visited[Y - 1][X] = true;
        }
        currentCoordinate = Coordinates(Y , X - 1);
        //West
        if( possibleStep( currentCoordinate ) && visited[Y][X - 1] == 0) {
            q.push(currentCoordinate);
            matrixWithPaths[Y][X - 1] = matrixWithPaths[Y][X] + 1;
            visited[Y][X - 1] = true;
        }
        currentCoordinate = Coordinates(Y + 1, X);
        //North
        if( possibleStep( currentCoordinate ) && visited[Y + 1][X] == 0) {
            q.push(currentCoordinate);
            matrixWithPaths[Y + 1][X] = matrixWithPaths[Y][X] + 1;
            visited[Y + 1][X] = true;
        }


    }
}

