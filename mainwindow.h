#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "manager.h"
#include "user.h"
#include "visitor.h"

#include <QMainWindow>
#include <QSqlTableModel>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void emitUser(const QString &textUser, const QString &textPassword);

private slots:
    void on_pushButtonLogIn_clicked();

    void on_pushButtonSignUp_clicked();

    void on_pushButtonVisitor_clicked();

//    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    Manager manager;
    User *userView;
    Visitor visitor;

    QSqlTableModel *model;
};

#endif // MAINWINDOW_H
