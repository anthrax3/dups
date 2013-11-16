#include <boost/test/unit_test.hpp>

namespace duplicatate {
  class bucket {
    public:
    bool is_empty() {
      return true;
    }
  };
}


BOOST_AUTO_TEST_CASE(buckets_start_empty) {
  
  duplicatate::bucket bucket;

  BOOST_CHECK(bucket.is_empty());
}
