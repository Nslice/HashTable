#ifndef HASHTABLE_H_INCLUDED
#define HASHTABLE_H_INCLUDED

#include <stdexcept>
#include <algorithm>
#include <utility>
#include <vector>
#include <list>

#include "include/log.h"
#include "include/aliases.h"
#include "include/structures/hashfunc.h"



namespace slice {

using mylogger::log;



struct PrimeNumberHashPolicy
{
    static uint nextSizeOver(uint size);
};




// TODO в 3 параметр можно передавать лямбды через std::function
template<typename K, typename V, typename F = Hash<K>>
class HashTable
{
private:
    const F& getHashCode;
    std::vector<std::list<std::pair<K, V>>*> table;
    // TODO поле убрать
    uint tableSize;
    ulong items;


    HashTable(const HashTable&) = delete;
    HashTable& operator=(const HashTable&) = delete;

public:
    explicit HashTable(uint tableSize = 127, const F& hasher = F());
    ~HashTable();

    const V& put(const K& key, const V& value);
    V& get(const K& key) const;
    void rehash();
};





template<typename K, typename V, typename F>
HashTable<K, V, F>::HashTable(uint tableSize, const F& hasher)
    : getHashCode(hasher), table(tableSize, nullptr)
{
    this->tableSize = tableSize;
    items = 0;
}



template<typename K, typename V, typename F>
HashTable<K, V, F>::~HashTable()
{
    for(auto* ptr : table)
    {
        delete ptr;
    }
}



template<typename K, typename V, typename F>
const V& HashTable<K, V, F>::put(const K& key, const V& value)
{
    // TODO пересмотреть коэффициент
    //    if (items / tableSize >= 2.5)
    //    rehash();

    uint hashIndex = getHashCode(key, tableSize);
    auto* bucket = table[hashIndex];

    if (bucket == nullptr)
    {
        bucket = new std::list<std::pair<K, V>>();
        bucket->emplace_back(key, value);
        table[hashIndex] = bucket;
    }
    else
    {
        auto iterator = std::find_if(bucket->begin(), bucket->end(), [&key](const std::pair<K, V>& pr) {
            return pr.first == key;
        });

        if (iterator != bucket->end())
        {
            iterator->second = value;
            return value;
        }

        bucket->emplace_back(key, value);
    }

    items++;
    return value;
}



template<typename K, typename V, typename F>
V& HashTable<K, V, F>::get(const K& key) const
{
    uint hash = getHashCode(key, tableSize);
    if (table[hash] != nullptr)
    {
        for (std::pair<K,V> pair : *(table[hash]))
        {
            if (pair.first == key)
                return pair.second;
        }
    }
    // TODO надо возвращать итератор
    throw std::invalid_argument("key not exsits");
}



template<typename K, typename V, typename F>
void HashTable<K, V, F>::rehash()
{
    tableSize = PrimeNumberHashPolicy::nextSizeOver(tableSize);
    decltype(table) newTable(tableSize, nullptr);


    std::for_each(table.begin(), table.end(), [&](const std::list<std::pair<K, V>>* list)
    {
        if (list == nullptr) return;
        std::for_each(list->begin(), list->end(), [&](const std::pair<K, V>& pair)
        {
            // TODO этот блок повторяет put(key, value), разбросать как-нибудь по методам
            uint hashIndex = getHashCode(pair.first, tableSize);
            auto* bucket = newTable[hashIndex];

            if (bucket == nullptr)
            {
                bucket = new std::list<std::pair<K, V>>();
                bucket->emplace_back(pair.first, pair.second);
                newTable[hashIndex] = bucket;
            }
            else
            {
                auto iterator = std::find_if(bucket->begin(), bucket->end(), [&pair](const std::pair<K, V>& p) {
                    return p.first == pair.first;
                });

                if (iterator != bucket->end())
                {
                    iterator->second = pair.second;
                    return;
                }

                bucket->emplace_back(pair);
            }
            return;
        });

    });


    for(auto* ptr : table)
    {
        delete ptr;
    }

    //копируются только указатели на списки
    table = std::vector(newTable);
    log("ok");
}



uint PrimeNumberHashPolicy::nextSizeOver(uint size)
{
    static constexpr uint prime_list[] =
    {
        3, 5, 7, 11, 13, 17, 23, 29, 37, 47,
        59, 73, 97, 127, 151, 197, 251, 313, 397,
        499, 631, 797, 1009, 1259, 1597, 2011, 2539,
        3203, 4027, 5087, 6421, 8089, 10193, 12853, 16193,
        20399, 25717, 32401, 40823, 51437, 64811, 81649,
        102877, 129607, 163307, 205759, 259229, 326617,
        411527, 518509, 653267, 823117, 1037059, 1306601,
        1646237, 2074129, 2613229, 3292489, 4148279, 5226491,
        6584983, 8296553, 10453007, 13169977, 16593127, 20906033,
        26339969, 33186281, 41812097, 52679969, 66372617,
        83624237, 105359939, 132745199, 167248483, 210719881,
        265490441, 334496971, 421439783, 530980861, 668993977,
        842879579, 1061961721, 1337987929, 1685759167, 2123923447,
        2675975881, 3371518343, 4247846927
    };

    const uint* found = std::upper_bound(std::begin(prime_list), std::end(prime_list) - 1, size);

    return *found;
}





} // end of namespace "slice"



#endif // HASHTABLE_H_INCLUDED
