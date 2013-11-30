#pragma once
#include <iostream>

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
}
