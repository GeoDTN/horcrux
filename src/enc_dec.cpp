#include <cstring>

#include "file_split_merge.h"
#include "enc_dec.h"
#include "customexceptions.h"

void encryptDecrypt::gen_params(byte key[KEY_SIZE]) {
  int rc = RAND_bytes(key, KEY_SIZE);
  if (rc != 1) throw random_generation_error("RAND_bytes key failed");

}

void encryptDecrypt::aes_encrypt(
    const byte key[KEY_SIZE], const byte iv[BLOCK_SIZE],
    secure_string& ctext, size_t horcrux_count,
    std::string& inputPath, std::string& outPutPath) {
    std::string encrypted_file = "encrypted.txt";
    const secure_string ptext = pathStringHandler::filePathToString(inputPath);
    std::cout << "Plain  text from file is :" << ptext << std::endl;
    EVP_CIPHER_CTX_free_ptr ctx(EVP_CIPHER_CTX_new(), ::EVP_CIPHER_CTX_free);
    int rc = EVP_EncryptInit_ex(ctx.get(), EVP_aes_256_cbc(), NULL, key, iv);
    if (rc != 1) throw encryption_error("EVP_EncryptInit_ex failed");

       // Recovered text expands upto BLOCK_SIZE
    ctext.resize(ptext.size() + BLOCK_SIZE);
    int out_len1 = (int)ctext.size();

     rc = EVP_EncryptUpdate(ctx.get(), (byte*)&ctext[0], &out_len1,
                         (const byte*)&ptext[0], (int)ptext.size());
     if (rc != 1) throw encryption_error("EVP_EncryptUpdate failed");

     int out_len2 = (int)ctext.size() - out_len1;
     rc = EVP_EncryptFinal_ex(ctx.get(), (byte*)&ctext[0] + out_len1, &out_len2);
     if (rc != 1) throw encryption_error("EVP_EncryptFinal_ex failed");

  // Set cipher text size now that we know it

    ctext.resize(out_len1 + out_len2);
    std::ofstream(encrypted_file) << ctext << '\n';
    fileSplitMerge::split(horcrux_count, encrypted_file, outPutPath);
    std::remove(encrypted_file.c_str());
    std::filesystem::remove(inputPath);

}

void encryptDecrypt::aes_decrypt(
    const byte key[KEY_SIZE], const byte iv[BLOCK_SIZE],
     secure_string& rtext,
     std::string& inputFilesPath, std::string& outputFilePath) {
     fileSplitMerge::merge(inputFilesPath, outputFilePath);
     const secure_string& ctext =
     pathStringHandler::filePathToString(outputFilePath);
      std::cout <<"Cipher text from file is :"<<ctext<<std::endl;

      EVP_CIPHER_CTX_free_ptr ctx(EVP_CIPHER_CTX_new(), ::EVP_CIPHER_CTX_free);
      int rc = EVP_DecryptInit_ex(ctx.get(), EVP_aes_256_cbc(), NULL, key, iv);
      if (rc != 1) throw decryption_error("EVP_DecryptInit_ex failed");

       // Recovered text contracts upto BLOCK_SIZE
       rtext.resize(ctext.size());
       int out_len1 = (int)rtext.size();

       rc = EVP_DecryptUpdate(ctx.get(), (byte*)&rtext[0], &out_len1,
                         (const byte*)&ctext[0], (int)ctext.size());
        if (rc != 1) throw decryption_error("EVP_DecryptUpdate failed");

        int out_len2 = (int)rtext.size() - out_len1;
        std::cout <<"Retrived text from file is :"<<rtext<<std::endl;
        rc = EVP_DecryptFinal_ex(ctx.get(), (byte*)&rtext[0] + out_len1, &out_len2);
        if (rc != 1) throw decryption_error("EVP_DecryptFinal_ex failed");

         // Set recovered text size now that we know it
        rtext.resize(out_len1 + out_len2);
       std::ofstream(outputFilePath) <<rtext << '\n';

}

