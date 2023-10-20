#ifndef FILESYSTEM_H
#define FILESYSTEM_H
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>
class FileSystem
{
private:
    FileSystem();
    QSqlDatabase db;
    void connectDB();
    void createTable();
public:
    static FileSystem* getInstance();
    bool insertData(QString &word,QString &translation);
    void deleteData(QString &word);
    void deleteAll();
    QList<QPair<QString,QString>> selectAll();
    bool isDataExists(QString &word);
};

#endif // FILESYSTEM_H
