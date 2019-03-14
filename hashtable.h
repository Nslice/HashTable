#ifndef HASHTABLE_H_INCLUDED
#define HASHTABLE_H_INCLUDED


//#include <cstdio>
#include <stdexcept>
#include <utility>
#include <vector>
#include "ilist.h"
#include "hashfunc.h"
#include <functional>
#include <list>

typedef unsigned int uint;


inline void log(const std::string& str)
{
    std::cout << "log: " << str << std::endl;
}



template<typename K, typename V, typename F = std::hash<K>>
class HashTable
{
private:
    std::vector<std::list<std::pair<K, V>>*> table;
    // TODO поле убрать
    uint tableSize;
    F getHashCode;
    uint items;


    HashTable(const HashTable&) = delete;
    HashTable& operator=(const HashTable&) = delete;

    void operator()() =delete;

public:
    explicit HashTable(uint tableSize = 117);
    ~HashTable();

    V put(K key, V value);
    V get(K key) const;
};



template<typename K, typename V, typename F>
HashTable<K, V, F>::HashTable(uint tableSize)
    : table(tableSize,nullptr), getHashCode()
{
    std::cout << "YEEAH constructor\n";
    this->tableSize = tableSize;
    items = 0;
}


template<typename K, typename V, typename F>
HashTable<K, V, F>::~HashTable()
{
    std::cout << "YEE\n";
    for (int i = 0; i < table.size(); i++)
    {
        // TODO обязательно это???
        if (table[i] != nullptr)
            delete table[i];
    }

}


template<typename K, typename V, typename F>
V HashTable<K, V, F>::put(K key, V value)
{
    uint hash = getHashCode(key);
    hash %= tableSize;
    if (table[hash] == nullptr)
    {
        auto* list = new std::list<std::pair<K, V>>();
        list->push_back(std::pair<K, V>(key, value));
        table[hash] = list;
        items++;
    }
    else
    {
        // TODO переписать
        auto* list = table[hash];
        for (auto pair : *list)
        {
            if (pair.first == key)
            {
                pair.second = value;
//                items++;
                return value;
            }
        }
        list->push_back(std::pair<K, V>(key, value));
        items++;
    }

    // TODO хз зачем возвращаю, делаю по примеру HashMap из JDK
    // посмотреть в документации
    return value;
}


template<typename K, typename V, typename F>
V HashTable<K, V, F>::get(K key) const
{
    uint hash = getHashCode(key);
    hash %= tableSize;
    if (table[hash] != nullptr)
    {
        for (std::pair<K,V> pair : *(table[hash]))
        {
            if (pair.first == key)
                return pair.second;
        }
    }
    // TODO посмотреть как в других классах (языках) с этим справляются
    throw std::invalid_argument("key not exsits");
}



#endif // HASHTABLE_H_INCLUDED
