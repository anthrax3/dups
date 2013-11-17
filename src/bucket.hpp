#pragma once

#include <string>
#include <map>
#include <vector>
#include <boost/filesystem.hpp>

namespace duplicate {

  class range {
    int from;
    int to;
  public:
    range() : range(0,0) {}
    range(int from, int to) : from(from), to(to) { }

    bool operator==(const range &other) const {
      return from == other.from && to == other.to;
    }
    friend std::ostream& operator<< (std::ostream& stream, const range& range);
  };
  
  inline std::ostream& operator<< (std::ostream& stream, const range& range) {
    return stream << "from " << range.from << " to " << range.to;
  }

  class match {
    typedef boost::filesystem::path path_type;
    path_type match_path;
    range match_range;
  public:
    match() {}
    match(path_type& path) : match_path(path), match_range(0, 0) {
    }
    match(path_type& path, range range) : match_path(path), match_range(range) {
    }

    path_type path() {
      return match_path;
    }

    range range() const {
      return match_range;
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

    bucket duplicates() {
      bucket result;

      for (auto e : contents) {
	if (e.second.size() > 1) {
	  result.contents[e.first] = e.second;
	}
      }

      return result;
    }

    bool is_empty() {
      return contents.size() == 0;
    }
  };
}
