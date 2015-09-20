#include "addbookdialog.h"
#include "ui_addbookdialog.h"

AddBookDialog::AddBookDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddBookDialog)
{
    ui->setupUi(this);
}

AddBookDialog::~AddBookDialog()
{
    delete ui;
}

void AddBookDialog::on_buttonBox_accepted()
{
    myAddISBN = ui->lineEditAddISBN->text();
    addBookName = ui->lineEditAddBookName->text();
    addAuthor = ui->lineEditAddAuthor->text();
    addTotal = ui->lineEditAddTotal->text();
    addLoaned = ui->lineEditAddLoaned->text();
    addRemaining = ui->lineEditAddRemaining->text();
    addVote = ui->lineEditAddVote->text();
    emit dlgAdd(myAddISBN, addBookName, addAuthor, addTotal, addLoaned, addRemaining, addVote);
}

void AddBookDialog::on_buttonBox_rejected()
{
    this->reject();
}
