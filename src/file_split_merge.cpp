#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <set>

#include "file_split_merge.h"
#include "file.h"
#include "customexceptions.h"

void fileSplitMerge::split(size_t splitNumber,std::string& inputfilePath, std::string& outputPath ) {
  namespace fs = std::filesystem;
  secure_string file_to_string = pathStringHandler::filePathToString(inputfilePath);
  size_t buffer_size = file_to_string.length() / splitNumber;
  std::ifstream ifs(inputfilePath, std::ios::in | std::ios::binary);

  char buf[buffer_size];
  size_t file_number = 0;

  while (ifs.read(buf, sizeof(buf)) || ifs.gcount()) {
    ++file_number;
    // use what was read in.

    // gcount() is the number of bytes actually read
    std::string chunk(buf, ifs.gcount());
    std::string split_component=outputPath+std::to_string(file_number);
    {
      //Create scope with {} to use RAII of std::ofstream to close file
      std::ofstream(split_component)<< chunk << '\n';
    }
    fs::copy(fs::path(split_component),fs::path(outputPath),fs::copy_options::overwrite_existing);
    std::filesystem::remove(split_component);

  }
}

void fileSplitMerge::merge(std::string& filesPath,
                           std::string& outPutFilePath) {
  namespace fs = std::filesystem;
  std::set<fs::path> files_to_merge;

  fs::path encrypted_files_path = fs::path(filesPath);
  for (const auto& file : fs::directory_iterator{encrypted_files_path}) {
    files_to_merge.insert((fs::path)file);
  }
  std::ofstream ofile(outPutFilePath, std::ios::out | std::ios::binary|std::ios::app);
  std::string str;
  ofile.unsetf(std::ios_base::skipws);
  for (auto& file : files_to_merge) {
    std::ifstream ifile(file, std::ios::in | std::ios::binary);
    //if (!ifile.is_open()||!ofile.is_open())
    //{
      //throw invalid_file("File opening error: ");
      //break;
    //}
    std::getline (ifile,str);
    ofile<<str;
    std::filesystem::remove(std::string(file));
  }

}
