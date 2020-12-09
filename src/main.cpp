#include <iostream>
#include <cstring>

#include "enc_dec.h"
#include "base64.h"
#include "customexceptions.h"

int main(int argc, char* argv[]) {
  if (argc < 5) {
    std::cerr << "Inavlid command line arguments. Please use correct arguments"
              << std::endl;
    exit(EXIT_FAILURE);
  }

  // Load the necessary cipher
  EVP_add_cipher(EVP_aes_256_cbc());
  encryptDecrypt encrpt_decrypt;
  secure_string ctext, rtext;

  byte key[KEY_SIZE], iv[BLOCK_SIZE];
  encrpt_decrypt.gen_params(key, iv);
  std::string encrpt_decrypt_argument1 = std::string(argv[1]);
  std::string encrpt_decrypt_argument2 = std::string(argv[2]);
  std::string input_path = std::string(argv[4]);
  std::string output_path = std::string(argv[5]);

  try {
    if (encrpt_decrypt_argument1.compare("create") == 0 &&
        encrpt_decrypt_argument2.compare("-n") == 0) {
      size_t horcrux_count = static_cast<size_t>(std::stoi(argv[3]));
      encrpt_decrypt.aes_encrypt(key, iv, ctext, horcrux_count, input_path,
                                 output_path);
      std::cout << "encrytion key  before encoding is :  " << key << std::endl;
      std::cout << "encrytion key is: " <<base64::base64_encode(key,sizeof (key))<< std::endl;
    } else if (encrpt_decrypt_argument1.compare("load") == 0 &&
               encrpt_decrypt_argument2.compare("-k") == 0) {
      std::string decryptionKey=base64::base64_decode(std::string(argv[3]));
      std::cout << "The decrytion key is :" <<base64::base64_encode((unsigned char*)decryptionKey.c_str (),sizeof (decryptionKey))<< std::endl;
      encrpt_decrypt.aes_decrypt((unsigned char*)decryptionKey.c_str (),iv, rtext, input_path, output_path);
    } else {
      std::cout<<"Inavlid command line arguments. Please use correct arguments"<<'\n';
      exit(EXIT_FAILURE);
    }

  }  catch (const invalid_file& e) {
    std::cout<<e.what ()<<std::endl;
  }catch (const random_generation_error& e) {
    std::cout<<e.what ()<<std::endl;
  }catch (const encryption_error& e) {
    std::cout<<e.what ()<<std::endl;
  }catch (const decryption_error& e) {
    std::cout<<e.what ()<<std::endl;
  }catch (const base64_encode_error& e) {
    std::cout<<e.what ()<<std::endl;
  }
  catch (const base64_decode_error& e) {
    std::cout<<e.what ()<<std::endl;
  }
  catch (const std::exception& e) {
    std::cout<<"Unexpected exception:"<<e.what ()<<"thrown"<<std::endl;
  }

  OPENSSL_cleanse(key, KEY_SIZE);
  OPENSSL_cleanse(iv, BLOCK_SIZE);

  return 0;
}

