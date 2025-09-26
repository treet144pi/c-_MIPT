#include <unordered_map>
#include <list>

enum TwoQ{A1, Am};


template <typename T >
struct TwoQ_cache{
    size_t a1_size;
    size_t am_size;

    size_t a1_curr_size;
    size_t am_curr_size;


    std::list<T> a1;
    std::list<T> am;
    std::unordered_map <T , std::pair<TwoQ ,typename std::list<T>::iterator>> hash_table;

    TwoQ_cache (size_t );
    bool access(const T&);
};


template<typename T>
TwoQ_cache<T>::TwoQ_cache (size_t sz): a1_curr_size(0),am_curr_size(0)
{
    if (sz == 1)
    {
        a1_size=1;
        am_size=0;
    }
    else
    {
        a1_size = sz/ 2;
        am_size = sz - a1_size;
    }
}

template<typename T>
bool TwoQ_cache<T>::access(const T& id_page)
{
    auto it_map = hash_table.find(id_page);
    if (it_map == hash_table.end())
    {
        if (a1_curr_size == a1_size)
        {
            T deleted_page = a1.back();
            hash_table.erase(deleted_page);
            a1.pop_back();
        }
        else
            a1_curr_size++;
            a1.push_front(id_page);

            hash_table[id_page] = {A1,a1.begin()};
            return false;
        }


    if (am_size == 0)
        return true;

    if (it_map->second.first == A1)
        {
            if (am_curr_size == am_size )
            {
                T deleted_page = am.back();
                hash_table.erase(deleted_page);
                am.pop_back();
            }
            else
                am_curr_size++;

            a1_curr_size--;

            am.splice(am.begin(),a1,it_map->second.second);
            it_map->second = {Am,am.begin()};
        }
    else
        {
            am.splice(am.begin(),am,it_map->second.second);
            it_map->second.second = am.begin();
        }
    return true;
}
