#include <QApplication>
#include <QStyleFactory>

#include "include/form.h"
#include "include/structures/hashtable.h"
#include "include/structures/hashfunc.h"

using namespace slice;


template<>
struct slice::Hash<short> final
{
    uint operator()(short key, uint tableSize) const
    {
        return key % tableSize;
    }
};



int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    QApplication::setStyle(QStyleFactory::create("Fusion"));
    Form form;
    form.show();


    //Переопределение хеш-функции через лямбду.
    //(2 вариант написать явную специализацию slice::Hash<T> для своего типа)
    std::function<uint (const std::string&, uint)> f  = [](const std::string& str, uint m)
    { return str.length() % m; };
    HashTable<std::string, int, std::function<uint (const std::string&, uint)>> t(137, f);
    t.put("Tool", 10000);

    qDebug() << "sizeof = " << sizeof(NameGenerator().getRandomPerson());


    return app.exec();
}
