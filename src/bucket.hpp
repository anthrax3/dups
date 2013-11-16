#pragma once

#include <string>
#include <map>
#include <vector>

namespace duplicate {

  class match {
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
