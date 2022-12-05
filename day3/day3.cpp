#include <cctype>
#include <iterator>
#include <numeric>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
vector<char> split(string str){ //splits a string into a vector of chars
  vector<char> result;
  for(char ch: str){
    if (isalnum(ch)){
      result.push_back(ch);
    }
  }
  return result;
}

vector<char> intersection(vector<char> v1, vector<char> v2){ //set intersection
  vector<char> result;
  sort(v1.begin(), v1.end());
  sort(v2.begin(), v2.end());
  set_intersection(v1.begin(), v1.end(),
                   v2.begin(), v2.end(),
                   back_inserter(result));
  return result;
}

int calcvalue(char item){
  int value;
  if (item >= 'A' && item <= 'Z'){
    value = wchar_t(item - 38);
  } else if (item >= 'a' && item <= 'z'){
    value = wchar_t(item - 96);
  } else{
    cout << "could not calculate value of " << item << "\n";
  }
  return value;
}

int evalrucksack(string rucksack){
  int half = rucksack.length()/2;
  vector<char> firstcomp = split(rucksack.substr(0, half));
  vector<char> secondcomp = split(rucksack.substr(half, half));
  vector<char> intersec = intersection(firstcomp, secondcomp);
  return calcvalue(intersec[0]);
}

int calcbadge(vector<string> rucksacks){
  vector<char> r1 = split(rucksacks[0]);
  vector<char> r2 = split(rucksacks[1]);
  vector<char> r3 = split(rucksacks[2]);
  vector<char> halfintersec = intersection(r1, r2);
  vector<char> totalintersec = intersection(halfintersec, r3);
  return calcvalue(totalintersec[0]);
}

vector<int>evalrucksacks(string filename){
  fstream fs;
  string output;
  vector<int> rucksacksums;
  vector<string> groupbuffer;
  vector<int> badges;
  vector<int> returnvalues;
  int counter = 0;

  fs.open(filename, ios::in);
    if(fs.is_open()){
        while(getline(fs, output, '\n')){
            rucksacksums.push_back(evalrucksack(output));
            groupbuffer.push_back(output);
            counter++;
            if (counter == 3){
                badges.push_back(calcbadge(groupbuffer));
                groupbuffer.clear();
                counter = 0;
            }
        }
    }
  fs.close();
  returnvalues.push_back(accumulate(rucksacksums.begin(), rucksacksums.end(), 0));
  returnvalues.push_back(accumulate(badges.begin(), badges.end(), 0));
  return(returnvalues);

}

int main(int arc, char** argv){
  string filename;
  cout << "enter filename\n";
  cin >> filename;
  vector<int> output = evalrucksacks(filename);
  cout << "sum of all priorities: " << output[0] << '\n';
  cout << "sum of all badges: " << output[1] << '\n';
  return 0;
}
