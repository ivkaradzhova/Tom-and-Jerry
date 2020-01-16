//
// Created by pon on 15.01.20.
//
#include "Commands.h"

Path& Path::operator = (Path const& other) {
    this->length = other.length;
    this->turns = other.turns;
    this->numPaintSpots = other.numPaintSpots;
    this->steps.resize(other.steps.size());
    for(int i = 0; i < other.steps.size(); i++) {
        this->steps[i].x = other.steps[i].x;
        this->steps[i].y = other.steps[i].y;
    }
    this->commands = other.commands;
    return *this;
}

void Path::addStep(Coordinates newStep) {
    steps.push_back(newStep);
    length++;
    int X = newStep.x;
    int Y = newStep.y;
    //identify weather the new step is North, South, East, West
    if(X == steps[length - 2].x - 1) {
        commands.push_back('S');
    }
    if(X == steps[length - 2].x + 1) {
        commands.push_back('N');
    }
    if(Y == steps[length - 2].y - 1) {
        commands.push_back('E');
    }
    if(Y == steps[length - 2].y + 1) {
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

bool Path::inPath(Coordinates step){
    for(int i = 0; i < steps.size(); i++) {
        if(steps[i].x == step.x && steps[i].y == step.y) {
            return true;
        }
    }
    return false;
}

void Path::flipCommands() {
    for(int i = 0; i < commands.size(); i++) {
        switch (commands[i]) {
            case 'N': commands[i] = 'S'; break;
            case 'S': commands[i] = 'N'; break;
            case 'W': commands[i] = 'E'; break;
            case 'E': commands[i] = 'W'; break;
        }
    }
}
