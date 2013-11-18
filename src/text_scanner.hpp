#pragma once
#include <istream>
#include <boost/circular_buffer.hpp>
#include <boost/functional/hash.hpp>

namespace duplicate {
  class text_scanner {
    boost::circular_buffer<std::string> buffer;
  public:
    text_scanner(size_t size) : buffer(size) {}

    void emit_block(size_t line_number, std::function<void (const std::string &, int, size_t)> fun) {
      std::string content;
      
      for (auto x : buffer) {
	content += x;
      }
      
      fun(content, line_number - buffer.size(), buffer.size());
    }
    
    void scan(std::istream& stream, std::function<void (const std::string &, int, size_t)> fun) {
      auto line_number = 0;
      for (std::string line; std::getline(stream, line);) {
	line_number++;
	if (line.length() > 0) {
	  buffer.push_back(line);
	  if (buffer.full()) {
	    emit_block(line_number, fun);
	  }
	} 
      }
    }
  };
}
