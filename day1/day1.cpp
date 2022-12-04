#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

string getlargestinventory(string filename){
  fstream fs;
  string output;
  int buffer = 0;
  vector<int> inventories;
  vector<int>:: iterator it;


  fs.open(filename, ios::in);
    if(fs.is_open()){
      while(getline(fs, output, '\n')){
        if (output == ""){
            inventories.push_back(buffer);
            buffer = 0;
        } else{
            buffer += atoi(output.c_str());
        }
      }
    }
  fs.close();
  it = max_element(inventories.begin(), inventories.end());
  return to_string(*it);
}

int main(int arc, char** argv){
  string filename;
  cout << "enter filename\n";
  cin >> filename;
  string result = getlargestinventory(filename);
  cout << "largest inventory: " << result << '\n';

  return 0;
}
