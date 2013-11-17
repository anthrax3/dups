#include <boost/test/unit_test.hpp>

#include "bucket.hpp"

#include <boost/filesystem.hpp>

BOOST_AUTO_TEST_CASE(matches_contain_source_path) {
  boost::filesystem::path p("some/path");
  duplicate::match match(p);

  BOOST_CHECK_EQUAL(match.path(), "some/path");
}

BOOST_AUTO_TEST_CASE(matches_contain_range) {
  boost::filesystem::path p("some/path");
  duplicate::match match(p);

  BOOST_CHECK_EQUAL(match.range(), duplicate::range(0,0));

}

BOOST_AUTO_TEST_CASE(matches_contain_path_and_range) {
  boost::filesystem::path p("some/path");
  duplicate::match match(p, duplicate::range(10, 100));
  duplicate::range r(10,100);
  
  BOOST_CHECK_EQUAL(match.range(), duplicate::range(10,100));
}
