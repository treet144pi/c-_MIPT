#include <iostream>
#include "perfect_cache.hpp"

int main()
{
    size_t sz_cache,n;
    std::cin>>sz_cache>>n;
    int * page_arr = new int [n];

    perfect_cache<int> ideal_cache(sz_cache);
    int id_page;

    for (int i=0; i<n;i++)
    {
        std::cin>>id_page;
        page_arr[i] = id_page;
    }

    std::cout<<ideal_cache.count_hits(page_arr,n)<<std::endl;




    return 0;
}
