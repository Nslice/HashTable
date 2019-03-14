#include <iostream>
#include <ilist.h>
#include "hashtable.h"
#include <array>
#include <ctime>

struct S {
    std::string first_name;
    std::string last_name;
};

namespace std {
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
}


int main()
{
    //    std::function<uint (std::string)> f = [](std::string key)
    //    {
    //        key.length();
    //        return 2;
    //    };
    //    int n = 2;

    //    std::string str = "Meet the new boss...";
    //    std::hash<std::string> hash_fn;
    //    size_t str_hash = hash_fn(str);
    //    std::cout << str_hash << '\n';


    //    HashTable<std::string, int> table;
    //    table.put("Mike", 545);
    //    table.put("Dua", 625);
    //    table.put("Lipa", 435);

    //    std::cout << table.get("Mike") << std::endl;
    //    std::cout << table.get("Dua") << std::endl;


    std::srand(time(nullptr));
    log(std::to_string(rand()));

    HashTable<int, int> table(4457);
    for (int i = 0; i < 1000000; ++i) {
        table.put(i, i);
    }

    log("generated");


    table.get(700434);
    log("requested");

    std::vector<int> vec(1000000);
    for (int i = 0; i < 1000000; ++i) {
        vec[i] = i;
    }

    log("generated_vector");
    for (int i = 0; i < 1000000; ++i) {
        if (vec[i] = 700434)
        {
            log("YEAH found");
            break;
        }
    }





    //    using namespace std;
    //    vector<list<int>*> v(5, nullptr);
    //    cout << v.size() << endl;
    //    for (int i = 0; i < v.size(); ++i) {
    //        v[i] = new list<int>{43,4,34,3};
    //    }

    //    for (int i : *v[2])
    //        cout << i << endl;


    return 0;
}
