//
// Created by pon on 16.12.19.
//

#include "Commands.h"


void Path::addStep(Coordinates newStep) {
    steps.push_back(newStep);
    length++;

    int X = newStep.x;
    int Y = newStep.y;
    //identify weather the new step is North, South, East, West
    if(X == steps[length - 2].x - 1) {
        commands.push_back('S');
    }
    else if(X == steps[length - 2].x + 1) {
        commands.push_back('N');
    }
    else if(Y == steps[length - 2].y - 1) {
        commands.push_back('E');
    }
    else if(Y == steps[length - 2].y + 1) {
        commands.push_back('W');
    }
}


void Path::countTurns() {
    for(int i = 1; i < commands.size(); i++) {
        if(commands[i] != commands[i - 1]) {
            turns++;
        }
    }
}

void Path::printPath() {
    for(int i = 0; i < steps.size(); i++) {
        cout << "(" << steps[i].x << " " << steps[i].y << ") ";
    }
    cout << endl;
    cout << "length = " << length << endl;
    cout << "turns  = " << turns << endl;
    cout << "number of paint splatering spots = " << numPaintSpots << endl;
    cout << "commands: " << commands << endl;
    cout << "===========" << endl;

}



void Commands::getPathFromRoot(Node *current, Path &pathFromCurrent) {
    if(current == nullptr) {
        return;
    }
    else {
        if(room.terrain[current->data.x][current->data.y] == 'P'){
            pathFromCurrent.numPaintSpots++;
        }
        pathFromCurrent.addStep(current->data);
        if(current->parent)
            getPathFromRoot(current->parent, pathFromCurrent);
    }
}

void Commands::getShortestPaths(string filename) {
    room.readRoom(filename);
    ShortestPathTree t(filename);
    if(!t.createTree()) {
        cout << "Sorry Tom! Jerry can't be reached in this room. "
                "Don't try to splatter paint anywhere!" << endl;
        return;
    }

    vector<Node*> leaves;
    t.getLeaves(leaves);

    shortestPaths.resize(leaves.size());

    for(int i = 0; i < leaves.size(); i++) {
        getPathFromRoot(leaves[i], shortestPaths[i]);
        shortestPaths[i].countTurns();
    }

}


void Commands::printShortestPaths() {
    for(int i = 0; i < shortestPaths.size(); i++) {
        shortestPaths[i].printPath();
    }

}
