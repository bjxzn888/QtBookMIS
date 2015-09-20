#ifndef DBHELPER_H
#define DBHELPER_H

#include <QString>

class DbHelper
{
public:
    DbHelper();
    ~DbHelper();
    bool createDbTable();
    bool queryOne(const QString &textUser, const QString &textPwd);
    bool addOne(const QString &textUser, const QString &textPwd);
    bool addOneBook(const QString &myAddISBN, const QString &addBookName,
                    const QString &addAuthor, const QString &addTotal,
                    const QString &addLoaned, const QString &addRemaining,
                    const QString &addVote);
    bool updataManagerComment(const QString &textComment);
    bool updataUserComment(const QString &textUser, const QString &textComment);
    bool updataAppoint(const QString &myISBN);
    bool updataAppointManager(const QString &myISBN);
    bool updataSetUser(const QString &userName, const QString &oldPwd, const QString &newPwd);
};

#endif // DBHELPER_H
