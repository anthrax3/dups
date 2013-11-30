#pragma once
#include <iostream>
#include <fstream>
#include <boost/regex.hpp>
#include <boost/filesystem.hpp>
#include "bucket.hpp"
#include "text_scanner.hpp"

using namespace std;

namespace duplicate {

  class console_progress_ticker {
    constexpr static auto t = "-\\|//-/|\\";
    constexpr static auto KILL_EOL = "\033[K";
    unsigned int index;
    string last_message;
  public:
    console_progress_ticker() : index(0), last_message("") {}

    void tick() {
      cout << "\b" << t[index % 7];
      index++;
    }
    void tick(const string& message) {
      cout << KILL_EOL;
      cout << "scanning: " << message << "\r";
      last_message = message;
    }
    
    void clear() {
      cout << "\b" << KILL_EOL;
    }
  };

  class duplicate_text_finder {
    int match_threshold;

    boost::regex build_regex() {
      string pattern_text = ".*("
	"\\.cpp"
	"|\\.h"
	"|\\.hpp"
	"|\\.java"
	"|\\.scala"
	")$"
	;
      return boost::regex(pattern_text);
    }
    
  public:
    duplicate_text_finder(int match_threshold) : match_threshold(match_threshold) {}
    
    bucket find(std::string path) {
      console_progress_ticker ticker;
      bucket result;
      text_scanner scanner(match_threshold);

      boost::regex pattern = build_regex();
      for (boost::filesystem::recursive_directory_iterator iter(path), end; iter != end;  ++iter) {
	std::string name = iter->path().leaf().string();

	if (regex_match(name, pattern)) {
	  ticker.tick();
	  std::ifstream file(iter->path().string());

	  scanner.scan(file, [&](std::string text, int start, size_t len) {
	      boost::filesystem::path p = *iter;
	      match m(p, range(start, start + len));
	      result.add(text, m);
	    });
	}
      }
      ticker.clear();
      return result.duplicates();
    }
    
    int threshold() const {
      return match_threshold;
    }
  };
}
