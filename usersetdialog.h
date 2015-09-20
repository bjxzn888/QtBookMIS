#ifndef USERSETDIALOG_H
#define USERSETDIALOG_H

#include <QDialog>

namespace Ui {
class UserSetDialog;
}

class UserSetDialog : public QDialog
{
    Q_OBJECT

public:
    explicit UserSetDialog(QWidget *parent = 0);
    ~UserSetDialog();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

signals:
    void userSet(const QString &userName, const QString &userOldPwd, const QString &userNewPwd);

private:
    Ui::UserSetDialog *ui;
};

#endif // USERSETDIALOG_H
