#include <QIntValidator>
#include <QDebug>

#include "include/name_generator.h"
#include "include/form.h"
#include "ui_form.h"



Form::Form(QWidget* parent) : QWidget(parent),  ui(new Ui::Form()),
    mTable(251), mFile("queries.txt"), mBar(this)
{
    ui->setupUi(this);
    resize(width() + 100, height());
    ui->numberGenerateEdit->setValidator(new QIntValidator(0, std::numeric_limits<int>::max(),
                                                           ui->numberGenerateEdit));
    ui->label->setBuddy(ui->additionalTextArea);
    ui->splitter->setStretchFactor(0, 10);
    ui->splitter->setStretchFactor(1, 5);


    const int tabStop = 8;
    QFontMetrics metrics(ui->mainTextArea->font());
    ui->mainTextArea->setTabStopWidth(tabStop * metrics.width(' '));
    ui->additionalTextArea->setTabStopWidth(tabStop * metrics.width(' '));


    //Progress bar
    mBar.setRange(0, 100);
    ui->gridLayout->addWidget(&mBar, 1, 0, 1, 1);
    mBar.hide();


    //Thread
    mThread = new GenerateThread(this);
    connect(mThread, &GenerateThread::ticks, &mBar, &QProgressBar::setValue);
    connect(mThread, &GenerateThread::started, &mBar, &QProgressBar::show);
    connect(mThread, &GenerateThread::finished, &mBar, &QProgressBar::hide);
    connect(mThread, &GenerateThread::finished, this, &Form::setEnabledButtons);
}



Form::~Form()
{
    dumpObjectTree();
    delete mThread;
    delete ui;
}



void Form::on_generateButton_clicked()
{
    mThread->start();
}



void Form::on_testButton_clicked()
{
    ui->mainTextArea->clear();
    QString text;
    mFile.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in(&mFile);
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

            text.append("{key:\"" + key + "\", value:" + QString::number(value) + "}, time:"
                        + QString::number(millis) + "ms " + QString::number(nanos) + "ns\n");
        }
        catch (std::out_of_range ex)
        {
            text.append(QString("out_of_range exception, msg:") + ex.what() + "\n");
        }
    }

    ui->mainTextArea->append(text);
    mFile.close();
}



void Form::on_searchButton_clicked()
{
    ui->mainTextArea->clear();
    QString text;

    try
    {
        QString key = ui->searchEdit->text();
        QElapsedTimer timer;
        timer.start();
        int value = mTable.get(key);
        quint64 nanos = timer.nsecsElapsed();
        quint64 millis = nanos / 1000000;

        text = ("{key:\"" + key + "\", value:" + QString::number(value) + "}, time:"
                    + QString::number(millis) + "ms " + QString::number(nanos) + "ns\n");
    }
    catch (std::out_of_range ex)
    {
        text = QString("out_of_range exception, msg:") + ex.what() + "\n";
    }

    ui->mainTextArea->append(text);
}



void Form::on_clearButton_clicked()
{
    ui->mainTextArea->clear();
    ui->additionalTextArea->clear();
    mTable.clear();
    ui->searchButton->setEnabled(false);
    ui->testButton->setEnabled(false);
}



void Form::on_stateButton_clicked()
{
    QString text;
    text.append(QString("{items:") + QString::number(mTable.size()) + ", tableSize:" +
                QString::number(mTable.sizeTable()) + "}\n");
    ui->mainTextArea->append(text);
}



void Form::setEnabledButtons()
{
   ui->searchButton->setEnabled(true);
   ui->testButton->setEnabled(true);
}





//GenerateThread-----------------------------------
Form::GenerateThread::GenerateThread(Form* form)
{
    this->form = form;
}



void Form::GenerateThread::run()
{
    for (QString line : form->ui->additionalTextArea->toPlainText().split("\n"))
    {
        if (!line.isEmpty())
        {
            QStringList parts = line.split("|");
            form->mTable.put(parts.first().trimmed(), parts.last().toInt());
        };
    }


    auto* generator = slice::NameGenerator::getInstance();

    form->mFile.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&form->mFile);

    uint count = form->ui->numberGenerateEdit->text().toInt();
    uint k = count / 100;
    k = (k == 0) ? 1 : k;

    int tick = 1;

    for (uint i = 0; i < count; i++)
    {
        QString person = generator->getRandomPerson().toString();
        form->mTable.put(person, generator->getInt(-5000, 25000));
        if (i % k == 0)
        {
            out << person << "|" << i << endl;
            emit ticks(tick++);
        }
    }

    form->mFile.close();
 }
