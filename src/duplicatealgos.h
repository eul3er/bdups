#ifndef DUPLICATEALGOS_H
#define DUPLICATEALGOS_H
#include <algorithm>
#include <iterator>
#include <iostream>


template <typename ForwardItr>
std::pair<ForwardItr, ForwardItr> duplicateRange(ForwardItr first, ForwardItr last){

    auto range = std::equal_range(first, last, *first);
    auto itr = first;

    int range_distance = std::distance(range.first, range.second);
    if(range.first != last && range_distance > 1){
        return range;
    }

    while(range.first != last && range_distance == 1){
        std::advance(itr, 1);
        range = std::equal_range(itr, last, *itr);
        range_distance = std::distance(range.first, range.second);
    }
    return range;
}

#endif // DUPLICATEALGOS_H
