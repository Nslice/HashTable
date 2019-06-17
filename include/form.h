#ifndef FORM_H
#define FORM_H

#include <QWidget>

#include "name_generator.h"
#include "structures/hashtable.h"


namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT

private:
    slice::NameGenerator generator;
    slice::HashTable<QString, int> table;

public:
    explicit Form(QWidget *parent = nullptr);
    ~Form();

private slots:
    void on_generateButton_clicked();

private:
    Ui::Form *ui;
};

#endif // FORM_H
