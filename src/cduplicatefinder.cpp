#include "cduplicatefinder.h"
#include <iostream>
#include "duplicatealgos.h"

CDuplicateFinder::CDuplicateFinder(std::vector<CFileEntry>&& dups) : m_duplicates(std::move(dups))
{}

CDuplicateFinder::~CDuplicateFinder()
{}


void CDuplicateFinder::doWork(){

    if(!std::is_sorted(m_duplicates.begin(), m_duplicates.end(),
                      [](const CFileEntry& lhs, const CFileEntry& rhs){
                      return lhs.m_filesize < rhs.m_filesize;})){

        sortFilesize();
    }

    findDuplicatesFileSize(m_duplicates.begin());

    std::vector<CFileEntry>::iterator itr_hashed_end = partitionHash();

    sortHashes(itr_hashed_end);

    findHashDuplicates(itr_hashed_end);
}

void CDuplicateFinder::sortFilesize(){
    std::sort(m_duplicates.begin(), m_duplicates.end(),
              [](const auto& lhs, const auto& rhs){
       return lhs.m_filesize < rhs.m_filesize;
    });
}

void CDuplicateFinder::findDuplicatesFileSize(std::vector<CFileEntry>::iterator itr){

    auto itr_end = m_duplicates.end();
    auto itr_dup = std::adjacent_find(itr,
                                      itr_end,
                                      [](const auto& lhs, const auto& rhs) {
          return lhs.m_filesize == rhs.m_filesize;
        });

    if (itr_dup != itr_end) {

      //Found a potential duplicate range

      auto itr_base = itr_dup;

      //Potential duplicates get prepared for a deep comparision
      while (itr_dup != itr_end && itr_base->m_filesize == itr_dup->m_filesize) {
        itr_dup->createHash();
        ++itr_dup;
      }

      //check for more dups
      if (itr_dup != itr_end) {
        findDuplicatesFileSize(itr_dup);
      }
    }
}

std::vector<CFileEntry>::iterator CDuplicateFinder::partitionHash(){
    //create a range of hot duplicate candidates
    return std::stable_partition(m_duplicates.begin(),
                          m_duplicates.end(),
                          [](const auto& element){
                          return !element.m_hash.empty();});
}

void CDuplicateFinder::sortHashes(std::vector<CFileEntry>::iterator itr_hashed_end){
    //sorting the hot duplicate candidates
    std::sort(m_duplicates.begin(),
              itr_hashed_end,
              [](const auto& lhs, const auto& rhs){
        return lhs.m_hash < rhs.m_hash;
    });
}

void CDuplicateFinder::findHashDuplicates(std::vector<CFileEntry>::iterator itr_hashed_end){

    std::pair<std::vector<CFileEntry>::iterator, std::vector<CFileEntry>::iterator> range;

    //defined in duplicatealgos.h
    range = duplicateRange(m_duplicates.begin(),
                           itr_hashed_end);

    //check for a valid range
    //don't invalidate the iterators => copy elements
    while(range.first != itr_hashed_end){

        std::copy(range.first,
                  range.second,
                  std::back_inserter(m_results));

        range = duplicateRange(range.second,
                               itr_hashed_end);
    }
}

std::vector<CFileEntry>&& CDuplicateFinder::results(){
    return std::move(m_results);
}
