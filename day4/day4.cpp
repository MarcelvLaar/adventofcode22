#include <iterator>
#include <numeric>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

vector<int> readsection(string s){
  vector<int> output;
  int pos = s.find('-');
  output.push_back(atoi(s.substr(0,pos).c_str()));
  output.push_back(atoi(s.substr(pos+1,s.size() + pos).c_str()));
  return output;
}
bool fulloverlaps(string sectionpair){
  int pos = sectionpair.find(",");
  vector<int> s1 = readsection(sectionpair.substr(0,pos));
  vector<int> s2 = readsection(sectionpair.substr(pos+1, sectionpair.size() - pos));
  if ((s2[0] >= s1[0] && s2[1] <= s1[1]) ||
      (s1[0] >= s2[0] && s1[1] <= s2[1])){
    return true;
  }
  return false;
}
bool overlapsatall(string sectionpair){
  int pos = sectionpair.find(",");
  vector<int> s1 = readsection(sectionpair.substr(0,pos));
  vector<int> s2 = readsection(sectionpair.substr(pos+1, sectionpair.size() - pos));
  if ((s1[0] >= s2[0] && s2[1] >= s1[0]) ||
      (s2[0] >= s1[0] && s1[1] >= s2[0])){
    return true;
  }
  return false;
}
vector<int> calcoverlaps(string filename){
  fstream fs;
  string output;
  int ass1 = 0;
  int ass2 = 0;
  fs.open(filename, ios::in);
    while(getline(fs, output, '\n')){
      if(fulloverlaps(output)){
        ass1++;
      }
      if(overlapsatall(output)){
        ass2++;
      }
  }
    vector<int> returnvalue;
    returnvalue.push_back(ass1);
    returnvalue.push_back(ass2);
    return returnvalue;
}
int main(int arc, char** argv){
  string filename;
  cout << "enter filename\n";
  cin >> filename;
  vector<int> output = calcoverlaps(filename);
  cout << "there are " << output[0] << " full overlaps.\n";
  cout << "there are " << output[1] << " pairs that overlap at all. \n";
  return 0;
}
