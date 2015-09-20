#include "usersetdialog.h"
#include "ui_usersetdialog.h"

UserSetDialog::UserSetDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UserSetDialog)
{
    ui->setupUi(this);
    ui->lineEdidOldPwd->setEchoMode(QLineEdit::Password);
    ui->lineEditNewPwd->setEchoMode(QLineEdit::Password);
}

UserSetDialog::~UserSetDialog()
{
    delete ui;
}

void UserSetDialog::on_buttonBox_accepted()
{
    QString userName = ui->lineEditUserNameSet->text();
    QString oldPwd = ui->lineEdidOldPwd->text();
    QString newPwd = ui->lineEditNewPwd->text();
    emit userSet(userName, oldPwd, newPwd);
    accept();
}

void UserSetDialog::on_buttonBox_rejected()
{
    reject();
}
