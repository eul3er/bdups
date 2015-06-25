#include "cloadbalancer.h"
#include "cfileentry.h"
#include <iostream>

CLoadBalancer::CLoadBalancer()
{}

CLoadBalancer::~CLoadBalancer()
{}


std::pair<Itr,Itr> CLoadBalancer::createRange(std::vector<CFileEntry>& input_container,
                                              unsigned int package_size,
                                              std::vector<std::pair<Itr, Itr>>& ranges){

    if(ranges.empty()){
        //check if we have to increase package size
        //expand the border if necessary
        auto size = balance(input_container, package_size);

        if(size == 0){
            std::cerr << "No items to create a valid range\n";
        }
        else{
            package_size += size;
        }

        //create the first range
        auto range_end_itr = std::next(input_container.begin(), package_size);
        auto r = std::make_pair(input_container.begin(), range_end_itr);
        ranges.emplace_back(r);
        return r;
    }
    else{
        //get the end of the last collected range
        auto itr_begin = ranges[ranges.size() -1].second;

        //check if we have to increase package size
        //expand the border if necessary
        auto size = balance(itr_begin, input_container.end(), package_size);

        auto range_end_itr = std::next(itr_begin, package_size + size);
        auto range = std::make_pair(itr_begin, range_end_itr);
        ranges.emplace_back(range);
        return range;
    }
}

//convenience function
unsigned int CLoadBalancer::balance(std::vector<CFileEntry>& input_container, unsigned int package_size){
    return balance(input_container.begin(), input_container.end(), package_size);
}

unsigned int CLoadBalancer::balance(Itr first, Itr last, unsigned int package_size){
    //create the end of package-range
    //look at the end of the border and beyond the border
    //look for equal filesizes at end and beyond the border
    //expand the border if necessary for items equaling filesize of the border item
    auto border_itr = std::next(first, package_size);
    auto past_border_itr = std::next(border_itr,1);

    //Check: Are we at the end of the input vector
    if(std::distance(first, last) <= package_size){
        //TODO check calc
        return std::distance(first, last)  - package_size;
    }

    while(border_itr->m_filesize == past_border_itr->m_filesize){
        std::advance(past_border_itr, 1);
        if(past_border_itr == last){
            break;
        }
    }
    return std::distance(border_itr, past_border_itr);
}
