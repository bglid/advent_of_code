#include <algorithm>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>

int main() {

  // setting input file as a string
  /*std::string input = "./sample_input_a";*/
  std::string input = "./input_a.txt";

  // reading in the file
  std::ifstream file(input);

  // reading through the file line by line and assining to vectors
  std::string my_line;
  std::vector<int> col1;
  std::vector<int> col2;

  while (std::getline(file, my_line)) {
    std::size_t splitter = my_line.find(" ");
    col1.push_back(std::stoi(my_line.substr(0, splitter)));
    col2.push_back(
        std::stoi(my_line.substr(splitter + 1, my_line.size() - splitter - 1)));
  }

  // sorting the vectors
  std::sort(col1.begin(), col1.end());
  std::sort(col2.begin(), col2.end());

  // looping through and summing
  long long sum = 0;
  // checking that both cols are the same size
  if (col1.size() == col2.size()) {
    for (int i = 0; i < col1.size(); i++) {
      auto const &num1 = col1[i];
      auto const &num2 = col2[i];
      /*std::cout << col1[i] << " " << col2[i] << std::endl;*/
      sum += std::abs(num2 - num1);
    }
  }
  else{
    std::printf("Columns are different lengths");
  }
  // return our result
  std::cout << sum << std::endl;

  return 0;
}
