#include <iterator>
#include <numeric>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
vector<string> loadcrates(string filename) {
  fstream fs;
  string output;
  vector<string> returnvalue;
  fs.open(filename, ios::in);
  while(getline(fs,output,'\n')){
    returnvalue.push_back(output.c_str());
  }
  for(string s: returnvalue){
    cout << s << "\n";
  }
  fs.close();
  return returnvalue;
}
 vector<string> movecrates(string movefile, vector <string> crates){
   fstream fs;
   string output;
   vector<string> words;
   vector<string> returnvalue;
   fs.open(movefile, ios::in);
     while(getline(fs, output, '\n')){
       size_t pos = 0;
        vector<string> words;
       while((pos = output.find(' ')) != string::npos){
         words.push_back(output.substr(0, pos));
         output.erase(0, pos + 1);
       }
       int amount = atoi(words[1].c_str());
       int from = atoi(words[3].c_str()) -1;
       int to = atoi(words[5].c_str()) -1;
       for(int i=0; i<amount; i++){
         string grab = crates[from].substr(crates[from].size()-1, 1);
         crates[from].erase(crates[from].size()-1, 1);
         crates[to] += grab;
         // cout << "and put it right here: " << crates[to] << "\n";
       }
     }
   fs.close();
   return crates;

}
 vector<string> movecrates2(string movefile, vector <string> crates){
   fstream fs;
   string output;
   vector<string> words;
   vector<string> returnvalue;
   fs.open(movefile, ios::in);
     while(getline(fs, output, '\n')){
       size_t pos = 0;
        vector<string> words;
       while((pos = output.find(' ')) != string::npos){
         words.push_back(output.substr(0, pos));
         output.erase(0, pos + 1);
       }
       int amount = atoi(words[1].c_str());
       int from = atoi(words[3].c_str()) -1;
       int to = atoi(words[5].c_str()) -1;
         string grab = crates[from].substr(crates[from].size()-amount, amount);
         crates[from].erase(crates[from].size()-amount, amount);
         crates[to] += grab;
     }
   fs.close();
   return crates;
}

string lookattop(vector <string> crates){
  string output = "";
  for(int i=0; i<crates.size(); i++){
    output += crates[i].substr(crates[i].size()-1, 1);
  }
  return output;
}
int main(){
  string cratesfile;
  string movefile;
  vector<string> crates;
  cout << "your example file is split in two: moves and locations.\n";
  cout << "please input the location of the crates file\n";
  cin >> cratesfile;
  crates = loadcrates(cratesfile);
  cout << "now, please input the location of the moves file\n";
  cin >> movefile;
  cout << "starting top boxes: " << lookattop(crates) << "\n";
  crates = movecrates(movefile, crates);
  cout << "final top boxes (assignment 1): " << lookattop(crates) << "\n";
  crates = loadcrates(cratesfile);
  crates = movecrates2(movefile, crates);
  cout << "final top boxes (assignment 2): " << lookattop(crates) << "\n";
  return 0;
}
