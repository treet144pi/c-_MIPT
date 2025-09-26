#include <iostream>
#include "TwoQ_cache.hpp"
//создать когда в пейлд айди в котором есть структура
int main()
{
    size_t sz_cache,n;
    std::cin>>sz_cache>>n;
    TwoQ_cache<int> cache_2q(sz_cache);
    size_t hits = 0;

    int id_page;

    for (int i=0; i<n;i++)
    {
        std::cin>>id_page;
        hits += cache_2q.access(id_page) ? 1: 0;
    }

    std::cout<<hits<<std::endl;


    return 0;
}
