#include <iostream>
#include <ctime>
#include <typeinfo>
#include <unordered_set>
#include <unordered_map>
#include <functional>
#include <iterator>
#include <vector>
#include <map>
#include <stdio.h>

#include "include/structures/hashtable.h"
#include "include/structures/hashfunc.h"
#include "include/log.h"
#include "include/name_generator.h"
#include "include/form.h"

#include <QApplication>
#include <QStyleFactory>


//#include <boost/algorithm/string.hpp>



using std::cout, std::endl, std::cin, std::string, std::vector;
using namespace slice;




template<>
struct slice::Hash<short> final
{
    uint operator()(short key, uint tableSize) const
    {
        return key % tableSize;
    }
};

//    std::function<uint (short, uint)> f  = [](short key, uint m) { return key % m; };
//    HashTable<short, int, std::function<uint (short, uint)>> wow(137, f);


int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
     QApplication::setStyle(QStyleFactory::create("Fusion"));
    Form form;
    form.show();




    QTextStream cin(stdin);
    QTextStream cout(stdout);
    cin.setCodec("CP866");
    cout.setCodec("CP866");


    cout << std::numeric_limits<int>::max() << endl;


//    HashTable<QString, int> table(631);
//    NameGenerator generator;


//    QVector<QString> homies;
//    for (int i = 0; i < 5; i++)
//    {
//        homies.append(generator.getRandomPerson().toString());
//        table.put(homies.last(), -128);
//    }



//    for (int i = 0; i < 1000000; i++)
//    {
//        table.put(generator.getRandomPerson().toString(), i);
//        if (i % 20000 == 0)
//            printf("%d\n", i);
//    }

//    QElapsedTimer timer;
//    timer.start();

//    cout << "GET: " << table.get(homies[0]) << endl;
//    int time = timer.elapsed();
//    cout << "TIME: " << time << " ms" <<  endl;















    //    int arr[] = { 3,2,432,5,345,43,5,345,34};
    //    int* found = std::upper_bound(std::begin(arr), std::end(arr) - 1, 500);

    //    std::list<int>::iterator it;

    //    HashTable<string, string> table(3);

    //    try {
    //        table.put("Mike", "Pike");
    //        table.put("Dua", "Lipa");
    //        table.put("Meynard", "Keenan");
    //        table.put("Meynard", "James");
    //        table.put("BestBand", "Tool");
    //        table.put("Bass", "Wooten");
    //        table.put("Guitar", "Dimebag");
    //        table.put("Vocal", "Anhelmo");
    //        table.put("Drum", "Daney");
    //        table.put("Xzibit", "Paparazi");


    //        std::cout << table.get("sMike") << std::endl;
    //        std::cout << table.get("Dua") << std::endl;
    //    }
    //    catch (std::exception& e) {
    //        logger(e.what());
    //        logger("ALARM");
    //    }







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





    /*          TEST

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
*/

    cout << "Done.";
    return app.exec();
}
