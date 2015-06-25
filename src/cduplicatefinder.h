#ifndef CDUPLICATEFINDER_H
#define CDUPLICATEFINDER_H
#include <vector>
#include "cfileentry.h"

class CDuplicateFinder
{
public:
    CDuplicateFinder(std::vector<CFileEntry>&& dups);
    ~CDuplicateFinder();

    void doWork();

    std::vector<CFileEntry>&& results();


private:
    void sortFilesize();
    void sortHashes(std::vector<CFileEntry>::iterator itr_hashed_end);
    void findDuplicatesFileSize(std::vector<CFileEntry>::iterator itr);
    std::vector<CFileEntry>::iterator partitionHash();
    void findHashDuplicates(std::vector<CFileEntry>::iterator itr_hashed_end);
    void print(std::vector<CFileEntry>::iterator itr_end);

private:
    std::vector<CFileEntry> m_duplicates;
    std::vector<CFileEntry> m_results;
};

#endif // CDUPLICATEFINDER_H
