#ifndef CFILEENTRY_H
#define CFILEENTRY_H
#include <string>
#include <cstdint>
#include <boost/filesystem/path.hpp>

class CFileEntry
{
public:
    CFileEntry(const boost::filesystem::path& path, uintmax_t fsize);
    ~CFileEntry();

    CFileEntry(const CFileEntry&) = default;
    CFileEntry(CFileEntry&&) = default;

    CFileEntry& operator=(const CFileEntry&) = default;
    CFileEntry& operator=(CFileEntry&&) = default;

    void createHash();

    boost::filesystem::path m_path;

    uintmax_t m_filesize;
    std::string m_hash;
};

bool operator==(const CFileEntry& lhs, const CFileEntry& rhs);
bool operator<(const CFileEntry& lhs, const CFileEntry& rhs);

#endif // CFILEENTRY_H
