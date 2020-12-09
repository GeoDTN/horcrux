#ifndef FILE_H_
#define FILE_H_

#include <fstream>
#include <streambuf>
#include <filesystem>
#include <iostream>
#include <memory>
#include <limits>
#include <stdexcept>
#include <openssl/evp.h>
#include <openssl/rand.h>


static const unsigned int KEY_SIZE = 32;
static const unsigned int BLOCK_SIZE = 16;

template <typename T>
struct zallocator {
 public:
  typedef T value_type;
  typedef value_type* pointer;
  typedef const value_type* const_pointer;
  typedef value_type& reference;
  typedef const value_type& const_reference;
  typedef std::size_t size_type;
  typedef std::ptrdiff_t difference_type;

  pointer address(reference v) const { return &v; }
  const_pointer address(const_reference v) const { return &v; }

  pointer allocate(size_type n, const void* hint = 0) {
    if (n > std::numeric_limits<size_type>::max() / sizeof(T))
      throw std::bad_alloc();
    return static_cast<pointer>(::operator new(n * sizeof(value_type)));
  }

  void deallocate(pointer p, size_type n) {
    OPENSSL_cleanse(p, n * sizeof(T));
    ::operator delete(p);
  }

  size_type max_size() const {
    return std::numeric_limits<size_type>::max() / sizeof(T);
  }

  template <typename U>
  struct rebind {
    typedef zallocator<U> other;
  };

  void construct(pointer ptr, const T& val) {
    new (static_cast<T*>(ptr)) T(val);
  }

  void destroy(pointer ptr) { static_cast<T*>(ptr)->~T(); }

#if __cpluplus >= 201103L
  template <typename U, typename... Args>
  void construct(U* ptr, Args&&... args) {
    ::new (static_cast<void*>(ptr)) U(std::forward<Args>(args)...);
  }

  template <typename U>
  void destroy(U* ptr) {
    ptr->~U();
  }
#endif
};

typedef unsigned char byte;
typedef std::basic_string<char, std::char_traits<char>, zallocator<char> >
    secure_string;
using EVP_CIPHER_CTX_free_ptr =
    std::unique_ptr<EVP_CIPHER_CTX, decltype(&::EVP_CIPHER_CTX_free)>;

class pathStringHandler {
 public:
  pathStringHandler() = default;

  static void stringToFile( secure_string& fileContent,  std::string& filePath);
  static secure_string filePathToString( std::string& filePath);
 private:
  pathStringHandler(pathStringHandler const&) = delete;
  pathStringHandler(pathStringHandler&&) = delete;
  pathStringHandler& operator=(pathStringHandler const&) = delete;
  pathStringHandler& operator=(pathStringHandler&&) = delete;

};

#endif // FILE_H_
