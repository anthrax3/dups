#pragma once
#include <istream>
#include <boost/circular_buffer.hpp>
#include <boost/functional/hash.hpp>

namespace duplicate {
  class text_scanner {
    boost::circular_buffer<std::string> buffer;
  public:
    text_scanner(size_t size) : buffer(size) {}
    
    void scan(std::istream& stream, std::function<void (const std::string &, int, size_t)> fun) {
      auto line_number = 0;
      for (std::string line; std::getline(stream, line);) {
	if (line.length() > 0) {
	  buffer.push_back(line);
	  line_number++;
	  if (buffer.full()) {
	    std::string content;
	    
	    for (auto x : buffer) {
	      content += x;
	    }
	    
	    fun(content, line_number, buffer.size());
	  }
	} 
      }
    }
  };
}
