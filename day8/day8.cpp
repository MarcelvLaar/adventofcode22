#include <set>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

string direction(int direction){
  switch (direction){
    case 1: return "right";
    case 2: return "left";
    case 3: return "up";
    case 4: return "down";
  }
  return "";
}
bool checkdirection(int direction, vector<string>& lines, int x, int y){
  int size = lines[0].size();
  int height = lines.size();
  switch (direction){
    case 1:
        for (int currentx = x; currentx<size; currentx++){
          if (lines[y][currentx+1] >= lines[y][x]){
            return false;
          }
        }
        return true;
    case 2:
        for (int currentx = x; currentx>=0; currentx--){
          if (lines[y][currentx-1] >= lines[y][x]){
            return false;
          }
        }
        return true;
    case 3:
        for (int currenty = y; currenty<height; currenty++){
          if (lines[currenty+1][x] >= lines[y][x]){
            return false;
          }
        }
        return true;
    case 4:
        for (int currenty = y; currenty>=0; currenty--){
          if (lines[currenty-1][x] >= lines[y][x]){
            return false;
          }
        }
        return true;
    }
  return false;
}
int lookatlines(string filename){
  fstream fs;
  string output;
  int counter;
  vector<string> lines;
  fs.open(filename, ios::in);
  while(getline(fs, output, '\n')){
    lines.push_back(output);
  }
  counter = (lines[0].size()*2) + ((lines.size()-2)*2) ; //top and bottom of the lines are visible
  // cout << "visible from outside: " << counter << "\n";
  for( int y = 1; y< lines.size()-1; y++){
    for (int x = 1; x < lines[0].size()-1; x++){
      char c = '0';
      for (int i=1; i<=4; i++){
        if (checkdirection(i, lines, x,y)){
          c = '1';
          counter ++;
          // cout << lines[y][x] << "(" << x << "," << y << ") returned true in direction " << direction(i) << "\n";
          break;
        }
      }
      // std::cout << c;
    }
  }
  fs.close();
  return counter;
}
int main(){
  int visibletrees;
  string file = "jobinput.txt";
  // cout << "please input location of tree file\n";
  // cin >> file;
  visibletrees = lookatlines(file);
  cout << "visible trees: " << visibletrees << "\n";
  return 0;
}
