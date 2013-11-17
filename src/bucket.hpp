#pragma once

#include <string>
#include <map>
#include <vector>
#include <boost/filesystem.hpp>
#include <boost/functional/hash.hpp>

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

    size_t size() const {
      return to - from;
    }

    bool contains(int line_number) {
      return line_number >= from && line_number <= to;
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
    typedef std::string key_type;
 
    std::map<key_type, std::vector<match> > contents;
    typedef std::map<key_type, std::vector<match> >::iterator iterator;
    typedef std::map<key_type, std::vector<match> >::const_iterator const_iterator;
  public:
    void add(key_type key, match m) {
      boost::hash<std::string> string_hash;

      std::size_t h = string_hash(key);

      if (contents.find(key) == contents.end()) {
	std::vector<match> a;
	contents[key] = a;
      }
      contents[key].push_back(m);
    }

    std::vector<match>& operator[](const key_type& key) {
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

    iterator begin() { return contents.begin(); }

    const_iterator begin() const { return contents.begin(); }

    iterator end() { return contents.end(); }

    const_iterator end() const { return contents.end(); }
  };
}
