#include <algorithm>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>

bool isValid(std::vector<int> int_line);
bool notInRange(int num1, int num2);
bool removeLevel(std::vector<int> int_line);

int main(int argc, char *argv[]) {
  (void)argc;
  (void)argv;

  // read in file
  /*std::string input_file = "./sample_input.txt";*/
  std::string input_file = "./input.txt";
  std::ifstream file(input_file);

  if (!file.is_open()) {
    std::cout << "Failed to open" << input_file << "\n";
  }

  // reading files into a string vector
  auto list_vector = std::vector<std::vector<int>>{};
  int loop_counter = 0;
  int safe_counter = 0;

  for (std::string list_line; std::getline(file, list_line);) {
    auto ss = std::istringstream{list_line};

    list_vector.emplace_back();
    for (int i = 0; ss >> i;) {
      list_vector.back().push_back(i);
    }
  }

  // iterating through string vect
  for (const auto &level : list_vector) {
    // check 1
    /*bool valid_level = isValid(level);*/
    // check 2
    bool valid_level = removeLevel(level);
    loop_counter++;
    if (valid_level) {
      safe_counter++;
    }
  }
  // print out our results:
  std::cout << "Total safe reports: " << safe_counter << "\n";
}

// checking ascending vs. descending
bool isValid(std::vector<int> int_line) {

  bool is_asc_desc = false;

  // checking ascending
  if (std::is_sorted(int_line.begin(), int_line.end())) {
    is_asc_desc = true;
  }
  // checking descending
  std::reverse(int_line.begin(), int_line.end());
  if (std::is_sorted(int_line.begin(), int_line.end())) {
    is_asc_desc = true;
  }
  // returning number to beginning state
  std::reverse(int_line.begin(), int_line.end());

  if (is_asc_desc == false) {
    return false;
  }

  // checking that numbers are not the same and in range
  if (std::adjacent_find(int_line.begin(), int_line.end()) != int_line.end()) {
    return false;
  }

  if (std::adjacent_find(int_line.begin(), int_line.end(), notInRange) !=
      int_line.end()) {
    return false;
  }
  // if everything passes, return true
  return true;
}

// checking range requirements
bool notInRange(int num1, int num2) {
  if (abs(num1 - num2) > 3 || abs(num1 - num2) < 1) {
    return true;
  }
  return false;
}

// Criteria for part b
bool removeLevel(std::vector<int> int_line) {

  // first checking that isValid is already true
  if (isValid(int_line) == true) {
    return true;
  }
  // else we're removing a level
  for (std::size_t i = 0; i < int_line.size(); i++) {
    int temp_number = int_line[i];
    int_line.erase(int_line.begin() + i);
    // check if now safe
    if (isValid(int_line)) {
      return true;
    }
    int_line.insert(int_line.begin() + i, temp_number);
  }
  return false;
}