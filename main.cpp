#include <iostream>
#include <fstream>
#include "Room.h"
using namespace std;
int main() {
    //ifstream ifile("deleteME!.tht");
    Room ex1;
    ex1.createRoom("deleteME!.tht");
    ex1.print();
    return 0;
}