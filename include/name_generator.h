#ifndef NAME_GENERATOR_H_INCLUDED
#define NAME_GENERATOR_H_INCLUDED

#include <QVector>
#include <QString>
#include <QRandomGenerator>


namespace slice {

struct Person;


class NameGenerator
{
private:
    static quint32 size;
    static QVector<QString> fnames;
    static QVector<QString> lnames;
    static QVector<QString> patronymics;

    static QRandomGenerator* rand;


    friend struct Constructor;
    struct Constructor
    {
        Constructor();
    };
    static Constructor ctor;

public:

    Person getRandomPerson() const;
};



struct Person
{
    QString fname;
    QString lname;
    QString patronymic;

    QString fullname() const;
};





} // end of namespace "slice"


#endif // NAME_GENERATOR_H_INCLUDED
