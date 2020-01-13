
#include "Tree.h"

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
        root->parent = nullptr;
        return true;
    }
        /*else if(current->hasChildren() == 0){
             if(canAddLeaf(current, child)) {
                 Node *newChild = new Node(child);
                 newChild->parent = current;
                 current->children.push_back(newChild);
                 return true;
             }
         }*/
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


bool ShortestPathTree::canAddLeaf(Node* current, Coordinates child) {
    int X = current->data.x;
    int Y = current->data.y;
    return  indexedMatrix[X][Y] + 1 == indexedMatrix[child.x][child.y] &&
            ((Y == child.y - 1 && X == child.x) || (Y == child.y + 1 && X == child.x) ||
             (Y == child.y && X == child.x - 1) || (Y == child.y && X == child.x + 1));
}

/**
 * Removes all of the ancestors of the given leaf
 * till a node with other children is reached.
 **/
void ShortestPathTree::removeAncestors(Node *current) {
    if(current != nullptr && !current->hasChildren()) {
        Node* helper = current->parent;
        helper->removeChild(current);
        delete current;
        removeAncestors(helper);
    }
    else
        return;
}


/**
 * Removes all of the nodes which are not a part of a path reaching Jerry.
 **/
void ShortestPathTree::removeAllUnneededNodes() {
    vector<Node*> leaves;
    getLeaves(root, leaves);
    for(int i = 0; i < leaves.size(); i++) {
        if(leaves[i]->data != room.jerry) {
            removeAncestors(leaves[i]);
        }
    }
}

