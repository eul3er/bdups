#include "cselect.h"
#include <algorithm>



std::unique_ptr<std::vector<CFileEntry>>
CSelectWithMatching::select_in(std::unique_ptr<std::vector<CFileEntry>> data){

    //select only candidate files which are of equal file size like those
    //files in the matching vector
    std::unique_ptr<std::vector<CFileEntry>> input_selection(new std::vector<CFileEntry>);
    input_selection->reserve(m_matching->size());

    std::for_each(m_matching->begin(),
                  m_matching->end(),
                  [&data, &input_selection](const CFileEntry& elem){

        auto range = std::equal_range(data->begin(),
                                      data->end(),
                                      elem,
                                      [](const CFileEntry& lhs, const CFileEntry& rhs){
            return lhs.m_filesize < rhs.m_filesize;
        });

        if(range.first != data->end()){
            std::copy(range.first,
                      range.second,
                      std::back_inserter(*input_selection));
        }

    });

    std::copy(m_matching->begin(),
              m_matching->end(),
              std::back_inserter(*input_selection));

    std::sort(input_selection->begin(),
              input_selection->end(),
              [](const CFileEntry& lhs, const CFileEntry& rhs){
        return lhs.m_filesize < rhs.m_filesize;
    });

    return std::move(input_selection);
}

std::unique_ptr<std::vector<CFileEntry>>
CSelectWithMatching::select_out(std::unique_ptr<std::vector<CFileEntry>> data){

    //select only those files which hash equal on of those in the matching vector
    std::unique_ptr<std::vector<CFileEntry>> merged_endresult(new std::vector<CFileEntry>);

    std::for_each(m_matching->begin(),
                  m_matching->end(),
                  [&data, &merged_endresult](CFileEntry& elem){

        elem.createHash();

        auto range = std::equal_range(data->begin(),
                                      data->end(),
                                      elem);

        if(range.first != data->end()){
            std::copy(range.first,
                      range.second,
                      std::back_inserter(*merged_endresult));
        }

    });

    return std::move(merged_endresult);
}

std::unique_ptr<std::vector<CFileEntry>>
CSelectWithoutMatching::select_in(std::unique_ptr<std::vector<CFileEntry>> data){
    return std::move(data);
}

std::unique_ptr<std::vector<CFileEntry>>
CSelectWithoutMatching::select_out(std::unique_ptr<std::vector<CFileEntry>> data){
    return std::move(data);
}
