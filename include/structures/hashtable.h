#ifndef HASHTABLE_H_INCLUDED
#define HASHTABLE_H_INCLUDED


#include <typeinfo>
#include <stdexcept>
#include <utility>
#include <vector>
#include <functional>
#include <list>


#include "include/structures/hashfunc.h"
#include "include/log.h"
#include "include/aliases.h"


// TODO в namespace добавить вместе с хеш функцией


// TODO в 3 параметр можно передавать лямбды через std::function
template<typename K, typename V, typename F = Hash<K>>
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

public:
    explicit HashTable(uint tableSize = 117);
    ~HashTable();

    V put(K key, V value);
    V get(K key) const;
};



template<typename K, typename V, typename F>
HashTable<K, V, F>::HashTable(uint tableSize)
    : table(tableSize, nullptr), getHashCode()
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
    // TODO надо возвращать итератор
    throw std::invalid_argument("key not exsits");
}



#endif // HASHTABLE_H_INCLUDED
