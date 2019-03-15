#include <iostream>
#include <ctime>
#include <unordered_set>

#include "include/structures/hashtable.h"
#include "include/structures/hashfunc.h"


using std::cout, std::endl, std::cin, std::string;
using mylogger::log;




struct Point
{
    int x, y;
};

struct S
{
    std::string first_name;
    std::string last_name;
};


namespace std
{
template<>
struct hash<S>
{
    size_t operator()(const S &s) const
    {
        size_t h1 = std::hash<std::string>()(s.first_name);
        size_t h2 = std::hash<std::string>()(s.last_name);
        return h1 ^ ( h2 << 1 );
    }
};

//template<>
//struct hash<Point>
//{
//    uint operator()(const Point& p) const
//    {

//        uint n = static_cast<uint>(std::hash<int>()(p.x));
//        return n;
//    }
//};
}




int main()
{
    std::srand(static_cast<uint>(time(nullptr)));

    //TODO сделать так же со своим классом
    std::unordered_set<Point, std::function<size_t (const Point&)>> map;


    //    Hash<string> h;
    //    string s = "Meshuggah";
    //    log(h(s));

    //    Hash<int> h2;
    //    log(h2(252));

    //    log("std::hash ", std::hash<double>()(5.32));


    //    Hash<Point> hd;
    //    hd(Point());
    //    log("my Hash ", hd(Point()));

    Hash<string> ds;
    log(ds("ssds"));
    log(ds("ssds"));




    //    std::hash<Point> f;
    //    Point p;
    //    p.x = rand();
    //    log("checl");
    //    log("Point ", std::hash<Point>()(p));

    //    log("string ", std::hash<string>()(s));


    //    std::string str = "Meet the new boss...";
    //    std::hash<std::string> hash_fn;
    //    size_t str_hash = hash_fn(str);
    //    std::cout << str_hash << '\n';




    HashTable<string, int> table;
    table.put("Mike", 545);
    table.put("Dua", 625);
    table.put("Lipa", 435);

    std::cout << table.get("Mike") << std::endl;
    std::cout << table.get("Dua") << std::endl;


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
