#ifndef BASE64_H
#define BASE64_H

#include<iostream>

class base64 {
 public:
  static std::string base64_encode(unsigned char const* bytes_to_encode, unsigned int in_len);
  static std::string base64_decode(std::string const& encoded_string) ;
 private:
  static inline bool is_base64(unsigned char c) {
    return (isalnum(c) || (c == '+') || (c == '/'));
  }

};

#endif /* BASE64_H */

