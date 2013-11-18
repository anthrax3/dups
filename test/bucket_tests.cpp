
#include <boost/test/unit_test.hpp>

#include "bucket.hpp"


BOOST_AUTO_TEST_CASE(buckets_start_empty) {
  
  duplicate::bucket bucket;

  BOOST_CHECK(bucket.is_empty());
}

BOOST_AUTO_TEST_CASE(can_add_a_match_to_bucket_with_key) {
  duplicate::bucket bucket;
  duplicate::match m;
  bucket.add("key", m);

  BOOST_CHECK(!bucket.is_empty());
}

BOOST_AUTO_TEST_CASE(adding_match_to_bucket_already_containing_a_match) {
  duplicate::bucket bucket;
  duplicate::match m;
  bucket.add("key", m);
  bucket.add("key", m);

  BOOST_CHECK(!bucket.is_empty());
}

BOOST_AUTO_TEST_CASE(bucket_is_empty_if_no_duplicates) {
  duplicate::bucket bucket;
  duplicate::match m;
  bucket.add("key", m);
  bucket.add("key1", m);

  auto dups = bucket.duplicates();

  BOOST_CHECK(dups.is_empty());
}

BOOST_AUTO_TEST_CASE(small_text_change_are_not_duplicates) {
  duplicate::bucket bucket;
  duplicate::match m;
  bucket.add("key0", m);
  bucket.add("key1", m);

  auto dups = bucket.duplicates();

  BOOST_CHECK(dups.is_empty());
}

BOOST_AUTO_TEST_CASE(can_filter_bucket_contents_for_duplicates) {
  duplicate::bucket bucket;
  duplicate::match m;
  bucket.add("key", m);
  bucket.add("key", m);

  auto dups = bucket.duplicates();

  BOOST_CHECK(!dups.is_empty());
}

BOOST_AUTO_TEST_CASE(can_iterate_matches) {
  duplicate::bucket bucket;
  duplicate::match m;
  bucket.add("key", m);
  bucket.add("key", m);

  int count = 0;
  for (auto e : bucket) {
    count++;
    BOOST_CHECK_EQUAL(e.second.size(), 2);
  }

  BOOST_CHECK_EQUAL(count, 1);
}
