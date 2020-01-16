#include <iostream>
#include <fstream>
//#include <vector>
//#include "Commands.h"
using namespace std;
int main() {
    ifstream f;
    f.open("test4.txt");
    int a, b,c ,d;
    //getline(f, a);
    f >> a >> b >> c >> d;
    cout << a << " " << b << c << d << endl;
    f.close();


    //Room room;
    // room.readRoom("test1.txt");
    // room.print();

    // Commands test("test1.txt");
   //test2.findAllPaths();
   //test2.printAllPaths();
   //test.writeTree("tree.dot");
   /*Path answer2;
   answer2 = test2.getDirtiestPath();
   answer2.printPath();
   Path one, two;
   test2.workWithJinx(one, two);
   one.printPath();
   two.printPath();/**/
   //test.choosePath();
   return 0;
}