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
    Path& operator = (Path const& other);
    void countTurns();
    void addStep(Coordinates newStep);
    bool inPath(Coordinates step);
    void printPath();
    void flipCommands();
    void countPaintSpots(Room room);
};


class Commands {
    Room room;
    ShortestPathTree tree;
    vector<Path> shortestPaths;
    vector<Path> allPaths;

public:
    Commands(Room _room) {
        this->room = _room;
        tree.setRoom(this->room);
        if(!tree.createTree()) {
            cout << "Sorry Tom, Jerry can't be reached in this room.\n "
                    "Better luck next time!" << endl;
            return;
        }
    }

    void choosePath();

    void findShortestPaths();
    Path& getDirtiestPath();
    void workWithJinx(Path& drone1, Path& drone2);
    void findAllPaths();


    void writeTree(string filename);
    void writeTransitions(ofstream &dotFile, Node *current);
    char determineWay(Coordinates curr, Coordinates next);
    void printShortestPaths();
    void printAllPaths();

private:
    void getPathToRoot(Node *current, Path &pathFromCurrent);
    bool possibleStep(Coordinates step, Path path);
};


#endif //TOM_JERRY_2_COMMANDS_H
