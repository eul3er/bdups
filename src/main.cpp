#include <iostream>
#include "cfileselector.h"
#include "cduplicatefinder.h"
#include "cconcurrencyhandler.h"
#include "corganizer.h"
#include "cfilter.h"
#include "cselect.h"
#include <boost/lexical_cast.hpp>
#include <fstream>

/* Description:
 * Find Duplicate Files considering file size and further a MD5 Hash of the file content
 *
 * Basic Algorithm:
 * get filenames +paths + filesize from disk
 * sort according to filesize
 * hash only the duplicate ranges
 * move hashed files to front
 * sort hashed files subrange
 * find duplicates
 * print grouped duplicates
 *
 * Options:
 * 1. With two arguments (core count, path):
 *  Look at the given path and execute the basic algorithm
 *
 * 2. With three arguments (core count, path1, path2)
 *  Look at path1 for the given files in path2 and execute basic algorithm
 *
 */


int main(int argc, char** argv)
{
    std::string folder;
    unsigned int cores = 0;

    if(argc == 3){
        //option 1
        cores = boost::lexical_cast<unsigned int> (argv[1]);
        folder = boost::lexical_cast<std::string>(argv[2]);

        CFilter<CSelectWithoutMatching> plain_filter(folder);

        COrganizer<
                CFilter<CSelectWithoutMatching>,
                CConcurrencyHandler,
                std::unique_ptr<std::vector<CFileEntry>>
                > organizer(std::move(plain_filter), cores);

        organizer.start();
        organizer.printResults();
    }
    else if(argc == 4){

        //Option 2
        cores = boost::lexical_cast<unsigned int> (argv[1]);
        folder = boost::lexical_cast<std::string> (argv[2]);
        std::string folder_to_match;
        folder_to_match = boost::lexical_cast<std::string> (argv[3]);

        //load file infos from path2
        CFileSelector matching_selector;
        matching_selector.process_directory(folder_to_match);


        CSelectWithMatching matched(matching_selector.results());

        //Filter out unwanted data
        CFilter<CSelectWithMatching> matching_filter(folder, std::move(matched));

        COrganizer<CFilter<CSelectWithMatching>,
                   CConcurrencyHandler,
                   std::unique_ptr<std::vector<CFileEntry>>
                  > organizer(std::move(matching_filter), cores);

        organizer.start();
        organizer.printResults();
    }
    else
    {
        std::cerr << "wrong usage\n";
        return -1;
    }


    return 0;
}

