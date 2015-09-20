#include "querybookdialog.h"
#include "ui_querybookdialog.h"
#include <QMessageBox>
#include <iostream>

using namespace std;

QueryBookDialog::QueryBookDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QueryBookDialog)
{
    ui->setupUi(this);
}

QueryBookDialog::~QueryBookDialog()
{
    delete ui;
}

void QueryBookDialog::on_buttonBox_accepted()
{
    myISBN = ui->lineEditISBN->text();
    bookName = ui->lineEditBookName->text();
    author = ui->lineEditAuthor->text();
    total = ui->lineEditTotal->text();
    loaned = ui->lineEditLoaned->text();
    remaining = ui->lineEditRemaining->text();
    vote = ui->lineEditVote->text();
    emit dlgQuery(myISBN, bookName, author, total, loaned, remaining, vote);
    emit dlgBorrow(myISBN);
}

void QueryBookDialog::on_buttonBox_rejected()
{
    this->reject();
}
