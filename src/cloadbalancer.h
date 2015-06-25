#ifndef CLOADBALANCER_H
#define CLOADBALANCER_H

#include <vector>
class CFileEntry;

typedef std::vector<CFileEntry>::iterator Itr;

class CLoadBalancer
{
public:
    CLoadBalancer();

    ~CLoadBalancer();

    std::pair<Itr,Itr> createRange(std::vector<CFileEntry>& input_container,
                                   unsigned int package_size,
                                   std::vector<std::pair<Itr, Itr>>& ranges);


    unsigned int balance(std::vector<CFileEntry>& input_container, unsigned int package_size);

    unsigned int balance(Itr fist, Itr last, unsigned int package_size);    
};

#endif // CLOADBALANCER_H
