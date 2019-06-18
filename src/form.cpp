#include <QProgressBar>
#include <QIntValidator>
#include <QDebug>

#include "include/form.h"
#include "ui_form.h"



Form::Form(QWidget* parent) : QWidget(parent),  ui(new Ui::Form()),
    mTable(), file("queries.txt")
{
    ui->setupUi(this);
    ui->numberGenerateEdit->setValidator(new QIntValidator(0, std::numeric_limits<int>::max(),
                                                           ui->numberGenerateEdit));
    ui->label->setBuddy(ui->additionalTextArea);
    ui->splitter->setStretchFactor(0, 10);
    ui->splitter->setStretchFactor(1, 5);

    resize(width() + 100, height());


    const int tabStop = 8;
    QFontMetrics metrics(ui->mainTextArea->font());
    ui->mainTextArea->setTabStopWidth(tabStop * metrics.width(' '));
    ui->additionalTextArea->setTabStopWidth(tabStop * metrics.width(' '));
}



Form::~Form()
{
    dumpObjectTree();
    delete ui;
}



void Form::on_generateButton_clicked()
{
    QVector<QString> homies;
    for (QString line : ui->additionalTextArea->toPlainText().split("\n"))
    {
        if (!line.isEmpty())
        {
            QStringList parts = line.split("|");
            mTable.put(parts.first().trimmed(), parts.last().toInt());
        };
    }



    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);

    QProgressBar bar(this);
    bar.setRange(0, 100);
    bar.setValue(0);
    ui->gridLayout->addWidget(&bar, 1, 0, 1, 1);
    bar.show();

    uint count = ui->numberGenerateEdit->text().toInt();
    uint k = count / 100;

    for (uint i = 0; i < count; i++)
    {
        QString person = mGenerator.getRandomPerson().toString();
        mTable.put(person, mGenerator.rand->bounded(-5000, 25000));
                if (i % k == 0)
        {
            out << person << "|" << i << endl;
            bar.setValue(bar.value() + 1);
        }
    }

    file.close();
    ui->gridLayout->removeWidget(&bar);
    ui->searchButton->setEnabled(true);
    ui->testButton->setEnabled(true);
}



void Form::on_clearButton_clicked()
{
    ui->mainTextArea->clear();
    ui->additionalTextArea->clear();
    mTable.clear();
    ui->searchButton->setEnabled(false);
    ui->testButton->setEnabled(false);
}



void Form::on_searchButton_clicked()
{
    ui->mainTextArea->clear();
    QString text;
    QString key = ui->searchEdit->text();

    try
    {
        QElapsedTimer timer;
        timer.start();
        int value = mTable.get(key);
        quint64 nanos = timer.nsecsElapsed();
        quint64 millis = nanos / 1000000;

        text.append("{key:" + key + ", value:" + QString::number(value) + "}, time:"
                    + QString::number(millis) + "ms " + QString::number(nanos) + "ns\n");
    }
    catch (std::out_of_range ex)
    {
        text = QString("out_of_range exception, msg:") + ex.what() + "\n";
    }

    ui->mainTextArea->append(text);
}



void Form::on_testButton_clicked()
{
    ui->mainTextArea->clear();
    QString text;
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in(&file);
    QElapsedTimer timer;

    QString line, key;
    while (!(line = in.readLine()).isNull())
    {
        try
        {
            key = line.split("|").first();
            timer.restart();
            int value = mTable.get(key);
            quint64 nanos = timer.nsecsElapsed();
            quint64 millis = nanos / 1000000;

            text.append("{key:" + key + ", value:" + QString::number(value) + "}, time:"
                        + QString::number(millis) + "ms " + QString::number(nanos) + "ns\n");
        }
        catch (std::out_of_range ex)
        {
            text.append(QString("out_of_range exception, msg:") + ex.what() + "\n");
        }
    }

    ui->mainTextArea->append(text);
    file.close();
}



void Form::on_stateButton_clicked()
{
    QString text;
    text.append(QString("{items:") + QString::number(mTable.size()) + ", tableSize:" +
            QString::number(mTable.sizeTable()) + "}\n");
    ui->mainTextArea->append(text);
}
