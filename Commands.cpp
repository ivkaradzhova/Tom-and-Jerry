
#include "Commands.h"
#include <fstream>
#include <queue>
#include <utility>

void Commands::getPathToRoot(Node *current, Path &pathFromCurrent) {
    if(current == nullptr) {
        return;
    }
    else {
        if(room.terrain[current->data.x][current->data.y] == 'P'){
            pathFromCurrent.numPaintSpots++;
        }
        pathFromCurrent.addStep(current->data);
        if(current->parent)
            getPathToRoot(current->parent, pathFromCurrent);
    }
}

//<may have to delete>

void Commands::findShortestPaths() {
    vector<Node*> leaves;
    tree.getLeaves(leaves);

    shortestPaths.resize(leaves.size());

    for(int i = 0; i < leaves.size(); i++) {
        getPathToRoot(leaves[i], shortestPaths[i]);
        shortestPaths[i].countTurns();
    }

}

void Commands::printShortestPaths() {
    for(int i = 0; i < shortestPaths.size(); i++) {
        shortestPaths[i].printPath();
    }
}

void Commands::printAllPaths() {
    for(int i = 0; i < allPaths.size(); i++) {
        allPaths[i].printPath();
    }
}

//</may have to delete>

bool Commands::possibleStep(Coordinates step, Path path) {
    return step.x >= 0 && step.y >= 0 && step.x < room.length
           && step.y < room.width && room.terrain[step.x][step.y] != '1'
           && !path.inPath(step);
}

void Commands::findAllPaths() {
    Coordinates start = room.tom;
    Coordinates final = room.jerry;

    Path currentPath;
    queue<Path> q;

    currentPath.addStep(start);
    q.push(currentPath);

    while(!q.empty()) {
        currentPath = q.front();
        q.pop();
        Coordinates lastStep;
        lastStep.x = currentPath.steps[currentPath.steps.size() - 1].x;
        lastStep.y = currentPath.steps[currentPath.steps.size() - 1].y;
        if(lastStep == final) {
            currentPath.countTurns();
            currentPath.flipCommands();
            this->allPaths.push_back(currentPath);
        }
        else {
            int j = 0;
            while (j < 4) {
                Coordinates nextStep;
                if(j == 0) nextStep = Coordinates(lastStep.x + 1, lastStep.y);
                if(j == 1) nextStep = Coordinates(lastStep.x - 1, lastStep.y);
                if(j == 2) nextStep = Coordinates(lastStep.x, lastStep.y + 1);
                if(j == 3) nextStep = Coordinates(lastStep.x, lastStep.y - 1);
                j++;
                if(possibleStep(nextStep, currentPath)) {
                    Path newPath;
                    for(int i = 0; i < currentPath.length; i++) {
                        if(room.terrain[currentPath.steps[i].x][currentPath.steps[i].y] == 'P')
                            newPath.numPaintSpots++;
                        newPath.addStep(currentPath.steps[i]);
                    }
                    if(room.terrain[nextStep.x][nextStep.y] == 'P')
                        newPath.numPaintSpots++;
                    newPath.addStep(nextStep);
                    q.push(newPath);
                }
            }
        }
    }


}

Path& Commands::getDirtiestPath(){
    findAllPaths();
    int maxPaintSpots = 0;
    for(int i = 0; i < allPaths.size(); i++) {
        if (allPaths[i].numPaintSpots > allPaths[maxPaintSpots].numPaintSpots ||
            (allPaths[i].numPaintSpots == allPaths[maxPaintSpots].numPaintSpots &&
             allPaths[i].turns < allPaths[maxPaintSpots].turns)) {
            maxPaintSpots = i;
        }
    }
    return allPaths[maxPaintSpots];
}

void Commands::workWithJinx(Path& drone1, Path& drone2) {
    findShortestPaths();

    int indexTomDrone = 0, indexJinxDrone = 0;

    for (int i = 0; i < shortestPaths.size(); i++) {
        int tomPaintSpots = shortestPaths[i].numPaintSpots;
        for (int j = i + 1; j < shortestPaths.size(); j++) {
            int maxPaintSpots = shortestPaths[indexJinxDrone].numPaintSpots + shortestPaths[indexTomDrone].numPaintSpots;
            int jinxPaintSpots = shortestPaths[j].numPaintSpots;
            if (maxPaintSpots < tomPaintSpots + jinxPaintSpots) {
                indexTomDrone = i;
                indexJinxDrone = j;
            }
        }
    }
    drone1 = shortestPaths[indexTomDrone];
    drone2 = shortestPaths[indexJinxDrone];

}

char Commands::determineWay(Coordinates curr, Coordinates next) {
    if(curr.x == next.x + 1) return 'N';
    if(curr.y == next.y + 1) return 'W';
    if(curr.x == next.x - 1) return 'S';
    if(curr.y == next.y - 1) return 'E';

}

void Commands::writeTransitions(ofstream &dotFile, Node *current) {
    queue< pair<Node*, int> > q;
    int id = 0;
    string from = "(" + to_string(current->data.x) + "," + to_string(current->data.y) + ")";
    dotFile << "\"" + from + " " + to_string(id) + "\""
            << " [label = \"" << "start\"];" << endl;

    q.push(make_pair(current, id));
    while(!q.empty()) {
        pair<Node*, int> top = q.front();
        q.pop();
        string from = "(" + to_string(top.first->data.x) + "," + to_string(top.first->data.y) + ")";
        if(top.first->hasChildren()) {
            for (int i = 0; i < top.first->children.size(); i++) {
                id++;
                string to = "(" + to_string(top.first->children[i]->data.x) + "," + to_string(top.first->children[i]->data.y) + ")";

                dotFile << "\"" + to + " " + to_string(id) + "\""
                        << " [label = \"" << determineWay(top.first->data, top.first->children[i]->data) << "\"];" << endl;
                dotFile << "\"" << from << " " << to_string(top.second) << "\" -> "
                        << "\"" << to   << " " << to_string(id) << "\"" << endl;
                q.push(make_pair(top.first->children[i], id));
            }
        }
    }
}

void Commands::writeTree(string filename){

    ofstream dotFile;
    dotFile.open(filename);
    dotFile << "digraph Choice {\n";

    writeTransitions(dotFile, tree.root);
    dotFile << "}";

}

string reverseString(string text) {
    for(int i = 0; i < text.size(); i++) {
        swap(text[i], text[text.size() - i - 1]);
    }
    return text;
}

void Commands::choosePath() {
    vector<Node*> leaves;
    tree.getLeaves(tree.root, leaves);
    cout << "You saw all of the paths, Tom! Now is your chance to make a mess AAAND blame it on Jerry!!\n"
            "Muahahahaha!!\n"
            "...soooo...please input the number of the path you want to take and I will give you all "
            "of the details you need.\n"
            "You have " << leaves.size() << " choices."<< endl;
    int input;
    while(input != -1) {
        cout << "Number: ";
        cin >> input;
        if(input >= leaves.size()) {
            cout << "Tom, I am looking forward to the execution of the plan!" << endl;
            break;
        }
        Path theChosen;
        getPathToRoot(leaves[input], theChosen);
        theChosen.countTurns();
        cout << "Commands you need to input: " << reverseString(theChosen.commands) << endl;
        cout << "Length of path: " << theChosen.length << endl;
        cout << "Number of turns: " << theChosen.turns << endl;
        cout << "Estimated amount of splattered paint: " << theChosen.numPaintSpots << endl;
    }
}

