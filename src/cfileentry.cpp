#include "cfileentry.h"
#include <cryptopp/files.h>
#include <cryptopp/md5.h>
#include <cryptopp/hex.h>


CFileEntry::CFileEntry(const boost::filesystem::path& path, uintmax_t fsize) :
    m_path(path), m_filesize(fsize)
{}

CFileEntry::~CFileEntry(){}


void CFileEntry::createHash(){
    using namespace CryptoPP;
    MD5 hash;
    FileSource(m_path.string().c_str(),
               true,
               new HashFilter(hash,
                              new HexEncoder(
                                             new StringSink(this->m_hash)))
               );
}


bool operator==(const CFileEntry& lhs, const CFileEntry& rhs){
    return lhs.m_hash == rhs.m_hash;
}

bool operator<(const CFileEntry& lhs, const CFileEntry& rhs){
    return lhs.m_hash < rhs.m_hash;
}
