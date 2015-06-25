#include "cconcurrencyhandler.h"

#include <iostream>
#include <iterator>
#include "duplicatealgos.h"
#include "cloadbalancer.h"
#include "cfileentry.h"

CConcurrencyHandler::CConcurrencyHandler(std::unique_ptr<std::vector<CFileEntry>> search_folder, unsigned int cores) :
   m_vec(std::move(search_folder)),
   m_cores(cores)
{
    if(cores == 0){
        m_cores = std::thread::hardware_concurrency();
    }    
}


CConcurrencyHandler::~CConcurrencyHandler()
{}

void CConcurrencyHandler::partition(){
    //partionen files among threads
    unsigned files_per_thread = m_vec->size() / m_cores;

    for (unsigned i(0); i != m_cores; ++i) {

        CLoadBalancer balancer;
        auto range = balancer.createRange(*m_vec, files_per_thread, m_ranges);

        //Prepare a work_package without data sharing between threads
        std::vector<CFileEntry> work_package;
        work_package.reserve(std::distance(range.first, range.second));

        std::copy(range.first,
                  range.second,
                  std::back_inserter(work_package));

        auto lambda = [](std::vector<CFileEntry>&& vec)
        {
            CDuplicateFinder finder(std::move(vec));
            finder.doWork();
            return finder.results();
        };

        std::packaged_task<std::vector<CFileEntry>(std::vector<CFileEntry>&&)> job(lambda);

        m_futures.emplace_back(std::move(job.get_future()));
        std::thread thread(std::move(job), std::move(work_package));
        thread.detach();
        m_threads.push_back(std::move(thread));
    }
}

std::unique_ptr<std::vector<CFileEntry>> CConcurrencyHandler::results(){

    std::unique_ptr<std::vector<CFileEntry>> end_result(new std::vector<CFileEntry>);

    for(auto & element : m_futures){
        element.wait();
        //get the Future
        auto result_vec = element.get();
        end_result->reserve(result_vec.size());
        std::move(result_vec.begin(), result_vec.end(), std::back_inserter(*end_result));
    }

    return std::move(end_result);
}
