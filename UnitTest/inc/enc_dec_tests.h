#ifndef ENC_DEC_TESTS_H_
#define ENC_DEC_TESTS_H_

#include <gtest/gtest.h>

#include "enc_dec.h"
#include "customexceptions.h"



class encryptDecrypt_Tests : public ::testing::Test, public encryptDecrypt {
 public:
  bool isValid();
 protected:
  virtual void SetUp() override;
  virtual void TearDown() override;

 private:
  encryptDecrypt* encrypt_decrypt;
};

#endif
