#include <iostream>
#include <ctime>
#include <typeinfo>
#include <unordered_set>
#include <unordered_map>
#include <functional>
#include <iterator>
#include <vector>


#include "include/structures/hashtable.h"
#include "include/structures/hashfunc.h"
#include "include/log.h"


using std::cout, std::endl, std::cin, std::string, std::vector;
using namespace slice;



struct Point
{
    int x, y;
};



// TODO алгоритм решето Эратосфена
void separator(vector<uint>& vec)
{
    for (uint j = 0; j < vec.size(); j++)
    {
        if (vec[j] == 0)
            continue;
        uint p = vec[j];
        for (uint i = 2, n = i * p; n < vec.size(); i++)
        {
            n = i * p;
            vec[n - 1] = 0;
        }
    }

}



int main()
{
    std::srand(static_cast<uint>(time(nullptr)));

    //    vector<uint> series;
    //    series.reserve(120);

    //    log(series.size());
    //    log(series.capacity());

    //    series.push_back(0);
    //    for (uint i = 2; i <= 120; i++)
    //    {
    //        series.push_back(i);
    //    }

    //    log("size_t" ,sizeof(size_t));


    //    log("size ", series.size());
    //    log("last ", series.back());

    //    separator(series);




    HashTable<string, int> table(11);


    try {
        table.put("Mike", 545);
        table.put("Dua", 625);
        table.put("Lipa", 435);
        table.put("Lipa", 555);
        table.rehash();
        std::cout << table.get("Mike") << std::endl;
        std::cout << table.get("Dua") << std::endl;
    }
    catch (std::exception& e) {
        log(e.what());
        std::cerr << e.what() << '\n';
        const boost::stacktrace::stacktrace* st = boost::get_error_info<traced>(e);
        if (st)
            std::cerr << *st << '\n';
    }





    int ar[] = {2,3,214,23,4,234, 2};
    std::for_each(std::begin(ar), std::end(ar), [](int n)
    {
       log(_(n));
    });





    //    //    std::function<uint (const std::string&, uint)> f  = [](const std::string& str, uint m) { return str.length() % m; };
    //    //    slice::HashTable<string, int, std::function<uint (const std::string&, uint)>> dd(137, f);
    //    //    dd.put("Tool", 10000);


    //    std::list<pair<string, string>> lst;
    //    lst.push_back(pair<string, string>("Dua Lipa", "Blow Your Mind"));
    //    lst.push_back(pair<string, string>("Taylor", "Style"));
    //    lst.push_back(pair<string, string>("Tool", "Right in Two"));
    //    lst.push_back(pair<string, string>("Childish", "Gambino"));

    //    string key = "Taylsr";
    //    auto iter = std::find_if(lst.begin(), lst.end(), [&key](const pair<string, string>& pr)
    //    {
    //        return pr.first == key;
    //    });



    //    log(typeid(iter).name());
    //    if (iter != lst.end())
    //    {
    //        log(iter->first);
    //        log(iter->second);
    //    }
    //    else {
    //        log("fuckj");
    //    }





    //1 1 2 3 5 8 13 21

    // 1 1 10 11 101 1000 1101  10101

    //  (1 ^ 1)    (1 & 1)

    /*
     * int add(int i, int j)
{
    int uncommonBits = i ^ j;
    int commonBits = i & j;

    if (commonBits == 0)
        return uncommonBits;

    return add(uncommonBits, commonBits << 1);
     */






    //    HashTable<int, int> table(4457);
    //    for (int i = 0; i < 1000000; ++i) {
    //        table.put(i, i);
    //    }


    //    log("generated");


    //    table.get(700434);
    //    log("requested");

    //    std::vector<int> vec(1000000);
    //    for (int i = 0; i < 1000000; ++i) {
    //        vec[i] = i;
    //    }

    //    log("generated_vector");
    //    for (int i = 0; i < 1000000; ++i) {
    //        if (vec[i] = 700434)
    //        {
    //            log("YEAH found");
    //            break;
    //        }
    //    }


    return 0;
}






// TODO добавить лист и интерфейс
////#ifndef ILIST_H_INCLUDED
//#define ILIST_H_INCLUDED

//#include <list>
//#include <iostream>

//template<typename T>
//class IList
//{
//public:
//    virtual ~IList(){}

////    void push_back(const T& obj) = 0;
////    void push_front(const T& obj) = 0;
////    void pop_back() = 0;
////    virtual void pop_front() = 0;
//};


//template<typename T>
//class TempList :  public std::list<T>, public IList<T>
//{
//public:

////    virtual ~TempList() override;

//};

////#endif // ILIST_H_INCLUDED
