#include <QIntValidator>
#include <QDebug>

#include "include/form.h"
#include "ui_form.h"



Form::Form(QWidget *parent) : QWidget(parent),  ui(new Ui::Form),
    table(653267)
{
    ui->setupUi(this);
    ui->numberGenerateEdit->setValidator(new QIntValidator(0, std::numeric_limits<int>::max(),
                                                           ui->numberGenerateEdit));
    ui->label->setBuddy(ui->homiesTextArea);
    ui->splitter->setStretchFactor(0, 3);
    ui->splitter->setStretchFactor(1, 1);
}



Form::~Form()
{
    dumpObjectTree();
    delete ui;
}



void Form::on_generateButton_clicked()
{
    QVector<QString> homies;
    ui->homiesTextArea->textCursor().
    for (;;) {

    }



}
