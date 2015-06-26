#ifndef CORGANIZER_H
#define CORGANIZER_H

#include <memory>
#include "cfileentry.h"
#include <boost/filesystem.hpp>
#include <iostream>
#include <utility>

/*
 * Input -> Input preprocessing ->
 * general processing ->
 * Output postprocessing -> print output *
 */

template<typename Filter, typename Worker, typename ResultType>
class COrganizer
{
public:
    COrganizer(Filter&& in_filter, unsigned int cores) :
        m_filter(std::move(in_filter)), m_cores(cores){}


    void start(){
        Worker worker(std::move(m_filter.filterInput()), m_cores);
        worker.partition();
        m_result = std::move(m_filter.filterOutput(std::move(worker.results())));
    }

    void printResults(){
        auto prev = m_result->begin();
        for(auto itr = m_result->begin(); itr != m_result->end(); ++itr){

            if(itr->m_hash != prev->m_hash){
                std::cout << "\n";
            }
            prev = itr;
            std::cout<< itr->m_path.native() << "\n";
        }
    }


private:
    Filter m_filter;
    ResultType m_result;
    unsigned int m_cores;
};

#endif // CORGANIZER_H
