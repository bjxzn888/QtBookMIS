#ifndef MANAGER_H
#define MANAGER_H

#include "querybookdialog.h"
#include "addbookdialog.h"
#include "usersetdialog.h"

#include <QMainWindow>
#include <QSqlTableModel>

namespace Ui {
class Manager;
}

class Manager : public QMainWindow
{
    Q_OBJECT

public:
    explicit Manager(QWidget *parent = 0);
    ~Manager();

private slots:
    void on_pushButtonAdd_clicked();

    void on_pushButtonDelete_clicked();

    void on_pushButtonModify_clicked();

    void on_pushButtonQuery_clicked();

    void showValues(const QString &myISBN, const QString &bookName,
                    const QString &author, const QString &total,
                    const QString &loaned, const QString &remaining,
                    const QString &vote);

    void showAddValues(const QString &myAddISBN, const QString &addBookName,
                       const QString &addAuthor, const QString &addTotal,
                       const QString &addLoaned, const QString &addRemaining,
                       const QString &addVote);

    void showSetUser(const QString &userName, const QString &userOldPwd, const QString &userNewPwd);

    void updateAppointManager(const QString &myISBN);

    void on_pushButtonComment_clicked();

    void on_pushButtonVote_clicked();

    void on_pushButtonBorrow_clicked();

    void on_pushButtonSetManager_clicked();

private:
    Ui::Manager *ui;
    QSqlTableModel *model;
    QueryBookDialog queryBookDialog;
    AddBookDialog addBookDialog;
    UserSetDialog userSetDialog;
};

#endif // MANAGER_H
