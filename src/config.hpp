#pragma once

#include <initializer_list>
#include <boost/foreach.hpp>
#include <boost/filesystem.hpp>

using namespace std;

namespace duplicate {
  class config {
  private:
    bool verbose;
    bool help_only;
    bool version_only;
    vector<string> input_files;
  public:
    config() {
      verbose = false;
      help_only = false;
    }

    void set_verbose(bool b) {
      verbose = b;
    }

    bool verbose_output() {
      return verbose;
    }

    void set_help_only() {
      help_only = true;
    }

    bool just_need_help() {
      return help_only;
    }

    void set_version_only() {
      version_only = true;
    }

    bool show_version_only() {
      return version_only;
    }

    void set_input_files(const vector<string>& files) {
      for (auto f : files) {
	input_files.push_back(f);
      }
    }

    vector<string>& get_input_files() {
      return input_files;
    }
  };
}
