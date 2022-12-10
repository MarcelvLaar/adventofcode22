#include <fstream>
#include <iostream>
#include <string>
#include <vector>
bool checkright(std::vector<std::string> lines, int *size, int cx, int cy){
  for (size_t x = cx; x < *size; ++x){
    if (lines[cy][x+1] >= lines[cy][cx]){
      return false;
    }
  }
  return true;
}
bool checkleft(std::vector<std::string> lines, int *size, int cx, int cy){
  for (size_t x = cx; x > 0; --x){
    if (lines[cy][x-1] >= lines[cy][cx]){
      return false;
    }
  }
  return true;
}
bool checkup(std::vector<std::string> lines, int *size, int cx, int cy){
  for (size_t y = cy; y < *size; ++y){
    if (lines[y+1][cx] >= lines[cy][cx]){
      return false;
    }
  }
  return true;
}
bool checkdown(std::vector<std::string> lines, int *size, int cx, int cy){
  for (size_t y = cy; y > 0; --y){
    if (lines[y-1][cx] >= lines[cy][cx]){
      return false;
    }
  }
  return true;
}

int main(){
    std::string file = "input.txt";
    std::fstream fs;
    std::string output;
    std::vector<std::string> lines;
    fs.open(file, std::ios::in);
    while(getline(fs, output, '\n')){
      lines.push_back(output);
    }
    //hiervoor stond fs.close() hier
    int size = lines[0].size();
    int counter = (size * 4) - 4;

    for (size_t y = 1; y < size-1; ++y){
      for (size_t x = 1; x < size - 1; ++x){
        if (checkright(lines, &size, x, y)){
          ++counter;
        } else if(checkleft(lines, &size, x, y)){
          ++counter;
        } else if (checkup(lines, &size, x, y)){
          ++counter;
        } else if(checkdown(lines, &size, x, y)){
          ++counter;
        }
      }
    }
    std::cout << counter << "\n";
    fs.close(); //DIT << was het probleem
    return 0;
}
