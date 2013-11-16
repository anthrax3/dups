#include <boost/test/unit_test.hpp>
#include <string>
#include <map>
#include <vector>

namespace duplicate {

  class match {
  };

  class bucket {
    std::map<std::string, std::vector<match> > contents;
  public:
    void add(std::string key, match m) {

      if (contents.find(key) == contents.end()) {
	std::vector<match> a;
	contents[key] = a;
      }
      contents[key].push_back(m);
    }

    std::vector<match>& operator[](const std::string& key) {
      return contents[key];
    }

    bool is_empty() {
      return contents.size() == 0;
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

BOOST_AUTO_TEST_CASE(adding_match_to_bucket_already_containing_a_match) {
  duplicate::bucket bucket;
  duplicate::match m;
  bucket.add("key", m);
  bucket.add("key", m);

  BOOST_CHECK(!bucket.is_empty());

  BOOST_CHECK(bucket["key"].size() == 2);
}
