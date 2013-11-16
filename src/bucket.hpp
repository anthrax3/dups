#pragma once

#include <string>
#include <map>
#include <vector>
#include <boost/filesystem.hpp>

namespace duplicate {

  class match {
    typedef boost::filesystem::path path_type;
    path_type match_path;
  public:
    match() {}
    match(path_type& path) {
      match_path = path;
    }

    path_type path() {
      return match_path;
    }
  };

  class bucket {
    std::map<std::string, std::vector<match> > contents;
  public:
    void add(std::string key, match m) {

      if (contents.find(key) == contents.end()) {
	std::vector<match> a;
	contents[key] = a;
      }
      contents[key].push_back(m);
    }

    std::vector<match>& operator[](const std::string& key) {
      return contents[key];
    }

    bool is_empty() {
      return contents.size() == 0;
    }
  };
}
