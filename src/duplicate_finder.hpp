#pragma once
#include <iostream>
#include "duplicate_text_finder.hpp"
#include "command_line_options_parser.hpp"

using namespace std;

namespace duplicate {
  class duplicate_finder {
  public:
    int run(int argc, const char* argv[]) {
      command_line_options_parser options_parser;
      
      auto config = options_parser.parse(argc, argv);
      
      if (config.show_version_only()) {
	options_parser.show_version(std::cout);
      }

      if (config.just_need_help()) {
	options_parser.show_help(std::cout);
      }

      duplicate::duplicate_text_finder finder(6);
      
      if (config.get_input_files().size() > 0) {
	for (auto f : config.get_input_files()) {
	
	  auto duplicates = finder.find(f);
	
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
      }
      return 0;
    }
  };
}
