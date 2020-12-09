#ifndef FILE_SPLIT_MERGE_H
#define FILE_SPLIT_MERGE_H

#include <string>

class fileSplitMerge {
 public:

  static void split(size_t splitNumber,std::string& inputPath, std::string& outPutPath );
  static void merge(std::string& filesPath,std::string& outPutFilePath);
 private:

  fileSplitMerge(fileSplitMerge const&) = delete;
  fileSplitMerge(fileSplitMerge&&) = delete;
  fileSplitMerge& operator=(fileSplitMerge const&) = delete;
  fileSplitMerge& operator=(fileSplitMerge&&) = delete;

};

#endif //FILE_SPLIT_MERGE_H

