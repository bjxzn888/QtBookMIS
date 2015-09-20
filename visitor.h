#ifndef VISITOR_H
#define VISITOR_H

#include "querybookdialog.h"
#include <QSqlTableModel>
#include <QMainWindow>

namespace Ui {
class Visitor;
}

class Visitor : public QMainWindow
{
    Q_OBJECT

public:
    explicit Visitor(QWidget *parent = 0);
    ~Visitor();

private slots:
    void on_pushButtonVisitor_clicked();
    void showValueVisitor(const QString &myISBN, const QString &bookName,
                       const QString &author, const QString &total,
                       const QString &loaned, const QString &remaining,
                       const QString &vote);

private:
    Ui::Visitor *ui;
    QueryBookDialog *queryBookDialog;
    QSqlTableModel *model;
};

#endif // VISITOR_H
