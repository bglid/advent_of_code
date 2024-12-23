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
#include <unordered_map>
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
  std::unordered_map<int, int> frequency_2;

  while (std::getline(file, my_line)) {
    std::size_t splitter = my_line.find(" ");
    col1.push_back(std::stoi(my_line.substr(0, splitter)));
    col2.push_back(
        std::stoi(my_line.substr(splitter + 1, my_line.size() - splitter - 1)));
  }

  // Build a map for frequency in col 2
  for (int i = 0; i < col2.size(); i++) {
    frequency_2[col2[i]]++;
  }

  // Check the similarity between col[i] and it->second
  for (int i = 0; i < col1.size(); i++) {
    auto iter = frequency_2.find(col1[i]);
    if (iter == frequency_2.end()) {
      similarity.push_back(0);
    } else {
      int counter = iter->second;
      similarity.push_back(counter * col1[i]);
    }
  }

  // Adding up the values of the array
  int total = std::accumulate(std::begin(similarity), std::end(similarity), 0,
                              std::plus<int>());
  std::cout << "Total acumulation of similarity: " << total << "\n";
  return 0;
}
