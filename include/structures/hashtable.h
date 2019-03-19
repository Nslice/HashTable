#ifndef HASHTABLE_H_INCLUDED
#define HASHTABLE_H_INCLUDED

#include <stdexcept>
#include <algorithm>
#include <iterator>
#include <utility>
#include <vector>
#include <list>

#include "include/log.h"
#include "include/aliases.h"
#include "include/structures/hashfunc.h"



namespace slice {


// TODO в 3 параметр можно передавать лямбды через std::function
template<typename K, typename V, typename F = Hash<K>>
class HashTable
{
    typedef std::pair<K, V> node;
    class Iterator;

private:
    const F& getHashCode;
    std::vector<std::list<node>*> table;
    uint tableSize;
    ulong items;


    HashTable(const HashTable&) = delete;
    HashTable& operator=(const HashTable&) = delete;

public:
    explicit HashTable(uint tableSize = 127, const F& hasher = F());
    ~HashTable();

    void put(const K& key, const V& value);
    V& get(const K& key) const;




    void rehash(); // TODO потом перенести в private


    Iterator begin();
    Iterator end();

private:
    static uint nextSizeOver(uint size);
    bool _put(const node& pair, std::vector<std::list<node>*>& t);




};





template<typename K, typename V, typename F>
class HashTable<K, V, F>::Iterator
        : public std::iterator<std::input_iterator_tag, node, uint, node*, node>
{
    //        friend class HashTable;
private:
    uint index;
    std::vector<std::list<node>*>* table;
    typename std::list<node>::iterator current;


public:
    Iterator() {}
    Iterator(std::vector<std::list<node>*>* table, uint index)
    {
        this->table = table;
        this->index = index;
        this->current = (*table)[index]->begin();
    }


    // TODO еще  один const после типа зачем
    bool operator==(const Iterator& other) const;
    bool operator!=(const Iterator& other) const;
    Iterator& operator++(void);
    node& operator*() const;

};








template<typename K, typename V, typename F>
HashTable<K, V, F>::HashTable(uint tableSize, const F& hasher)
    : getHashCode(hasher), table(tableSize, nullptr)
{
    // TODO мб тут выделять память под все списки
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
void HashTable<K, V, F>::put(const K& key, const V& value)
{
    // TODO пересмотреть коэффициент
    //    if (items / tableSize >= 2.5)
    //    rehash();


    if (_put(std::make_pair(key, value), table))
        items++;
}



template<typename K, typename V, typename F>
V& HashTable<K, V, F>::get(const K& key) const
{
    uint hashIndex = getHashCode(key, tableSize);
    if (table[hashIndex] != nullptr)
    {
        for (node& pair : *(table[hashIndex]))
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
    tableSize = nextSizeOver(tableSize);
    decltype(table) newTable(tableSize, nullptr);
    items = 0;

    std::for_each(table.cbegin(), table.cend(), [&](const std::list<node>* list)
    {
        if (list == nullptr) return;
        std::for_each(list->cbegin(), list->cend(), [&](const node& pair)
        {
            if (_put(pair, newTable))
                items++;
        });
    });


    for(auto* ptr : table)
    {
        delete ptr;
    }

    //копируются только указатели на списки
    table = std::vector(newTable);
}




template<typename K, typename V, typename F>
typename HashTable<K, V, F>::Iterator HashTable<K, V, F>::begin()
{
    for (auto* list : table)
    {
        if (list != nullptr)
        {
            auto n = getHashCode(list->front().first, tableSize);
            return Iterator(&table, n);
        }
    }
    return Iterator();
}



template<typename K, typename V, typename F>
typename HashTable<K, V, F>::Iterator HashTable<K, V, F>::end()
{

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
bool HashTable<K, V, F>::_put(const node& pair, std::vector<std::list<node>*>& t)
{
    uint hashIndex = getHashCode(pair.first, tableSize);
    auto* bucket = t[hashIndex];

    if (bucket == nullptr)
    {
        bucket = new std::list<node>();
        bucket->emplace_back(pair);
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

        bucket->emplace_back(pair);
    }
    return true;
}



//-----------------------Iterator----------------------------------

//template<typename K, typename V, typename F>
//HashTable<K, V, F>::Iterator::Iterator()
//{

//}



//template<typename K, typename V, typename F>
//HashTable<K, V, F>::Iterator::Iterator(uint index,
//    typename std::list<node>::iterator current,
//    typename std::list<node>::iterator end)
//{
//    this->index;
//    this->current = current;
//    this->end = end;
//}




template<typename K, typename V, typename F>
typename HashTable<K, V, F>::Iterator& HashTable<K, V, F>::Iterator::operator++(void)
{
    current++;
    if (current == (*table)[index]->end())
    {

    }
    node chek = *current;
    log("ds");
    return *this;
}





//template<typename K, typename V, typename F>
//typename HashTable<K, V, F>::Iterator HashTable<K, V, F>::begin()
//{
//    Iterator iter;
//    for (auto* list : table)
//    {
//        if (list != nullptr)
//        {

//            Iterator iter(&list->front(), getHashCode(&list->front().first(), list->begin()));

//        }

//    }
//    return iter;
//}



//template<typename K, typename V, typename F>
//typename HashTable<K, V, F>::Iterator HashTable<K, V, F>::end()
//{
//    Iterator iter;

//    for (auto* list : table)
//    {
//        // TODO тут нужен последний список
//        if (list != nullptr)
//        {
//            Iterator iter(&list->end());
//        }

//    }
//    return iter;
//}



} // end of namespace "slice"



#endif // HASHTABLE_H_INCLUDED
