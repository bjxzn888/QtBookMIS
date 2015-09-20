#ifndef USER_H
#define USER_H

#include "querybookdialog.h"
#include "dbhelper.h"
#include "usersetdialog.h"
#include <QMainWindow>
#include <QSqlTableModel>

namespace Ui {
class User;
}

class User : public QMainWindow
{
    Q_OBJECT

public:
    explicit User(QWidget *parent = 0);
    ~User();

private slots:
    void on_pushButtonUserQuery_clicked();

    void showValueUser(const QString &myISBN, const QString &bookName,
                       const QString &author, const QString &total,
                       const QString &loaned, const QString &remaining,
                       const QString &vote);

    void showSetUser(const QString &userName, const QString &oldPwd, const QString &newPwd);

    void on_pushButtonCommentUser_clicked();
    void showUser(const QString &textUser, const QString &textPassword);

    void showISBNBorrow(const QString &myISBN);

    void on_pushButtonAppointment_clicked();

    void on_pushButtonSetUser_clicked();

    void on_pushButtonUserVote_clicked();

private:
    Ui::User *ui;
    QueryBookDialog queryBookDialog;
    QSqlTableModel *model;
    DbHelper *dbHelper;
    UserSetDialog userSetDialog;
};

#endif // USER_H
