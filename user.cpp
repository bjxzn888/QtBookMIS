#include "user.h"
#include "ui_user.h"
#include "mainwindow.h"

#include <iostream>
#include <QMessageBox>

QString sUser;
using namespace std;

User::User(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::User)
{
    ui->setupUi(this);
    model = new QSqlTableModel(this);
    model->setTable("books");
    model->select();
    model->setHeaderData(0, Qt::Horizontal, tr("ISBN"));
    model->setHeaderData(1, Qt::Horizontal, tr("姓名"));
    model->setHeaderData(2, Qt::Horizontal, tr("作者"));
    model->setHeaderData(3, Qt::Horizontal, tr("总数"));
    model->setHeaderData(4, Qt::Horizontal, tr("已借"));
    model->setHeaderData(5, Qt::Horizontal, tr("剩余"));
    model->setHeaderData(6, Qt::Horizontal, tr("预约"));
    model->setHeaderData(7, Qt::Horizontal, tr("投票"));
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    ui->tableViewUser->setModel(model);
    connect(&userSetDialog, SIGNAL(userSet(QString,QString,QString)),
            this, SLOT(showSetUser(QString,QString,QString)));
}

User::~User()
{
    delete ui;
}

void User::on_pushButtonUserQuery_clicked()
{
    queryBookDialog.show();
    connect(&queryBookDialog, SIGNAL(dlgQuery(QString,QString,QString,QString,QString,QString,QString)),
            this, SLOT(showValueUser(QString,QString,QString,QString,QString,QString,QString)));
}

void User::showValueUser(const QString &myISBN, const QString &bookName, const QString &author, const QString &total, const QString &loaned, const QString &remaining, const QString &vote)
{
    bool ok = true;
    if (myISBN.toStdString() != "") {
        model->setFilter(QString("ISBN = '%1'").arg(myISBN));
    } else if (bookName.toStdString() != "") {
        model->setFilter(QString("name = '%1'").arg(bookName));
    } else if (author.toStdString() != "") {
        model->setFilter(QString("author = '%1'").arg(author));
    } else if (total.toStdString() != "") {
        model->setFilter(QString("numberAll = %1").arg(total.toInt(&ok, 10)));
    } else if (loaned.toStdString() != "") {
        model->setFilter(QString("numberLoan = %1").arg(loaned.toInt(&ok, 10)));
    } else if (remaining.toStdString() != "") {
        model->setFilter(QString("numberRemain = %1").arg(remaining.toInt(&ok, 10)));
    } else if (vote.toStdString() != "") {
        model->setFilter(QString("vote = %1").arg(vote.toInt(&ok, 10)));
    }
    model->select();
    ui->tableViewUser->setModel(model);
}

void User::on_pushButtonCommentUser_clicked()
{
    QString userComment = ui->plainTextEditUser->toPlainText();
    dbHelper->updataUserComment(sUser, userComment);
}

void User::showUser(const QString &textUser, const QString &textPassword)
{
    sUser = textUser;
}

void User::on_pushButtonAppointment_clicked()
{
    if (QMessageBox::Yes == QMessageBox::warning(this, tr("To appoint?"),
                            tr("Appoint a book?"), QMessageBox::Yes, QMessageBox::No))
    {
        //code should be more perfect;
        queryBookDialog.show();
        connect(&queryBookDialog, SIGNAL(dlgBorrow(QString)),
                this, SLOT(showISBNBorrow(QString)));
    }
}

void User::showISBNBorrow(const QString &myISBN)
{
    dbHelper->updataAppoint(myISBN);
    model->select();
    ui->tableViewUser->setModel(model);
}

void User::on_pushButtonSetUser_clicked()
{
    userSetDialog.show();
}

void User::on_pushButtonUserVote_clicked()
{
    model->sort(7, Qt::DescendingOrder);
    model->select();
}

void User::showSetUser(const QString &userName, const QString &oldPwd, const QString &newPwd)
{
    DbHelper *dbHelper = new DbHelper();
    dbHelper->updataSetUser(userName, oldPwd, newPwd);
}
