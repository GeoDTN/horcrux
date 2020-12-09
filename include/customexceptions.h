#ifndef CUSTOMEXCEPTIONS_H_
#define CUSTOMEXCEPTIONS_H_

#include <stdexcept>


class invalid_file: public std::runtime_error {
 public:
     /*std::string is copy constructible but itself could throw std::bad_alloc.*/
  explicit invalid_file(const std::string& arg) : std::runtime_error{arg} {}
    /*char * is nothrow copy-constructable. This means that the exception itself can be copied without the copy generating an exception.*/
  explicit invalid_file(const char *arg) : std::runtime_error{arg} {}

  virtual ~invalid_file() {}
};

class encryption_error: public std::runtime_error {
 public:
  explicit encryption_error(const std::string& arg) : std::runtime_error{arg} {}
  explicit encryption_error(const char *arg) : std::runtime_error{arg} {}

  virtual ~encryption_error() {}
};

class decryption_error: public std::runtime_error {
 public:
  explicit decryption_error(const std::string& arg) : std::runtime_error{arg} {}
  explicit decryption_error(const char *arg) : std::runtime_error{arg} {}

  virtual ~decryption_error() {}
};

class base64_encode_error: public std::runtime_error {
 public:
  explicit base64_encode_error(const std::string& arg) : std::runtime_error{arg} {}
  explicit base64_encode_error(const char *arg) : std::runtime_error{arg} {}

  virtual ~base64_encode_error() {}
};

class base64_decode_error: public std::runtime_error {
 public:
  explicit base64_decode_error(const std::string& arg) : std::runtime_error{arg} {}
  explicit base64_decode_error(const char *arg) : std::runtime_error{arg} {}

  virtual ~base64_decode_error() {}
};

class random_generation_error: public std::runtime_error {
 public:
  explicit random_generation_error(const std::string& arg) : std::runtime_error{arg} {}
  explicit random_generation_error(const char *arg) : std::runtime_error{arg} {}

  virtual ~random_generation_error() {}
};

#endif /* CUSTOMEXCEPTIONS_H_ */
