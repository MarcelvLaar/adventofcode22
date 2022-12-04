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

string gettop3inventories(string filename){
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
    int returnvalue = 0;
    sort(inventories.begin(), inventories.end(), greater<int>());
    for (int i = 0; i < 3; i++) {
      returnvalue += inventories[i];
    }

  return to_string(returnvalue);
}
int main(int arc, char** argv){
  string filename;
  cout << "enter filename\n";
  cin >> filename;
  string largest = getlargestinventory(filename);
  cout << "largest inventory: " << largest << '\n';
  string top3 = gettop3inventories(filename);
  cout << "sum of top 3 inventories: " << top3 << '\n';


  return 0;
}
