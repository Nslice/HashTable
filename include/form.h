#ifndef FORM_H_INCLUDED
#define FORM_H_INCLUDED

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
    Ui::Form* ui;
    slice::NameGenerator mGenerator;
    slice::HashTable<QString, int> mTable;

public:
    explicit Form(QWidget* parent = nullptr);
    ~Form();

private slots:
    void on_generateButton_clicked();
    void on_clearButton_clicked();
    void on_searchButton_clicked();
};

#endif // FORM_H_INCLUDED
