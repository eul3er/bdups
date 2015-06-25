#ifndef CCONCURRENCYHANDLER_H
#define CCONCURRENCYHANDLER_H
#include <vector>
#include "cfileentry.h"
#include <thread>
#include <future>
#include "cduplicatefinder.h"




class CConcurrencyHandler
{
public:
    CConcurrencyHandler(std::unique_ptr<std::vector<CFileEntry>> search_folder, unsigned int cores = 0);

    ~CConcurrencyHandler();

    void partition();

    std::unique_ptr<std::vector<CFileEntry>> results();



private:
    std::unique_ptr<std::vector<CFileEntry>> m_vec;
    std::vector<CDuplicateFinder> m_workers;
    std::vector<std::thread> m_threads;
    std::vector<std::future<std::vector<CFileEntry>>> m_futures;   
    std::vector<std::pair<std::vector<CFileEntry>::iterator,
    std::vector<CFileEntry>::iterator>> m_ranges;
    unsigned int m_cores;
};

#endif // CCONCURRENCYHANDLER_H
