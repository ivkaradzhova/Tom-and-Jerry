//
// Created by pon on 15.12.19.
//
#include "Tree.h"
#include <queue>

/**
 * Marks in indexMatrix the cells which belong to any of the shortest path
 * with the number of steps from Tom to them.
 * Returns false if Jerry can't be reached.
 **/
bool ShortestPathTree::createTree() {
    Coordinates start = room.tom;
    Coordinates finish = room.jerry;

    vector<vector<bool> > visited(room.length, vector<bool>(room.width, 0));

    queue<Coordinates> q;
    q.push(start);

    indexedMatrix.resize(room.length);
    for(int i = 0; i < room.length; i++) {
        indexedMatrix[i].resize(room.width, -1);
    }

    indexedMatrix[start.x][start.y] = 0;
    visited[start.x][start.y] = true;

    while(!q.empty()) {
        Coordinates top = q.front();
        q.pop();

        addLeaf(top);
        int X = top.x;
        int Y = top.y;

        if(X == finish.x && Y == finish.y ) {
            removeAllUnneededNodes();
            return true;
        }

        Coordinates currentCoordinate(X + 1, Y);
        //South
        if( room.possibleStep( currentCoordinate ) && visited[X + 1][Y] == 0) {
            q.push(currentCoordinate);
            indexedMatrix[X + 1][Y] = indexedMatrix[X][Y] + 1;
            visited[X + 1][Y] = true;
        }
        currentCoordinate = Coordinates(X, Y - 1);
        //West
        if( room.possibleStep( currentCoordinate ) && visited[X][Y - 1] == 0) {
            q.push(currentCoordinate);
            indexedMatrix[X][Y - 1] = indexedMatrix[X][Y] + 1;
            visited[X][Y - 1] = true;
        }
        currentCoordinate = Coordinates(X - 1, Y);
        //North
        if( room.possibleStep( currentCoordinate ) && visited[X - 1][Y] == 0) {
            q.push(currentCoordinate);
            indexedMatrix[X - 1][Y] = indexedMatrix[X][Y] + 1;
            visited[X - 1][Y] = true;
        }
        currentCoordinate = Coordinates(X, Y + 1);
        //East
        if( room.possibleStep( currentCoordinate ) && visited[X][Y + 1] == 0) {
            q.push(currentCoordinate);
            indexedMatrix[X][Y + 1] = indexedMatrix[X][Y] + 1;
            visited[X][Y + 1] = true;
        }
    }
    //Jerry can't be reached
    return false;
}


/**
 * Saves all of the leaves of the tree in vector<Node*> leaves.
 **/
void ShortestPathTree::getLeaves(Node* current, vector<Node*> &leaves) {
    if(!current->hasChildren()) {
        leaves.push_back(current);
    }
    else {
        for(int i = 0; i < current->children.size(); i++) {
            getLeaves(current->children[i], leaves);
        }
    }
}

bool ShortestPathTree::addLeaf(Node *current, Coordinates child) {
    if(root == nullptr) {
        root = new Node(child);
        return true;
    }
    else {
        if(canAddLeaf(current, child)) {
            Node *newChild = new Node(child);
            newChild->parent = current;
            current->children.push_back(newChild);
            return true;
        }
        for(int i = 0; i < current->children.size(); i++) {
            addLeaf(current->children[i], child);
        }
    }
    return false;
}
