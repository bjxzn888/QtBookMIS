#include "manager.h"
#include "ui_manager.h"
#include "dbhelper.h"

#include <iostream>
#include <QMessageBox>
#include <QSqlError>

using namespace std;

Manager::Manager(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Manager)
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
    ui->tableView->setModel(model);
    connect(&userSetDialog, SIGNAL(userSet(QString,QString,QString)),
            this, SLOT(showSetUser(QString,QString,QString)));
}

Manager::~Manager()
{
    delete ui;
}


void Manager::on_pushButtonAdd_clicked()
{
    addBookDialog.show();
    connect(&addBookDialog, SIGNAL(dlgAdd(QString,QString,QString,QString,QString,QString,QString)),
            this, SLOT(showAddValues(QString,QString,QString,QString,QString,QString,QString)));
}

void Manager::on_pushButtonDelete_clicked()
{
    int curRow = ui->tableView->currentIndex().row();

    model->removeRow(curRow);
    int ok = QMessageBox::warning(this, tr("Delete current row!"), tr("Delete current row?"), QMessageBox::Yes, QMessageBox::No);
    if (ok == QMessageBox::Yes) {
        model->submitAll();
    } else {
        model->revertAll();
    }

    model->select();
    ui->tableView->setModel(model);
}

void Manager::on_pushButtonModify_clicked()
{
    model->database().transaction();
    if (model->submitAll()) {
        model->database().commit();
    } else {
        model->database().rollback();
        QMessageBox::warning(this, tr("tableModel!"), tr("database wrong:%1").arg(model->lastError().text()));
    }
}

void Manager::on_pushButtonQuery_clicked()
{
    queryBookDialog.show();
    connect(&queryBookDialog, SIGNAL(dlgQuery(QString,QString,QString,QString,QString,QString,QString)),
            this, SLOT(showValues(QString,QString,QString,QString,QString,QString,QString)));
}

void Manager::showValues(const QString &myISBN, const QString &bookName,
                         const QString &author, const QString &total,
                         const QString &loaned, const QString &remaining, const QString &vote)
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
    ui->tableView->setModel(model);
}

void Manager::showAddValues(const QString &myAddISBN, const QString &addBookName,
                            const QString &addAuthor, const QString &addTotal,
                            const QString &addLoaned, const QString &addRemaining, const QString &addVote)
{
    DbHelper *dbHelper = new DbHelper();
    dbHelper->addOneBook(myAddISBN, addBookName, addAuthor,
                        addTotal, addLoaned, addRemaining,addVote);
    model->select();
    ui->tableView->setModel(model);
}



void Manager::on_pushButtonComment_clicked()
{
    QString textComment = ui->plainTextEdit->toPlainText();
    DbHelper *dbHelper = new DbHelper();
    dbHelper->updataManagerComment(textComment);
}

void Manager::on_pushButtonVote_clicked()
{
    model->sort(7, Qt::DescendingOrder);
    model->select();
}

void Manager::on_pushButtonBorrow_clicked()
{
    if (QMessageBox::Yes ==  QMessageBox::warning(this, tr("Borrow?"),
                             tr("Borrow?"), QMessageBox::Yes, QMessageBox::No))
    {
        queryBookDialog.show();
        //code should be more perfect
        connect(&queryBookDialog, SIGNAL(dlgBorrow(QString)),
                this, SLOT(updateAppointManager(QString)));

        model->select();
        ui->tableView->setModel(model);
    }
}

void Manager::updateAppointManager(const QString &myISBN)
{
    DbHelper *dbHelper = new DbHelper();
    dbHelper->updataAppointManager(myISBN);

    model->select();
    ui->tableView->setModel(model);
}

void Manager::on_pushButtonSetManager_clicked()
{
    userSetDialog.show();
}


void Manager::showSetUser(const QString &userName, const QString &userOldPwd, const QString &userNewPwd)
{
    DbHelper *dbHelper = new DbHelper();
    dbHelper->updataSetUser(userName, userOldPwd, userNewPwd);
}
