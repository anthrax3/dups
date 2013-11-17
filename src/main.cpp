#include <iostream>
#include "duplicate_text_finder.hpp"

using namespace std;

int main(int argc, const char *argv[]) {
  cout << "dups - duplicate text finder" << std::endl;

  duplicate::duplicate_text_finder finder(6);

  auto duplicates = finder.find(".");
  // For each file in current directory
  // Scan file
  // Remove unique blocks
  // print duplicates
}
