#include <boost/test/unit_test.hpp>
#include "text_scanner.hpp"

BOOST_AUTO_TEST_CASE(scanner_emits_lines_when_full) {
  duplicate::metrics m;
  duplicate::text_scanner scanner(2, m);

  std::istringstream input;
  input.str("1\n2");

  std::string emitted;
  scanner.scan(input, [&](const std::string& t, int start, int len) {
      emitted = t;
    });
  BOOST_CHECK_EQUAL(emitted, "12");
}

BOOST_AUTO_TEST_CASE(can_hash_strings) {
  boost::hash<std::string> hasher;
  auto hash = hasher("foo");
}


BOOST_AUTO_TEST_CASE(scanner_supports_single_lines) {
  duplicate::metrics m;
  duplicate::text_scanner scanner(1, m);
  
  std::istringstream input;
  input.str("1");

  std::string emitted;
  scanner.scan(input, [&](const std::string& t, int start, int len) {
      emitted = t;
    });
  BOOST_CHECK_EQUAL(emitted, "1");
}

BOOST_AUTO_TEST_CASE(scanner_ignores_blank_lines) {
  duplicate::metrics m;
  duplicate::text_scanner scanner(2, m);
  
  std::istringstream input;
  input.str("1\n\n2");

  std::string emitted;
  scanner.scan(input, [&](const std::string& t, int start, int len) {
      emitted = t;
    });
  BOOST_CHECK_EQUAL(emitted, "12");
}

