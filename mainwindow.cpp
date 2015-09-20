#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dbhelper.h"

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEditPassword->setEchoMode(QLineEdit::Password);
    userView = new User(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonLogIn_clicked()
{
    QString user = ui->lineEditUser->text();
    QString pwd = ui->lineEditPassword->text();
    DbHelper *dbhelper = new DbHelper();

    if (user == "" || pwd == "") {
        QMessageBox::warning(NULL, tr("Warning!"), tr("User name and password cannot be null!"));
    } else if (dbhelper->queryOne(user, pwd)) {
        if (user == "admin") {
            QMessageBox::information(NULL, tr("Welcome!"), tr("Your are a manager!"));
            manager.show();
        } else {
            QMessageBox::information(NULL, tr("Welcome!"), tr("Your are a user!"));
            userView->show();
        }
    }
    connect(this, SIGNAL(emitUser(QString,QString)),
            userView, SLOT(showUser(QString,QString)));
    emit emitUser(user, pwd);
}

void MainWindow::on_pushButtonSignUp_clicked()
{
    QString user = ui->lineEditUser->text();
    QString pwd = ui->lineEditPassword->text();
    DbHelper *dbhelper = new DbHelper();

    if (user == "" || pwd == "") {
        QMessageBox::warning(NULL, tr("Warning!"), tr("User name and password cannot be null!"));
    } else if (dbhelper->queryOne(user, pwd)) {
        QMessageBox::warning(NULL, tr("Warning!"), tr("User name have exited!"));
    } else {
        if (dbhelper->addOne(user, pwd)){
            QMessageBox::information(NULL, tr("Welcome!"), tr("You have been a user!"));
            userView->show();
        } else {
            QMessageBox::warning(NULL, tr("Wrong!"), tr("Sorry, database wrong!"));
        }
        connect(this, SIGNAL(emitUser(QString,QString)),
                userView, SLOT(showUser(QString,QString)));
        emit emitUser(user, pwd);
    }
}

void MainWindow::on_pushButtonVisitor_clicked()
{
    QMessageBox::information(NULL, tr("Welcome!"), tr("You are a visitor!"));
    visitor.show();
}

////code for test;
//void MainWindow::on_pushButton_clicked()
//{
//    model = new QSqlTableModel(this);
//    model->setTable("users");
//    model->select();
//    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
//    ui->tableView->setModel(model);
//}
