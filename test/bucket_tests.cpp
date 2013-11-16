#include <boost/test/unit_test.hpp>

namespace duplicate {
  class bucket {
    public:
    bool is_empty() {
      return true;
    }
  };
}


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
