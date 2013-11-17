#include <boost/test/unit_test.hpp>
#include "text_scanner.hpp"

BOOST_AUTO_TEST_CASE(scanner_emits_lines_when_full) {
  duplicate::text_scanner scanner(2);

  std::istringstream input;
  input.str("1\n2");

  std::string emitted;
  scanner.scan(input, [&](const std::string& t) {
      emitted = t;
    });
  BOOST_CHECK_EQUAL(emitted, "12");
}

BOOST_AUTO_TEST_CASE(can_hash_strings) {
  boost::hash<std::string> hasher;
  auto hash = hasher("foo");
}


BOOST_AUTO_TEST_CASE(scanner_supports_single_lines) {
  duplicate::text_scanner scanner(1);
  
  std::istringstream input;
  input.str("1");

  std::string emitted;
  scanner.scan(input, [&](const std::string& t) {
      emitted = t;
    });
  BOOST_CHECK_EQUAL(emitted, "1");
}
