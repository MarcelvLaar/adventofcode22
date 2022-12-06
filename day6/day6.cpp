#include <set>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int subroutine(vector<char> datastream, int packetlength){
  for(int i=0; i<datastream.size()-(packetlength-1); i++){
    set<char> s;
    for (int j=0+i; j<packetlength+i; j++){ //put i+packet in a set
      s.insert(datastream[j]);
    }
    if (s.size() > (packetlength-1)){ //check if that set if of size packetlength
      return i + packetlength;
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
    for (char c: output){
      characters.push_back(c);
    }
  }
  fs.close();
  returnvalue.push_back(subroutine(characters, 4));
  returnvalue.push_back(subroutine(characters, 14));
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
