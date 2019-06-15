#ifndef HASHTABLE_H_INCLUDED
#define HASHTABLE_H_INCLUDED

#include <stdexcept>
#include <algorithm>
#include <vector>
#include <list>

#include "include/aliases.h"
#include "include/structures/hashfunc.h"



namespace slice {

// В 3 параметр можно передавать лямбды через std::function.
template<typename K, typename V, typename F = Hash<K>>
class HashTable
{
    typedef std::pair<K, V> node;
    typedef std::vector<std::list<node>*> Table;

private:
    const F& getHashCode;
    Table mTable;
    uint tableSize;
    ulong items;


    HashTable(const HashTable&) = delete;
    HashTable& operator=(const HashTable&) = delete;

public:
    class Iterator;


    explicit HashTable(uint tableSize = 127, const F& hasher = F());
    ~HashTable();

    ulong size() const { return items; }
    bool isEmpty() const { return items == 0; }

    bool containsKey(const K& key) const;

    void put(const K& key, const V& value);
    V& get(const K& key) const;
    bool remove(const K& key);
    void clear();


    Iterator begin();
    Iterator end();

private:
    void rehash();
    static uint nextSizeOver(uint size);
    bool _put(const node& pair, Table& t);
};



template<typename K, typename V, typename F>
class HashTable<K, V, F>::Iterator
{
    friend HashTable;

    typedef typename Table::iterator TableIterator;

private:
    TableIterator itTable;
    TableIterator itEnd;
    typename std::list<node>::iterator current;

    //мнимый элемент, используется как конец для list итератора.
    static typename std::list<node>::iterator dummy;

public:
    Iterator() = default;
    Iterator(const Iterator& other) = default;
    Iterator& operator=(const Iterator& other) = default;


    node& operator*() const;
    typename std::list<node>::iterator operator->() const;


    Iterator& operator++();  //префиксный
    Iterator operator++(int);   //постфиксный

    bool operator==(const Iterator& other) const;
    bool operator!=(const Iterator& other) const;


private:
    static Iterator getEndIterator(const TableIterator& it1);

    static Iterator getBeginIterator(const TableIterator& begin,
                                     const TableIterator& end);

    void increment();
};








template<typename K, typename V, typename F>
HashTable<K, V, F>::HashTable(uint tableSize, const F& hasher)
    : getHashCode(hasher), mTable(tableSize, nullptr)
{
    this->tableSize = tableSize;
    items = 0;
}



template<typename K, typename V, typename F>
HashTable<K, V, F>::~HashTable()
{
    clear();
}



template<typename K, typename V, typename F>
bool HashTable<K, V, F>::containsKey(const K& key) const
{
    uint hashIndex = getHashCode(key, tableSize);
    if (mTable[hashIndex] != nullptr)
    {
        std::list<node>* bucket = mTable[hashIndex];
        for (node& pair : *bucket)
        {
            if (pair.first == key)
                return true;
        }
    }
    return false;
}



template<typename K, typename V, typename F>
void HashTable<K, V, F>::put(const K& key, const V& value)
{
    // TODO коэффициент
    double dd = (double) items / tableSize;
    if ((double) items / tableSize >= 2.5)
        rehash();
    if (_put(std::make_pair(key, value), mTable))
        items++;
}



template<typename K, typename V, typename F>
V& HashTable<K, V, F>::get(const K& key) const
{
    uint hashIndex = getHashCode(key, tableSize);
    if (mTable[hashIndex] != nullptr)
    {
        std::list<node>* bucket = mTable[hashIndex];
        for (node& pair : *bucket)
        {
            if (pair.first == key)
                return pair.second;
        }
    }

    throw std::invalid_argument("key not exsits");
}



template<typename K, typename V, typename F>
bool HashTable<K, V, F>::remove(const K& key)
{
    uint hashIndex = getHashCode(key, tableSize);
    if (mTable[hashIndex] != nullptr)
    {
        std::list<node>* bucket = mTable[hashIndex];
        auto iterator = bucket->begin();
        for ( ; iterator != bucket->end(); ++iterator)
        {
            if (iterator->first == key)
            {
                bucket->erase(iterator);
                items--;
                return true;
            }
        }
    }
    return false;
}



template<typename K, typename V, typename F>
void HashTable<K, V, F>::clear()
{
    for (uint i = 0; i < tableSize; i++)
    {
        delete mTable[i];
        mTable[i] = nullptr;
    }
    items = 0;
}



template<typename K, typename V, typename F>
typename HashTable<K, V, F>::Iterator
HashTable<K, V, F>::begin()
{
    typename Table::iterator it = mTable.begin();
    for ( ; it != mTable.end(); ++it)
    {
        if (*it != nullptr)
            return Iterator::getBeginIterator(it, mTable.end());
    }

    return end();
}



template<typename K, typename V, typename F>
typename HashTable<K, V, F>::Iterator
HashTable<K, V, F>::end()
{
    return Iterator::getEndIterator(mTable.end());
}




//-------------------PRIVATE---------------------------------
template<typename K, typename V, typename F>
void HashTable<K, V, F>::rehash()
{
    tableSize = nextSizeOver(tableSize);
    Table newTable(tableSize, nullptr);
    items = 0;

    for (auto* list : mTable)
    {
        if (list == nullptr)
            continue;

        for (auto& pair : *list)
        {
            if (_put(pair, newTable))
                items++;
        }
    }


    for(auto* ptr : mTable)
    {
        delete ptr;
    }

    mTable = std::move(newTable);
}



template<typename K, typename V, typename F>
uint HashTable<K, V, F>::nextSizeOver(uint size)
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



/**
 * @brief Помещает pair в таблицу.
 * @param t нужен для рехеша чтобы в временную таблицу помещать элементы.
 * @return true если добавился новый ключ, false если перезаписал значение по существующему.
 */
template<typename K, typename V, typename F>
bool HashTable<K, V, F>::_put(const node& pair, Table& t)
{
    uint hashIndex = getHashCode(pair.first, tableSize);
    std::list<node>* bucket = t[hashIndex];

    if (bucket == nullptr)
    {
        bucket = new std::list<node>();
        bucket->push_back(pair);
        t[hashIndex] = bucket;
    }
    else
    {
        auto iterator = std::find_if(bucket->begin(), bucket->end(), [&pair](const node& p) {
            return p.first == pair.first;
        });
        // если такой ключ есть
        if (iterator != bucket->end())
        {
            iterator->second = pair.second;
            return false;
        }

        bucket->push_back(pair);
    }
    return true;
}




//-----------------------Iterator-----------------------------------------

template<typename K, typename V, typename F>
typename std::list<std::pair<K, V>>::iterator HashTable<K, V, F>::Iterator::dummy =
         std::list<std::pair<K, V>>(1).begin();



template<typename K, typename V, typename F>
typename HashTable<K, V, F>::node&
HashTable<K, V, F>::Iterator::operator*() const
{
    return *current;
}



template<typename K, typename V, typename F>
typename std::list<typename HashTable<K, V, F>::node>::iterator
HashTable<K, V, F>::Iterator::operator->() const
{
    return current;
}



//префиксный инкремент
template<typename K, typename V, typename F>
typename HashTable<K, V, F>::Iterator&
HashTable<K, V, F>::Iterator::operator++()
{
    increment();
    return *this;
}



//постфиксный инкремент
template<typename K, typename V, typename F>
typename HashTable<K, V, F>::Iterator
HashTable<K, V, F>::Iterator::operator++(int)
{
    Iterator tmp(*this);
    increment();
    return tmp;
}



template<typename K, typename V, typename F>
bool HashTable<K, V, F>::Iterator::operator==(const Iterator& other) const
{
    return (itTable == other.itTable) && (current == other.current);
}



template<typename K, typename V, typename F>
bool HashTable<K, V, F>::Iterator::operator!=(const Iterator& other) const
{
    return !operator==(other);
}



//-------------------PRIVATE---------------------------------

template<typename K, typename V, typename F>
typename HashTable<K, V, F>::Iterator
HashTable<K, V, F>::Iterator::getBeginIterator(const TableIterator& begin,
                                               const TableIterator& end)
{
    Iterator iter;
    iter.itTable = begin;
    iter.itEnd = end;
    iter.current = (*begin)->begin();
    return iter;
}



template<typename K, typename V, typename F>
typename HashTable<K, V, F>::Iterator
HashTable<K, V, F>::Iterator::getEndIterator(const TableIterator& it1)
{
    Iterator iter;
    iter.itTable = it1;
    iter.itEnd = it1;
    iter.current = dummy;
    return iter;
}


template<typename K, typename V, typename F>
void HashTable<K, V, F>::Iterator::increment()
{
    ++current;
    if (current == (*itTable)->end())
    {
        while (true)
        {
            ++itTable;

            if (itTable == itEnd)
                break;

            if (*itTable != nullptr)
            {
                current = (*itTable)->begin();
                break;
            }
        }
    }

    if (itTable == itEnd)
        current = dummy;
}


} // end of namespace "slice"



#endif // HASHTABLE_H_INCLUDED
