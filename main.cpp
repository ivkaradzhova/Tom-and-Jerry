#include <iostream>
#include <fstream>
#include <vector>
#include "Tree.h"
using namespace std;
int main() {
    ShortestPathTree t("test2.txt");
  /*  t.addLeaf(Coordinates(0,0));
    t.addLeaf(Coordinates(0,1));
    t.addLeaf(Coordinates(0,2));
    t.addLeaf(Coordinates(1,0));
    t.addLeaf(Coordinates(1,1));

*/
    t.createTree();
    t.print();

   return 0;
}