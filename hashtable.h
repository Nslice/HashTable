#ifndef HASHTABLE_H_INCLUDED
#define HASHTABLE_H_INCLUDED


//#include <cstdio>
#include <stdexcept>
#include <utility>
#include <vector>
#include "ilist.h"
#include "hashfunc.h"
#include <functional>

typedef unsigned int uint;


inline void log(const std::string& str)
{
    std::cout << str << std::endl;
}



template<typename K, typename V,
         typename F = std::hash<K>>
class HashTable
{
private:
    std::vector<IList<std::pair<K, V>*>> table;
    uint tableSize;
    F getHashCode;


    HashTable(const HashTable&) = delete;
    HashTable& operator=(const HashTable&) = delete;

    void operator()() =delete;

public:
    explicit HashTable(uint tableSize = 117);
    ~HashTable();




    V put(K key, V value);
    V get(K key) const;




public:
};


template<typename K, typename V, typename F>
HashTable<K, V, F>::HashTable(uint tableSize)
    : table(tableSize, nullptr), getHashCode()
{
    std::cout << "YEEAH constructor\n";
    this->tableSize = tableSize;
}


template<typename K, typename V, typename F>
HashTable<K, V, F>::~HashTable()
{
    std::cout << "YEE\n";
//    throw std::logic_error("not implemnented");
}


template<typename K, typename V, typename F>
V HashTable<K, V, F>::put(K key, V value)
{
    uint hash = getHashCode(key);
    hash %= tableSize;
    table[hash];
    log("size" + table.size());


    return V();
}


template<typename K, typename V, typename F>
V HashTable<K, V, F>::get(K key) const
{
    return V();
}



#endif // HASHTABLE_H_INCLUDED
