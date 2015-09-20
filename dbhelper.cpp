#include "dbhelper.h"
#include <QtSql>
#include <QMessageBox>
#include <iostream>

using namespace std;

DbHelper::DbHelper()
{

}

DbHelper::~DbHelper()
{

}

bool DbHelper::createDbTable()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("LibraryMaster.db");
    if (! db.open()) {
        QMessageBox::warning(NULL, "Cannot connect to database!", "Cannot connect to database!", QMessageBox::Cancel);
        return false;
    }

    QSqlQuery query(db);
    //test
    //query.exec(QString("DROP table books"));
//    query.exec(QString("DROP table users"));
    query.exec(QString("create table books (ISBN varchar(255) primary key not NULL,"
                            "name varchar(255) not NULL,"
                            "author varchar(255) not NULL,"
                            "numberAll int not NULL,"
                            "numberLoan int not NULL,"
                            "numberRemain int not NULL,"
                            "numberAppointment int not NULL,"
                            "vote int not NULL)"));
    query.exec(QString("create table users(id integer primary key autoincrement NOT NULL ,"
                       "name varchar(255) not null,"
                       "password varchar(255) not null,"
                       "isManager boolean not null,"
                       "comment varchar(255))"));
    query.exec(QString("insert into users values(1, 'admin', 'admin', 1, '')"));
    query.exec(QString("insert into books values('1', '狼图腾', '姜戎', 100, 20, 80, 0, 85)"));
    query.exec(QString("insert into books values('2', '简爱', '夏洛蒂·勃朗特', 100, 20, 80, 0, 86)"));
    query.exec(QString("insert into books values('3', '三体', '刘慈欣', 500, 100, 400, 0, 96)"));
    return true;
}

bool DbHelper::queryOne(const QString &textUser, const QString &textPwd)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("LibraryMaster.db");
    if (! db.open()) {
        QMessageBox::warning(NULL, "Cannot connect to database!", "Cannot connect to database!", QMessageBox::Cancel);
        return false;
    }
    QSqlQuery query(db);

    int numRows;
    query.exec(QString("select * from users where name = '"
                       + textUser + "' and password = '"
                       + textPwd + "'"));
    query.last();
    numRows = query.at() + 1;
    //have changed;
    if (numRows == 1) {
//        QMessageBox::warning(NULL, "Wrong!", "User not exist or password wrong!");
//        return false;
        return true;
    } else {
        QMessageBox::warning(NULL, "Wrong!", "User not exist or password wrong!");
        return false;
    }
}

bool DbHelper::addOne(const QString &textUser, const QString &textPwd)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("LibraryMaster.db");
    if (! db.open()) {
        QMessageBox::warning(NULL, "Cannot connect to database!", "Cannot connect to database!", QMessageBox::Cancel);
        return false;
    }
    QSqlQuery query(db);
    query.exec(QString("insert into users (name, password, isManager, comment) values('" + textUser + "','" + textPwd + "', 0, '')"));
    return true;
}

bool DbHelper::addOneBook(const QString &myAddISBN, const QString &addBookName,
                          const QString &addAuthor, const QString &addTotal,
                          const QString &addLoaned, const QString &addRemaining, const QString &addVote)
{
    bool ok = true;
    int total = addTotal.toInt(&ok, 10);
    int loaned = addLoaned.toInt(&ok, 10);
    int remaining = addRemaining.toInt(&ok, 10);
    int vote = addVote.toInt(&ok, 10);
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("LibraryMaster.db");
    if (! db.open()) {
        QMessageBox::warning(NULL, "Cannot connect to database!", "Cannot connect to database!", QMessageBox::Cancel);
        return false;
    }
    QSqlQuery query(db);
    query.exec(QString("insert into books "
                       "values('" + myAddISBN + "', '"
                       + addBookName + "', '"
                       + addAuthor + "', "
                       + QString::number(total) + ", "
                       + QString::number(loaned) + ", "
                       + QString::number(remaining) + ", 0 , "
                       + QString::number(vote) + ")"));
    return true;
}

bool DbHelper::updataManagerComment(const QString &textComment)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("LibraryMaster.db");
    if (!db.open()) {
        QMessageBox::warning(NULL, "Cannot connect to database!", "Cannot connect to database!", QMessageBox::Cancel);
        return false;
    }
    QSqlQuery query(db);
    query.exec(QString("update users set comment = '" + textComment + "'where name = 'admin'"));
    return true;
}

bool DbHelper::updataUserComment(const QString &textUser, const QString &textComment)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("LibraryMaster.db");
    if (!db.open()) {
        QMessageBox::warning(NULL, "Cannot connect to database!", "Cannot connect to database!", QMessageBox::Cancel);
        return false;
    }
    QSqlQuery query(db);
    query.exec(QString("update users set comment = '" + textComment + "' where name = '" + textUser + "'"));
    return true;
}

bool DbHelper::updataAppoint(const QString &myISBN)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("LibraryMaster.db");
    if (!db.open()) {
        QMessageBox::warning(NULL, "Cannot connect to database!", "Cannot connect to database!", QMessageBox::Cancel);
        return false;
    }
    QSqlQuery query(db);
    query.exec(QString("update books set numberAppointment = numberAppointment + 1 where ISBN = '" + myISBN + "'"));
    return true;
}

bool DbHelper::updataAppointManager(const QString &myISBN)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("LibraryMaster.db");
    if (!db.open()) {
        QMessageBox::warning(NULL, "Cannot connect to database!", "Cannot connect to database!", QMessageBox::Cancel);
        return false;
    }
    QSqlQuery query(db);
    query.exec(QString("update books set numberAppointment = numberAppointment - 1, numberLoan = numberLoan + 1,"
                       "numberRemain = numberRemain - 1 where ISBN = '" + myISBN + "'"));
    return true;
}

bool DbHelper::updataSetUser(const QString &userName, const QString &oldPwd, const QString &newPwd)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("LibraryMaster.db");
    if (!db.open()) {
        QMessageBox::warning(NULL, "Cannot connect to database!", "Cannot connect to database!", QMessageBox::Cancel);
        return false;
    }

    QSqlQuery query(db);
    query.exec(QString("select * from users where name = '"
                       + userName + "' and password = '"
                       + oldPwd + "'"));
    query.last();
    int numRows;
    numRows = query.at() + 1;
    if (numRows != 1) {
        QMessageBox::warning(NULL, "Wrong!", "User not exist or password wrong!");
        return false;
    } else {
        query.exec(QString("update users set password = '" + newPwd + "' where name = '" + userName + "'"));
        QMessageBox::information(NULL, "Success!", "Success!");
        return true;
    }
}

