#ifndef CFILTER_H
#define CFILTER_H

#include <string>
#include <vector>
#include <memory>
#include "cfileselector.h"

/*
 * Filter Input + Output by calling a Selector object
 */

template <typename SELECTOR>
class CFilter
{
public:
    CFilter(const std::string& path) :m_path(path){}

    CFilter(const std::string& path, SELECTOR&& selector):
        m_selector(std::move(selector)), m_path(path){}


    std::unique_ptr<std::vector<CFileEntry>>
    filterInput(){
        CFileSelector sel;
        sel.process_directory(m_path);
        return std::move(m_selector.select_in(sel.results()));}


    std::unique_ptr<std::vector<CFileEntry>>
    filterOutput(std::unique_ptr<std::vector<CFileEntry>> data){
        return std::move(m_selector.select_out(std::move(data)));}


private:
    SELECTOR m_selector;
    std::string m_path;
};

#endif // CFILTER_H
