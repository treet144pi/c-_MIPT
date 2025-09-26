#include <unordered_map>
#include <deque>
#include <set>

template <typename T>
struct perfect_cache{
    size_t hits;
    size_t cache_size;
    perfect_cache(size_t sz): cache_size(sz),hits(0) { };

    std::set<std::pair<size_t,T>> eviction_order;
    std::unordered_map<T, std::deque<size_t>> positions_future;
    std::unordered_map <T , typename std::set<std::pair<size_t,T>>::iterator> cache;

    size_t count_hits(T const * data,size_t len)
    {
        if (data == nullptr || len ==0)
            return 0;

        hits = 0;
        eviction_order.clear();
        positions_future.clear();
        cache.clear();

        if (!cache_size)
            return 0;
        for (size_t i =0; i <len;i++ )
            positions_future[data[i]].push_back(i);

        for (size_t i=0;i<len;i++)
        {
            if (!positions_future[data[i]].empty())
                positions_future[data[i]].pop_front();

            size_t next = positions_future[data[i]].empty() ? len :positions_future[data[i]].front();

            auto it_map = cache.find(data[i]);
            if (it_map != cache.end())
            {
                hits++;
                eviction_order.erase(it_map->second);
                cache[data[i]] = (eviction_order.insert({next,data[i]})).first;
                continue;
            }

            if  (eviction_order.size() != cache_size)
                cache[data[i]] = (eviction_order.insert({next,data[i]})).first;
            else
            {
                auto it_set = prev(eviction_order.end());
                T key = it_set->second;

                eviction_order.erase(it_set);
                cache.erase(key);

                cache[data[i]] = (eviction_order.insert({next,data[i]})).first;
            }

        }
        return hits;

    }

};
