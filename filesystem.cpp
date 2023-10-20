#include "filesystem.h"

FileSystem::FileSystem()
{
    connectDB();
    QString str("hello");
    QString str1("你好");
    insertData(str,str1);
}

void FileSystem::connectDB()
{
    db=QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("management.db");
    if(db.open()){
        createTable();
    }
}

void FileSystem::createTable()
{
    QString sql = "CREATE TABLE customer(id INTEGER PRIMARY KEY,word TEXT,translation TEXT,occurrences REAL)";
    QSqlQuery sq;
    sq.exec(sql);
}

FileSystem* FileSystem::getInstance()
{
    static FileSystem* m_instance;
    if(m_instance==nullptr){
        m_instance=new FileSystem;
    }
    return m_instance;
}

bool FileSystem::insertData(QString &word,QString &translation)
{
    QSqlQuery sq;
    QString sql="INSERT INTO customer VALUES(?,?,?,?)";
    sq.prepare(sql);
    static int id=1;
    sq.addBindValue(QVariant(id++));//id相同会导致插入失败
    sq.addBindValue(QVariant(word));
    sq.addBindValue(QVariant(translation));
    sq.addBindValue(QVariant(0));
    if(sq.exec()){
        return true;
    }else{
        return false;
    }
}

void FileSystem::deleteData(QString &word)
{
    //假定元素中没有重复单词
    QSqlQuery sq;
    sq.exec("DELETE FROM customer where word='"+word+"'");
}

void FileSystem::deleteAll()
{
    QSqlQuery sq;
    sq.exec("DELETE FROM customer");
}

QList<QPair<QString,QString>> FileSystem::selectAll()
{
    QList<QPair<QString,QString>> t;
    QSqlQuery sq;
    sq.exec("SELECT * FROM customer");
    while(sq.next()){
        QPair<QString,QString>  h;
        h.first=sq.value(1).toString();
        h.second=sq.value(2).toString();
        t.push_back(h);
    };
    return t;
}
//使用时似乎有问题
bool FileSystem::isDataExists(QString &word)
{
    QSqlQuery sq;
    sq.exec("SELECT * FROM customer where word='"+word+"'");
    return sq.size()==1;
}
