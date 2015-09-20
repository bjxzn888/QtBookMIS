#ifndef QUERYBOOKDIALOG_H
#define QUERYBOOKDIALOG_H


#include <QDialog>
namespace Ui {
class QueryBookDialog;
}

class QueryBookDialog : public QDialog
{
    Q_OBJECT

public:
    explicit QueryBookDialog(QWidget *parent = 0);
    ~QueryBookDialog();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

signals:
    void dlgQuery(const QString &myISBN, const QString &bookName,
                  const QString &author, const QString &total,
                  const QString &loaned, const QString &remaining,
                  const QString &vote);

    void dlgBorrow(const QString &myISBN);

private:
    Ui::QueryBookDialog *ui;
    QString myISBN;
    QString bookName;
    QString author;
    QString total;
    QString loaned;
    QString remaining;
    QString vote;
};

#endif // QUERYBOOKDIALOG_H
