#include "base64_tests.h"

#include <cstring>

TEST(base64_Tests, base64_encode_decode_positive) {
  std::string asci = "0PebAbG/uVXwKSzvmlH80cWWbrWD0JM5oK+S6xOA/8k=";
  std::string decoded = base64::base64_decode(asci);
  std::string asci_encoded =
      base64::base64_encode((unsigned char*)decoded.c_str(), sizeof(decoded));
  EXPECT_EQ(asci, asci_encoded);

}

/*
TEST(base64_Tests, base64_encode_decode_negative){

}
*/
