
#ifndef TOM_JERRY_2_TREE_H
#define TOM_JERRY_2_TREE_H

#include "Room.h"
#include <algorithm>

struct Node {
    Coordinates data;
    Node* parent;
    vector<Node*> children;
    Node(Coordinates element) : data(element) {
        parent = nullptr;
        children.push_back(nullptr);
        children.pop_back();
    }
    bool hasChildren() {
        return !children.empty();
    }
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
    vector<vector<int>> indexedMatrix;
    friend class Commands;
public:
    ShortestPathTree(){
        root = nullptr;
    }
    ShortestPathTree(Room _room) {
        root = nullptr;
        room = _room;
    }
    void setRoom(Room _room) {
        room = _room;
    }

    bool createTree();
    bool addLeaf(Coordinates child) {
        return addLeaf(root, child);
    }
    void getLeaves(vector<Node*> &leaves) {
        getLeaves(root, leaves);
    }

private:
    bool canAddLeaf(Node* current, Coordinates child);
    bool addLeaf(Node *current, Coordinates child);
    void getLeaves(Node* current, vector<Node*> &leaves);
    void removeAncestors(Node *current);
    void removeAllUnneededNodes();

};

#endif //TOM_JERRY_2_TREE_H
