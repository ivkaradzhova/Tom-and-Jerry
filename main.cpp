#include <iostream>
#include <fstream>
#include <vector>
#include "Commands.h"
using namespace std;
int main() {
   Room room;
   room.readRoom("test2.txt");
   room.print();

   Commands test2;
   test2.getShortestPaths("test2.txt");
   test2.printShortestPaths();
   return 0;
}