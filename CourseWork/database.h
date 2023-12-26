#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QSql>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDatabase>
#include <QFile>
#include <QDate>
#include <QDebug>

/* Директивы имен таблицы, полей таблицы и базы данных */
#define DATABASE_NAME           "DataBase.db"

#define TABLE                   "Ads"

#define TABLE_ID                "_id"
#define TABLE_PICTURE           "Picture"

#define TABLE_TITLE             "Title"
#define TABLE_PLACE             "Place"
#define TABLE_PRICE             "Price"
#define TABLE_TELEPHONE         "Telephone"
#define TABLE_DESCRIPTION       "Description"

#define TABLE_PASSWORD          "Password"

class DataBase : public QObject
{
    Q_OBJECT
public:
    explicit DataBase(QObject *parent = nullptr);
    ~DataBase();
    /* Методы для непосредственной работы с классом
     * Подключение к базе данных и вставка записей в таблицу
     * */
    void connectToDataBase();
    bool insertIntoTable(const QByteArray &pic, const QString &title, const QString &place, const QString &price, const QString &telephone, const QString &description, const QString &password);
    bool editInTable(const int &id, const QByteArray &pic, const QString &title, const QString &place, const QString &price, const QString &telephone, const QString &description, const QString &password);
    bool deleteFromDatabase(const int id);
private:
    // Сам объект базы данных, с которым будет производиться работа
    QSqlDatabase    db;

private:
    /* Внутренние методы для работы с базой данных
     * */
    bool openDataBase();
    bool restoreDataBase();
    void closeDataBase();
    bool createTable();
};

#endif // DATABASE_H
