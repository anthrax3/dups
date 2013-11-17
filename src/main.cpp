#include <iostream>
#include "duplicate_text_finder.hpp"

using namespace std;

int main(int argc, const char *argv[]) {
  cout << "dups - duplicate text finder" << std::endl;

  duplicate::duplicate_text_finder finder(6);

  auto duplicates = finder.find(".");

  for (auto dup : duplicates) {
    std::cout << dup.second[0].range().size() << " duplicate lines found" << std::endl;

    for (auto m : dup.second) {
      std::cout << "  " << m.path() << " " << m.range() << std::endl;
      std::cout << "----------------------" << std::endl;
      
      ifstream p(m.path().string());

      auto line_number = 0;

      for (std::string line; std::getline(p, line);) {
	line_number++;

	if (m.range().contains(line_number)) {
	  std::cout << line << std::endl;
	}
      }
      std::cout << "----------------------" << std::endl;
    }
  }
}
