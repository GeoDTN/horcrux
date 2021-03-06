#include <string>

#include "enc_dec_tests.h"

void encryptDecrypt_Tests::SetUp() { encrypt_decrypt = new encryptDecrypt(); }

void encryptDecrypt_Tests::TearDown() { delete encrypt_decrypt; }
bool encryptDecrypt_Tests::isValid() {
  secure_string ptext = "Now is the time for all for the community of the world to cooperate for better futures. Air pollution, diseases, lack of eduction, health care and some other basic needs in some parts of the world need to be solved. The world will be stable only when all parts of it are stable";
  secure_string ctext, rtext;
  byte iv[]  =
      {   0x00, 0x01, 0x02, 0x03,
       0x04, 0x05, 0x06, 0x07,
       0x08, 0x09, 0x0a, 0x0b,
       0x0c, 0x0d, 0x0e, 0x0f };
  byte key[KEY_SIZE];
  encrypt_decrypt->gen_params(key);
  std::string plain_input_path = "original.txt";
  std::string encrypted_output_path = "encrypted.txt";
  std::string decrypted_output_path = "decrypted.txt";
  encrypt_decrypt->aes_encrypt(key, iv, ctext, 3, plain_input_path,
                               encrypted_output_path);

  encrypt_decrypt->aes_decrypt(key, iv, rtext, encrypted_output_path,
                               decrypted_output_path);
  OPENSSL_cleanse(key, KEY_SIZE);
  OPENSSL_cleanse(iv, BLOCK_SIZE);

  return (ptext == rtext) ? true : false;
}
TEST_F(encryptDecrypt_Tests, Test_aes_encrypt_decrypt_positive) {
  EXPECT_EQ(true, isValid());
}

/*
TEST(encryptDecrypt_Tests, Test_aes_encrypt_decrypt_negative) {
{

}
*/
