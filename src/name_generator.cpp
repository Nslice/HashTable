#include <QFile>
#include <QtXml>

#include "include/name_generator.h"


using slice::NameGenerator, slice::Person;


std::unique_ptr<const NameGenerator> NameGenerator::INSTANCE = nullptr;


NameGenerator::NameGenerator()
{
    qDebug() << "NameGenerator constructor";
    this->rand = QRandomGenerator::system();
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

    this->fnames = std::move(all[0]);
    this->lnames = std::move(all[1]);
    this->patronymics = std::move(all[2]);
    this->size = std::min({fnames.size(), lnames.size(), patronymics.size()});
}



NameGenerator::~NameGenerator()
{
    qDebug() << "NameGenerator destructor";
}



const NameGenerator* NameGenerator::getInstance()
{
    if (INSTANCE == nullptr)
    {
        INSTANCE.reset(new NameGenerator());
    }

    return INSTANCE.get();
}



Person NameGenerator::getRandomPerson(int ageMin, int ageMax) const
{
    if (ageMax < ageMin)
        throw std::invalid_argument("ageMax should be >= then ageMin");

    int currYear = QDate::currentDate().year();
    int lowYear = currYear - ageMax;
    int highYear = currYear - ageMin + 1;

    return Person {
        fnames.at(rand->bounded(size)),
        lnames.at(rand->bounded(size)),
        patronymics.at(rand->bounded(size)),
        QDate(rand->bounded(lowYear, highYear),
              1 + rand->bounded(12),
              1 + rand->bounded(28))
    };
}



int NameGenerator::getInt(int lowest, int highest) const
{
    return rand->bounded(lowest, highest);
}





//--------------------------struct Person------------------------
QString Person::toString() const
{
    return fname + " " + lname + " " + patronymic + " " + date.toString("dd.MM.yyyy");
}
