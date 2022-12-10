#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int checkcycle(int *cycle, int *x){
  if ((*cycle-20) % 40 == 0){
    cout << "signal strength in cycle " << *cycle << " : " << *x << "\n";
    return *cycle * *x;
  }
  return 0;
}

int main(){
  string file = "input.txt";
  fstream fs;
  string output;
  int signal = 0;
  int x = 1;
  int cycle = 1;
  fs.open(file, ios::in);
  while(getline(fs, output, '\n')){
    if (output == "noop"){
      ++cycle;
      signal += checkcycle(&cycle, &x);
    } else{
      int num = atoi(output.substr(5, 3).c_str());
      ++cycle;
      signal += checkcycle(&cycle, &x);
      x += num;
      ++cycle;
      signal += checkcycle(&cycle, &x);
    }
  }
  cout << "signal: " << signal << "\n";
  fs.close();
  return 0;
}
