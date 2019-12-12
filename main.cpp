#include <iostream>
#include <fstream>
#include "Room.h"
using namespace std;
int main() {
      Room ex1;
      ex1.readRoom("test2.txt");
      ex1.print();
      vector<vector<int> > asd;
      asd.resize(6);
      for(int i = 0; i < asd.size(); i++)
      {
          asd[i].resize(5);
      }
      ex1.bfs(asd);
      cout << endl;

      //cout << ex1.possibleStep(Coordinates(2, 2)) << endl;
    for(int i = 0; i < asd.size(); i++)
    {
        for(int j = 0; j < asd[i].size(); j++) {
            cout << asd[i][j] << " ";
        }
        cout << endl;
    }
    //ex1.print();

    return 0;
}