#include <set>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class node{
  public:
    int size;
    string name;
    vector<node*> content;
    bool isdir;
    node(int _size, string _name, bool _isdir){
      size = _size;
      name = _name;
      isdir = _isdir;
    }
  int topcalcsize(int top){
    if (isdir){
      int counter = 0;
      for(node* n: content){
        counter += n -> topcalcsize(top);
      }
      int s = calcsize();
      if (s <= top){
        counter += s;
      }
      return counter;
    } else{
      return 0;
    }
  }
  vector<node*> atleast(int least){
    vector<node*> returnvalues;
    if (isdir){
      int cs = calcsize();
      if (least <= cs){
        node* coolnode = new node(cs, name, true);
        returnvalues.push_back(coolnode);
      }
      for (node* c : content){
        vector<node*> cs  = c -> atleast(least);
        returnvalues.insert(returnvalues.end(), cs.begin(), cs.end());
      }
    }
    return returnvalues;
  }
  int calcsize(){
    if (isdir){
      int counter = 0;
      for (node* n: content){
        counter += n -> calcsize();
      }
      return counter;
    }
    return size;
  }
};

node* mkdir(node* root, string name, vector<string> location){
  // cout << "making dir " << name << " in: " << printer(location) << "\n";
  node* currentfolder = root; //een pointer naar de huidige folder
  for(string s : location){ //bijv. (a, b) = /a/b
    for (node* f :currentfolder -> content){
      if (f -> name == s){
        currentfolder = f;
      }
    }
  }
  currentfolder -> content.push_back(new node(0, name, true));
  return root;
}
node* addfile(node* root, string name, int size, vector<string> location){
  // cout << "adding file " << name << " of size " << size << " in " << printer(location) << "\n";
  node* currentfolder = root;
  for(string s : location){
    for (node* f : currentfolder -> content){
      if (f -> name == s){
        currentfolder = f;
      }
    }
  }
  currentfolder -> content.push_back(new node(size, name, false));
  return root;
}

vector<int> processoutput(string filename){
  fstream fs;
  string output;
  int pos;
  vector<int> returnvalues;
  node* root = new node(0, "/", true);
  vector<string> location;
  // location.push_back("/");
  fs.open(filename, ios::in);
  while(getline(fs, output, '\n')){
    size_t pos = 0;
    vector<string> words;
    // cout << output << "\n";
    while((pos = output.find(' ')) != (string::npos)){
        words.push_back(output.substr(0,pos));
        output.erase(0, pos+1);
    }
    words.push_back(output);
    if (words[0] == "$"){
      if (words[1] == "cd"){
        if (words [2] == ".."){
          location.pop_back(); //a/b -> a
        } else{
          location.push_back(words[2]); //a -> a/b
        }
      } else if (words[1] == "ls"){
        //nothing?
      }
    } else if (words[0] == "dir"){
      root = mkdir(root, words[1], location);
    } else{
      int size = atoi(words[0].c_str());
      root = addfile(root, words[1], size, location);
    }
  }
  fs.close();
  returnvalues.push_back(root -> topcalcsize(100000));
  //exersize 2:
  int totalsize = root -> calcsize();
  int sizetobedeleted = 30000000 - (70000000 - totalsize);
  vector<node*> result = root -> atleast(sizetobedeleted);
  int min = 70000000;
  for(node* n:result){
    if (n -> size < min){
      min = n -> size;
    }
  }
  returnvalues.push_back(min);
  return returnvalues;
}

int main(){
  string file;
  vector<int> pos;
  cout << "please input location of terminal output file\n";
  cin >> file;
  pos = processoutput(file);
  cout << "\n";
  cout << "sum of directories with size <=100 000: \n";
  cout << pos[0] << "\n";
  // cout << "first marker after character (assignemnt 2) " << pos[1] << "\n";
  cout << "the size of the directory that needs to be deleted: \n";
  cout << pos[1] << "\n";
  return 0;
}
