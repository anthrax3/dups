#include <boost/test/unit_test.hpp>

#include "duplicate_text_finder.hpp"


BOOST_AUTO_TEST_CASE(finder_accepts_threshold) {
  
  duplicate::duplicate_text_finder finder(2);

  BOOST_CHECK_EQUAL(finder.threshold(), 2);
}

