#include <numeric>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

enum move {Rock, Paper, Scissors};

int tomove(string car){
  enum move hand;
  if (car == "A" || car == "X"){
    hand = Rock;
  } else if (car == "B" || car == "Y"){
    hand = Paper;
  } else if (car == "C" || car == "Z"){
    hand = Scissors;
  } else {
    cout << "someone used a move that doesn't exist!";
    hand = Rock;
  }
  return hand;
}
int calcscore(string strategy){
    int score = 0;
    int pos = strategy.find(" ");
    int oppmove = tomove(strategy.substr(0,1));
    int yourmove = tomove(strategy.substr(2,1));
    if (yourmove == Rock){
      score++;
    } else if (yourmove == Paper){
      score += 2;
    } else if (yourmove == Scissors){
      score += 3;
    }
    if (yourmove == oppmove){
      score += 3;
    } else if(oppmove == Rock && yourmove == Paper){
      score += 6;
    } else if(oppmove == Paper && yourmove == Scissors){
      score += 6;
    } else if(oppmove == Scissors && yourmove == Rock){
      score += 6;
    }
    return score;
}

int lose(int move){
  if (move == Rock){
    return Scissors;
  } else if (move == Paper){
    return Rock;
  } else if (move == Scissors){
    return Paper;
  } else{
    cout << "move doesn't exist!";
    return 5;
  }
}

int win(int move){
  if (move == Rock){
    return Paper;
  } else if (move == Paper){
    return Scissors;
  } else if (move == Scissors){
    return Rock;
  } else{
    cout << "move doesn't exist!";
    return 5;
  }
}

int calcscore2(string strategy){
  int score = 0;
  int pos = strategy.find(" ");
  string outcome = strategy.substr(2,1);
  int oppmove = tomove(strategy.substr(0,1));
  if (outcome == "X"){
    score += lose(oppmove)+1;
  } else if (outcome == "Y"){
    score += oppmove+1;
    score += 3;
  } else if (outcome == "Z"){
    score += win(oppmove)+1;
    score += 6;
  } else{
    cout << "the outcome was unexpected";
  }
  return score;
}

vector<int> calctotalscore(string filename){
  fstream fs;
  string output;
  vector<int> scores;
  vector<int> scores2;
  vector<int> returnvalues;

  fs.open(filename, ios::in);
    if(fs.is_open()){
      while(getline(fs, output, '\n')){
        scores.push_back(calcscore(output));
        scores2.push_back(calcscore2(output));
      }
    }
  fs.close();
  returnvalues.push_back(accumulate(scores.begin(), scores.end(), 0));
  returnvalues.push_back(accumulate(scores2.begin(), scores2.end(), 0));
  return returnvalues;
}


int main(int arc, char** argv){
  string filename;
  cout << "enter filename\n";
  cin >> filename;
  vector<int> totalscore = calctotalscore(filename);
  cout << "total score (first puzzle): " << totalscore[0] << '\n';
  cout << "total score (second puzzle): " << totalscore[1] << '\n';
  return 0;
}
