
#ifndef TOM_JERRY_2_TREE_H
#define TOM_JERRY_2_TREE_H

#include "Room.h"
#include <algorithm>

struct Node {
    Coordinates data;
    Node* parent;
    vector<Node*> children;
    Node(Coordinates element) : data(element) {
        children.push_back(nullptr);
        children.pop_back();
    }
    bool hasChildren() {
        return !children.empty();
    }
    //sends children to Norway
    void removeChild(Node* child) {
        if(child == nullptr || child->parent == nullptr)
            return;
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
public:
    ShortestPathTree(string fileRoom) {
        root = nullptr;
        room.readRoom(fileRoom);

    }
    vector<vector<int>> indexedMatrix;

    bool createTree();
    bool addLeaf(Coordinates child) {
        return addLeaf(root, child);
    }
    void print() {
        print(root);
    }
    void getLeaves(vector<Node*> &leaves) {
        getLeaves(root, leaves);
    }

private:
    bool canAddLeaf(Node* current, Coordinates child);
    bool addLeaf(Node *current, Coordinates child);
    void print(Node* current);
    void getLeaves(Node* current, vector<Node*> &leaves);
    void removeAncestors(Node *current);
    void removeAllUnneededNodes();

};

#endif //TOM_JERRY_2_TREE_H
