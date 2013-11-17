#pragma once
#include <istream>
#include <boost/circular_buffer.hpp>
#include <boost/functional/hash.hpp>

namespace duplicate {
  class text_scanner {
    boost::circular_buffer<std::string> buffer;
  public:
    text_scanner(size_t size) : buffer(size) {}
    
    void scan(std::istream& stream, std::function<void (const std::string &)> fun) {
      for (std::string line; std::getline(stream, line);) {
	buffer.push_back(line);

	if (buffer.full()) {
	  std::string content;

	  for (auto x : buffer) {
	    content += x;
	  }
	  
	  fun(content);
	}
      }
    }
  };
}
