#include "file.h"

secure_string pathStringHandler::filePathToString(std::string &filePath)
{
  std::ifstream t(filePath.c_str());
  secure_string  str;
  t.seekg(0, std::ios::end);
  str.reserve(t.tellg());
  t.seekg(0, std::ios::beg);
  str.assign((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());

  return str;
}

void pathStringHandler::stringToFile(
    secure_string& fileContent,
    std::string& filePath) {  // Better passing non primitive types by reference than by value
  std::ofstream file(filePath);
  file << fileContent<<std::endl;
}

