#ifndef FORM_H_INCLUDED
#define FORM_H_INCLUDED

#include <QWidget>
#include <QFile>
#include <QProgressBar>
#include <QThread>

#include "name_generator.h"
#include "structures/hashtable.h"


namespace Ui {
class Form;
}


class Form : public QWidget
{
    Q_OBJECT

private:
    class GenerateThread;
    friend class GenerateThread;


    Ui::Form* ui;
    slice::NameGenerator mGenerator;
    slice::HashTable<QString, int> mTable;
    QFile mFile;
    QProgressBar mBar;

    GenerateThread* mThread;


public:
    explicit Form(QWidget* parent = nullptr);
    ~Form();

private slots:
    void on_generateButton_clicked();
    void on_testButton_clicked();
    void on_searchButton_clicked();

    void on_clearButton_clicked();
    void on_stateButton_clicked();

    void setEnabledButtons();
};


class Form::GenerateThread : public QThread
{
   Q_OBJECT
private:
    Form* form;

public:
    GenerateThread() = default;
    GenerateThread(Form* form);

protected:
   virtual void run() override;

signals:
   void ticks(int);
};

#endif // FORM_H_INCLUDED
