#include <QProgressBar>
#include <QIntValidator>
#include <QDebug>

#include "include/form.h"
#include "ui_form.h"



Form::Form(QWidget* parent) : QWidget(parent),  ui(new Ui::Form()),
    mTable()
{
    ui->setupUi(this);
    ui->numberGenerateEdit->setValidator(new QIntValidator(0, std::numeric_limits<int>::max(),
                                                           ui->numberGenerateEdit));
    ui->label->setBuddy(ui->homiesTextArea);
    ui->splitter->setStretchFactor(0, 3);
    ui->splitter->setStretchFactor(1, 1);


    const int tabStop = 8;
    QFontMetrics metrics(ui->mainTextArea->font());
    ui->mainTextArea->setTabStopWidth(tabStop * metrics.width(' '));
    ui->homiesTextArea->setTabStopWidth(tabStop * metrics.width(' '));
}



Form::~Form()
{
    dumpObjectTree();
    delete ui;
}



void Form::on_generateButton_clicked()
{
    QVector<QString> homies;
    int val = -127;
    for (QString str : ui->homiesTextArea->toPlainText().split("\n"))
    {
        if (!str.isEmpty())
            mTable.put(str, val++);
    }


    QProgressBar bar(this);
    bar.setRange(0, 100);
    bar.setValue(0);
    ui->gridLayout->addWidget(&bar, 1, 0, 1, 1);
    bar.show();

    uint count = ui->numberGenerateEdit->text().toInt();
    uint k = count / 100;
    for (uint i = 0; i < count; i++)
    {
        mTable.put(mGenerator.getRandomPerson().toString(), i);
        if (i % k == 0)
            bar.setValue(bar.value() + 1);
    }

    ui->gridLayout->removeWidget(&bar);
}



void Form::on_clearButton_clicked()
{
    ui->mainTextArea->clear();
    ui->homiesTextArea->clear();
    mTable.clear();
}



void Form::on_searchButton_clicked()
{
    QString line;
    QString key = ui->searchEdit->text();

    try
    {
        QElapsedTimer timer;
        timer.start();
        int value = mTable.get(key);
        quint64 nanos = timer.nsecsElapsed();
        quint64 millis = nanos / 1000000;

        line.append("{key:" + key + ", value:" + QString::number(value) + "}, time:"
                    + QString::number(millis) + "ms " + QString::number(nanos) + "ns");
    }
    catch (std::out_of_range ex)
    {
        line = QString("out_of_range exception, msg:") + ex.what();
    }

    ui->mainTextArea->append(line);
}
