#include <boost/test/unit_test.hpp>

#include "bucket.hpp"

#include <boost/filesystem.hpp>

BOOST_AUTO_TEST_CASE(matches_contain_source_path) {
  boost::filesystem::path p("some/path");
  duplicate::match match(p);

  BOOST_CHECK_EQUAL(match.path(), "some/path");
}
