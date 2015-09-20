#ifndef ADDBOOKDIALOG_H
#define ADDBOOKDIALOG_H

#include <QDialog>

namespace Ui {
class AddBookDialog;
}

class AddBookDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddBookDialog(QWidget *parent = 0);
    ~AddBookDialog();

signals:
    void dlgAdd(const QString &myAddISBN, const QString &addBookName,
                const QString &addAuthor, const QString &addTotal,
                const QString &addLoaned, const QString &addRemaining,
                const QString &addVote);

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::AddBookDialog *ui;
    QString myAddISBN;
    QString addBookName;
    QString addAuthor;
    QString addTotal;
    QString addLoaned;
    QString addRemaining;
    QString addVote;
};

#endif // ADDBOOKDIALOG_H
