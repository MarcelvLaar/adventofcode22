#include <set>
#include <iterator>
#include <numeric>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int subroutine(vector<char> datastream){
  cout << "starting subroutine\n";
  for(int i=0; i<datastream.size()-3; i++){
    set<char> s;
    for (int j=0+i; j<4+i; j++){
        s.insert(datastream[j]);
    }
    // cout << "s: " << datastream[i] << datastream[i+1] << datastream[i+2] << datastream[i+3] <<" (size " << s.size() <<")\n";

    if (s.size() > 3){
      return i + 4;
    }
  }
  return 42069;
}

int subroutine2(vector<char> datastream){
  cout << "starting subroutine2\n";
  for(int i=0; i<datastream.size()-13; i++){
    set<char> s;
    for (int j=0+i; j<14+i; j++){
        s.insert(datastream[j]);
    }
    // cout << "s: " << datastream[i] << datastream[i+1] << datastream[i+2] << datastream[i+3] <<" (size " << s.size() <<")\n";

    if (s.size() > 13){
      cout << "s.size: " << s.size() << "\n";
      return i + 14;
    }
  }
  return 42069;
}

vector<int> processdatastream(string filename){
  fstream fs;
  string output;
  vector<char> characters;
  vector<int> returnvalue;
  fs.open(filename, ios::in);
  while(getline(fs, output, '\n')){
    cout << "output: " << output << "\n";
    for (char c: output){
        characters.push_back(c);
    }
  }
  fs.close();
  returnvalue.push_back(subroutine(characters));
  returnvalue.push_back(subroutine2(characters));
  return returnvalue;
}
int main(){
  string file;
  vector<int> pos;
  cout << "please input location of datastream file\n";
  cin >> file;
  pos = processdatastream(file);
  cout << "first marker after character (assignment 1) " << pos[0] << "\n";
  cout << "first marker after character (assignemnt 2) " << pos[1] << "\n";
  return 0;
}
