//
// Created by pon on 14.12.19.
//

#ifndef TOM_JERRY_2_TREE_H
#define TOM_JERRY_2_TREE_H

#include "Room.h"
#include <algorithm>

struct Node {
    Coordinates data;
    Node* parent;
    vector<Node*> children;
    Node(Coordinates element) : data(element) {}
    bool hasChildren() {
        return !children.empty();
    }
    void removeChild(Node* child) {
        if(children.empty()) {
            return;
        }
        auto it = find(children.begin(), children.end(), child);
        if(it == children.end())
            return;
        else {
            children.erase(it);
        }
    }
};

class ShortestPathTree {
    Node* root;
    Room room;
    vector<vector<int>> indexedMatrix;
    bool bfs();
    bool canAddLeaf(Node* current, Coordinates child);
public:
    ShortestPathTree(string fileRoom) {
        root = nullptr;
        room.readRoom(fileRoom);
        if(!bfs()) {
            cout << "Sorry Tom! Jerry can't be reached in this room." << endl;
        }
    }
    bool addLeaf(Coordinates child) {
        return addLeaf(root, child);
    }
    void print() {
        print(root);
    }
private:
    bool addLeaf(Node *current, Coordinates child);
    void print(Node* current);
    void getLeaves(Node* current, vector<Node*> &leaves);
    void removeUnneededPathFromLeaf(Node* current);
    void removeAllUnneededNodes();
public:
    void createTree();

};

#endif //TOM_JERRY_2_TREE_H
