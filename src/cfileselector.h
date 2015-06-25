#ifndef CFILESELECTOR_H
#define CFILESELECTOR_H

#include <boost/filesystem.hpp>
#include "cfileentry.h"
#include <iostream>
#include <memory>

class CFileSelector
{
public:
    CFileSelector();

    ~CFileSelector();


    void process_directory(const boost::filesystem::path& path);

    std::unique_ptr<std::vector<CFileEntry>> results();

    void sort();

private:
    std::unique_ptr<std::vector<CFileEntry>> m_vector;
};

#endif // CFILESELECTOR_H
