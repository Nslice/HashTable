#include <QFile>
#include <QtXml>

#include "include/name_generator.h"


using slice::NameGenerator, slice::Person;


quint32 NameGenerator::size = 0;
QVector<QString> NameGenerator::fnames;
QVector<QString> NameGenerator::lnames;
QVector<QString> NameGenerator::patronymics;
NameGenerator::Constructor NameGenerator::ctor;

QRandomGenerator* NameGenerator::rand =
        QRandomGenerator::system();



NameGenerator::Constructor::Constructor()
{
    QFile f(":/dictionary.xml");
    if (!f.open(QIODevice::ReadOnly))
    {
        return;
    }

    QVector<QVector<QString>> all;
    all.reserve(3);

    QDomDocument doc;
    doc.setContent(&f);
    f.close();

    QDomElement component =  doc.documentElement()
            .firstChild()
            .toElement();

    while(!component.isNull())
    {
        if (component.tagName() == "ArrayOfString")
        {
            QDomElement child = component.firstChild().toElement();
            QVector<QString> vec;
            vec.reserve(60);

            while (!child.isNull())
            {
                if (child.tagName() == "string")
                    vec.append(child.firstChild().toText().data());
                child = child.nextSibling().toElement();
            }
            all.append(vec);
        }
        component = component.nextSibling().toElement();
    }

    fnames = std::move(all[0]);
    lnames = std::move(all[1]);
    patronymics = std::move(all[2]);
    size = std::min({fnames.size(), lnames.size(), patronymics.size()});
}



Person NameGenerator::getRandomPerson() const
{
    Person person{
        fnames.at(rand->bounded(size)),
        lnames.at(rand->bounded(size)),
        patronymics.at(rand->bounded(size))
    };
    return person;
}



QString Person::fullname() const
{
    QString fullname = fname + " " + lname + " " + patronymic;
    return fullname;
}
