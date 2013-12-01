#pragma once
#include <iostream>
#include <boost/progress.hpp>
#include "duplicate_text_finder.hpp"
#include "command_line_options_parser.hpp"
#include "metrics.hpp"

using namespace std;

namespace duplicate {
  class duplicate_finder {
  public:

    int run(int argc, const char* argv[]) {
      command_line_options_parser options_parser;
      
      auto config = options_parser.parse(argc, argv);

      if (!config.can_run()) {
	options_parser.show_help(std::cout);
	return -1;
      }
      
      if (config.show_version_only()) {
	options_parser.show_version(std::cout);
      }

      if (config.just_need_help()) {
	options_parser.show_help(std::cout);
      }

      duplicate::duplicate_text_finder finder(config.get_threshold());
      
      scan(config.get_input_files(), finder, config.verbose_output());

      return 0;
    }

    void scan(vector<string> files, duplicate::duplicate_text_finder finder, bool verbose) {
      if (files.size() > 0) {
	boost::progress_timer t;  // start timing

	metrics m;
	for (auto f : files) {
	
	  auto duplicates = finder.find(f, m);
	
	  for (auto dup : duplicates) {
	    std::cout << dup.second[0].range().size() << " duplicate lines found" << std::endl;
	    
	    for (auto m : dup.second) {
	      std::cout << "  " << m.path() << " " << m.range() << std::endl;
	      
	      if (verbose) {
		print_block(m.path().string(), m.range(), cout);
	      }
	    }
	  }
	}
	
	cout << "Found " << m.files_found << " files and scanned " << m.files_scanned << " files" << " totalling " << m.lines_scanned << " lines in ";
      }
    }
      
    void print_block(const string file_path, range range, ostream& output) {
      output << "----------------------" << endl;
	
      ifstream p(file_path);
      
      auto line_number = 0;
      
      for (string line; getline(p, line);) {
	line_number++;
	
	if (range.contains(line_number)) {
	  output << line << endl;
	}
      }
      output << "----------------------" << std::endl;
    }
  };
}
