#pragma once

namespace duplicate {

  struct metrics {
    metrics() : files_found(0), files_scanned(0), lines_scanned(0) {}
    int files_found;
    int files_scanned;
    int lines_scanned;
  };
};
