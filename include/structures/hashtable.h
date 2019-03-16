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


// TODO в 3 параметр можно передавать лямбды через std::function
template<typename K, typename V, typename F = Hash<K>>
class HashTable
{
private:
    const F& getHashCode;
    std::vector<std::list<std::pair<K, V>>*> table;
    // TODO поле убрать
    uint tableSize;
    uint items;


    HashTable(const HashTable&) = delete;
    HashTable& operator=(const HashTable&) = delete;

public:
    explicit HashTable(uint tableSize = 117, const F& hasher = F());
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
    for (uint i = 0; i < table.size(); i++)
    {
        delete table[i];
    }
}



template<typename K, typename V, typename F>
const V& HashTable<K, V, F>::put(const K& key, const V& value)
{
    // TODO пересмотреть коэффициент
    if (items > tableSize * 2)
        rehash();

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
    uint newTableSize = tableSize * 2;
    for (int i = newTableSize; i * i; i++) {

    }

}



} // end of namespace "slice"


#endif // HASHTABLE_H_INCLUDED
