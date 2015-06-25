#ifndef CSELECT_H
#define CSELECT_H

#include <vector>
#include "cfileentry.h"
#include <memory>

class CFileEntry;

class CSelectWithMatching
{
public:
    CSelectWithMatching(std::unique_ptr<std::vector<CFileEntry>> match) : m_matching(std::move(match)){}

    std::unique_ptr<std::vector<CFileEntry>>
    select_in(std::unique_ptr<std::vector<CFileEntry>> data);

    std::unique_ptr<std::vector<CFileEntry>>
    select_out(std::unique_ptr<std::vector<CFileEntry>> data);

private:
    std::unique_ptr<std::vector<CFileEntry>> m_matching;
};


class CSelectWithoutMatching
{
public:
    std::unique_ptr<std::vector<CFileEntry>>
    select_in(std::unique_ptr<std::vector<CFileEntry>> data);

    std::unique_ptr<std::vector<CFileEntry>>
    select_out(std::unique_ptr<std::vector<CFileEntry>> data);
};

#endif // CSELECT_H
