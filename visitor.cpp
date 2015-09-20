#include "visitor.h"
#include "ui_visitor.h"

Visitor::Visitor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Visitor)
{
    ui->setupUi(this);
    queryBookDialog = new QueryBookDialog();
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
}

Visitor::~Visitor()
{
    delete ui;
}

void Visitor::on_pushButtonVisitor_clicked()
{
    queryBookDialog->show();
    connect(queryBookDialog, SIGNAL(dlgQuery(QString,QString,QString,QString,QString,QString,QString)),
            this, SLOT(showValueVisitor(QString,QString,QString,QString,QString,QString,QString)));

}

void Visitor::showValueVisitor(const QString &myISBN, const QString &bookName, const QString &author, const QString &total, const QString &loaned, const QString &remaining, const QString &vote)
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
    ui->tableViewVisitor->setModel(model);
}
