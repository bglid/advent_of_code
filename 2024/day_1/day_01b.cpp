#include <algorithm>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <numeric>
#include <ostream>
#include <string>
#include <vector>

int main() {

  // setting input file as a string
  /*std::string input = "./sample_input_a";*/
  std::string input = "./input_a.txt";

  // reading in the file
  std::ifstream file(input);
  if (!file.is_open()) {
    std::cerr << "Failed to open the file: " << input << "\n";
    return 1;
  }

  // reading through the file line by line and assining to vectors
  std::string my_line;
  std::vector<int> col1;
  std::vector<int> col2;
  std::vector<int> similarity;

  while (std::getline(file, my_line)) {
    std::size_t splitter = my_line.find(" ");
    col1.push_back(std::stoi(my_line.substr(0, splitter)));
    col2.push_back(
        std::stoi(my_line.substr(splitter + 1, my_line.size() - splitter - 1)));
  }

  // looping through the first column, checking if in second column
  for (int i = 0; i < col1.size(); ++i) {
    int counter = 0;
    // checking if val exists first:
    // declaring iterator
    std::vector<int>::iterator it;
    it = std::find(col2.begin(), col2.end(), col1[i]);
    if (it == col2.end()) {
      /*std::cout << "Element " << col1[i] << " not found in array 2" << "\n";*/
      similarity.push_back(counter);
    } else {
      for (int j = 0; j < col2.size(); ++j) {
        if (col2[j] == col1[i]) {
          counter++;
        }
      }
      /*std::cout << col1[i] << " appears in col2 " << counter << " times\n";*/
      similarity.push_back(col1[i] * counter);
    }
  }

  // Adding up the values of the array
  int total = std::accumulate(std::begin(similarity), std::end(similarity), 0,
                              std::plus<int>());
  std::cout << "Total acumulation of similarity: " << total << "\n";
  return 0;
}
