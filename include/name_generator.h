#ifndef NAME_GENERATOR_H_INCLUDED
#define NAME_GENERATOR_H_INCLUDED

#include <QVector>
#include <QString>
#include <QDate>
#include <QRandomGenerator>

#include <memory>



namespace slice {

struct Person;


class NameGenerator
{
private:
    static std::unique_ptr<const NameGenerator> INSTANCE;

    QRandomGenerator* rand;
    quint32 size;
    QVector<QString> fnames;
    QVector<QString> lnames;
    QVector<QString> patronymics;


    NameGenerator();

    NameGenerator(const NameGenerator&) = delete;
    NameGenerator& operator=(const NameGenerator&) = delete;

public:
    ~NameGenerator();

    static const NameGenerator* getInstance();

    Person getRandomPerson(int ageMin = 15, int ageMax = 40) const;
    int getInt(int lowest, int highest) const;
};



struct Person
{
    QString fname;
    QString lname;
    QString patronymic;
    QDate date;

    QString toString() const;
};


} // end of namespace "slice"


#endif // NAME_GENERATOR_H_INCLUDED
