#pragma once

#include <boost/program_options.hpp>
#include <initializer_list>
#include <boost/foreach.hpp>
#include <boost/filesystem.hpp>

using namespace std;

namespace duplicate {
  class config {
  private:
    boost::program_options::variables_map variables;
  public:
    config(const boost::program_options::variables_map& variables) : variables(variables) {
    }

    bool can_run() {
      return variables.size() > 0;
    }

    bool verbose_output() {
      return (variables.count("verbose") > 0);
    }

    bool just_need_help() {
      return variables.count("help") > 0;
    }


    bool show_version_only() {
      return variables.count("version") > 0;
    }

    const vector<string>& get_input_files() {
      return variables["input-files"].as<vector<string>>();
    }
  };
}
