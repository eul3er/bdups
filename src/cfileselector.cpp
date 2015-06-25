#include "cfileselector.h"
#include <iostream>

CFileSelector::CFileSelector(): m_vector(new std::vector<CFileEntry>) {}

CFileSelector::~CFileSelector() {}

//recursively parse directory tree
void CFileSelector::process_directory(const boost::filesystem::path &path) {
    using namespace boost::filesystem;

  if (!exists(path)) {
      std::cerr << path << " doesn't exist\n";
      return;
  }

  if (!is_directory(path)) {
      std::cerr << path << "is not a directory\n";
      return;
  }

  auto end = directory_iterator();
  auto begin = directory_iterator(path);

  for (auto itr = begin; itr != end; ++itr) {

      if (itr->status().type() == file_type::directory_file) {
          //recursive call
          process_directory(itr->path());
      }
      else if (itr->status().type() == file_type::regular_file) {
          m_vector->emplace_back(itr->path(),
                                 file_size(itr->path()));
      }
      else {
          std::cerr << "unexpected file type at: "<< itr->path() << "\n";
      }
  }
}

void CFileSelector::sort() {
  std::sort(m_vector->begin(), m_vector->end(),
            [](const CFileEntry &lhs, const CFileEntry &rhs) {
              return lhs.m_filesize < rhs.m_filesize;
            });
}

std::unique_ptr<std::vector<CFileEntry>> CFileSelector::results() {
    sort();
    return std::move(m_vector);
}
