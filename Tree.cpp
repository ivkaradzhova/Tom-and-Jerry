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
bool ShortestPathTree::bfs() {
    Coordinates startPoint = room.tom;
    Coordinates endPoint = room.jerry;

    vector<vector<bool> > visited(room.length);
    for(int i = 0; i < room.length; i++) {
        visited[i].resize(room.width, 0);
    }
    queue<Coordinates> q;
    q.push(startPoint);

    indexedMatrix.resize(room.length);
    for(int i = 0; i < room.length; i++) {
        indexedMatrix[i].resize(room.width, -1);
    }

    indexedMatrix[startPoint.y][startPoint.x] = 0;
    visited[startPoint.y][startPoint.x] = true;

    while(!q.empty()) {
        Coordinates top = q.front();
        q.pop();
        int X = top.x;
        int Y = top.y;
        if(X == endPoint.x && Y == endPoint.y ) {
            return true;
        }

        Coordinates currentCoordinate(Y , X + 1);
        //East
        if( room.possibleStep( currentCoordinate ) && visited[Y][X + 1] == 0) {
            q.push(currentCoordinate);
            indexedMatrix[Y][X + 1] = indexedMatrix[Y][X] + 1;
            visited[Y][X + 1] = true;
        }
        currentCoordinate = Coordinates(Y - 1, X);
        //South
        if( room.possibleStep( currentCoordinate ) && visited[Y - 1][X] == 0) {
            q.push(currentCoordinate);
            indexedMatrix[Y - 1][X] = indexedMatrix[Y][X] + 1;
            visited[Y - 1][X] = true;
        }
        currentCoordinate = Coordinates(Y , X - 1);
        //West
        if( room.possibleStep( currentCoordinate ) && visited[Y][X - 1] == 0) {
            q.push(currentCoordinate);
            indexedMatrix[Y][X - 1] = indexedMatrix[Y][X] + 1;
            visited[Y][X - 1] = true;
        }
        currentCoordinate = Coordinates(Y + 1, X);
        //North
        if( room.possibleStep( currentCoordinate ) && visited[Y + 1][X] == 0) {
            q.push(currentCoordinate);
            indexedMatrix[Y + 1][X] = indexedMatrix[Y][X] + 1;
            visited[Y + 1][X] = true;
        }
    }
    //Jerry can't be reached
    return false;
}


bool ShortestPathTree::canAddLeaf(Node* current, Coordinates child) {
    int X = current->data.x;
    int Y = current->data.y;
    return  indexedMatrix[Y][X] + 1 == indexedMatrix[child.y][child.x] &&
            ((Y == child.y - 1 && X == child.x) || (Y == child.y + 1 && X == child.x) ||
             (Y == child.y && X == child.x - 1) || (Y == child.y && X == child.x + 1));
}

bool ShortestPathTree::addLeaf(Node *current, Coordinates child) {
    if(root == nullptr) {
        root = new Node(child);
        root->parent = nullptr;
        return true;
    }
    else if(current->hasChildren() == 0){
        if(canAddLeaf(current, child)) {
            Node *newChild = new Node(child);
            newChild->parent = current;
            current->children.push_back(newChild);
            return true;
        }
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

/**
 * Prints the tree by traversing it pre-order.
 **/
void ShortestPathTree::print(Node* current) {
    cout << current->data.y << " "<< current->data.x <<endl;
    if(!current->hasChildren()) {
        cout << "=====" << endl;
        return;
    }
    else {
        for(int i = 0; i < current->children.size(); i++) {
            print(current->children[i]);
        }
    }
}

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
void ShortestPathTree::removeUnneededPathFromLeaf(Node *current) {
     if(!current->hasChildren()) {
         Node* helper = current->parent;
         helper->removeChild(current);
         delete current;
         removeUnneededPathFromLeaf(helper);
     }
     else
         return;
}

void ShortestPathTree::removeAllUnneededNodes() {
    vector<Node*> leaves;
    getLeaves(root, leaves);
    for(int i = 0; i < leaves.size(); i++) {
        if(leaves[i]->data != room.jerry) {
            removeUnneededPathFromLeaf(leaves[i]);
        }
    }
}

/**
 * Creates the tree of all the possible shortest paths that Tom can take.
 **/
void ShortestPathTree::createTree() {
    Coordinates start = room.tom;
    Coordinates end = room.jerry;

    vector<vector<bool> > visited(room.length);
    for(int i = 0; i < room.length; i++) {
        visited[i].resize(room.width, 0);
    }
    visited[start.y][start.x] = 1;

    queue<Coordinates> q;
    q.push(start);

    while(!q.empty()) {
        Coordinates top = q.front();
        q.pop();

        addLeaf(top);
        if(top.x == end.x && top.y == end.y) {
            removeAllUnneededNodes();
            return;
        }

        if(top.x - 1 >= 0 && !visited[top.y][top.x - 1]) {
            q.push(Coordinates(top.y,top.x - 1));
            visited[top.y][top.x - 1] = 1;
        }
        if(top.x + 1 < room.width && !visited[top.y][top.x + 1]) {
            q.push(Coordinates(top.y,top.x + 1));
            visited[top.y][top.x + 1] = 1;

        }
        if(top.y - 1 >= 0 && !visited[top.y - 1][top.x]) {
            q.push(Coordinates(top.y - 1,top.x));
            visited[top.y - 1][top.x] = 1;

        }
        if(top.y + 1 < room.width && !visited[top.y + 1][top.x]) {
            q.push(Coordinates(top.y + 1,top.x));
            visited[top.y + 1][top.x] = 1;
        }
    }
}
