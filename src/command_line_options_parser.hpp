#pragma once

#ifndef BUILD_NUMBER
#define BUILD_NUMBER "ide"
#endif

#include <boost/program_options.hpp>
#include "config.hpp"

namespace duplicate {
  class command_line_options_parser {
    constexpr static auto verbose_option_name = "verbose";
    boost::program_options::options_description desc;
  public:
    command_line_options_parser() : desc("command-line-options") {
      desc.add_options()
	("help,h", "Display this message of command line options and exit")
	("version", "Display the application version and exit")
	("verbose,v",
	 "Include more details of builds and status. By default a count of builds in each 'state' is printed to the console. "
	 "Verbose output prints the status of each build and the causes of any failures.")
	("input-files",  boost::program_options::value<vector<string>>(), "input file");
    }
    
    config parse(int argc, const char *argv[]) {
      config result;

      boost::program_options::variables_map variables;
      
      boost::program_options::positional_options_description p;
      p.add("input-files", -1);


      boost::program_options::store(boost::program_options::command_line_parser(argc, argv).options(desc).positional(p).run(), variables);

      boost::program_options::notify(variables);

      if (variables.count(verbose_option_name) > 0) {
        result.set_verbose(true);
      }

      if (variables.count("help") > 0) {
        result.set_help_only();
      }

      if (variables.count("version") > 0) {
        result.set_version_only();
      }

      if (variables.count(verbose_option_name) > 0) {
        result.set_verbose(true);
      }
      
      if (variables.count("input-files")) {
	cout << "Input files supplied" << endl;
	result.set_input_files(variables["input-files"].as<vector<string>>());
      }
      
      return result;
    }

    void show_version(std::ostream &output) {
      std::cout << "dups v0.0." << BUILD_NUMBER << " - duplicate text finder" << std::endl;
    }

    void show_help(std::ostream &output) {
      show_version(output);
      output << std::endl;
      output << "usage:" << std::endl;
      output << "   dups [options]" << std::endl;
      output << std::endl;
      output << "Options:" << std::endl;
      output << desc << std::endl;
    }
  };
}
