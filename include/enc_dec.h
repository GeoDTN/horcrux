#ifndef ENC_DEC_H_
#define ENC_DEC_H_

#include "file.h"

class encryptDecrypt {
 public:
  void gen_params(byte key[KEY_SIZE], byte iv[BLOCK_SIZE]);
  void aes_encrypt(const byte key[KEY_SIZE], const byte iv[BLOCK_SIZE],
                   secure_string& ctext,
                   size_t horcrux_count, std::string& inputPath, std::string & outPutPath);
  void aes_decrypt(const byte key[KEY_SIZE], const byte iv[BLOCK_SIZE],
                    secure_string& rtext,
                   std::string& inputFilesPath, std::string & outputFilePath);
};

#endif



