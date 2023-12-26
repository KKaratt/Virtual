#include "database.h"

DataBase::DataBase(QObject *parent) : QObject(parent)
{

}

DataBase::~DataBase()
{

}

/* Методы для подключения к базе данных
 * */
void DataBase::connectToDataBase()
{
    /* Перед подключением к базе данных производим проверку на её существование.
     * В зависимости от результата производим открытие базы данных или её восстановление
     * */
    if(!QFile(DATABASE_NAME).exists()){
        this->restoreDataBase();
    } else {
        this->openDataBase();
    }
}

/* Методы восстановления базы данных
 * */
bool DataBase::restoreDataBase()
{
    if(this->openDataBase()){
        if(!this->createTable()){
            return false;
        } else {
            return true;
        }
    } else {
        qDebug() << "Не удалось восстановить базу данных";
        return false;
    }
}

/* Метод для открытия базы данных
 * */
bool DataBase::openDataBase()
{
    /* База данных открывается по заданному пути
     * и имени базы данных, если она существует
     * */
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(DATABASE_NAME);
    if(db.open()){
        return true;
    } else {
        return false;
    }
}

/* Методы закрытия базы данных
 * */
void DataBase::closeDataBase()
{
    db.close();
}

/* Метод для создания таблицы в базе данных
 * */
bool DataBase::createTable()
{
    /* В данном случае используется формирование сырого SQL-запроса
     * с последующим его выполнением.
     * */
    QSqlQuery query;
//    TABLE_ID    " INTEGER PRIMARY KEY AUTOINCREMENT, "
//    TABLE_PICTURE       " BLOB            NOT NULL,"
//    TABLE_NAME          " TINYTEXT        NOT NULL,"
//    TABLE_AUTHOR        " TINYTEXT        NOT NULL,"
//    TABLE_RELEASE_YEAR  " SMALLINT        NOT NULL,"

//    TABLE_DESCRIPTION   " TEXT            NOT NULL,"
//    TABLE_TYPE          " TINYINT         NOT NULL,"
//    TABLE_GENRES        " TEXT            NOT NULL,"

//    TABLE_VIEWDATE      "DATE             NOT NULL,"
//    TABLE_SCORE         "TINYINT          NOT NULL,"
//    TABLE_COMMENT       "TEXT             NOT NULL"
    if(!query.exec( "CREATE TABLE " TABLE " ("
                            TABLE_ID " INTEGER PRIMARY KEY AUTOINCREMENT, "
                            TABLE_PICTURE       " BLOB            NOT NULL,"
                            TABLE_TITLE         " TINYTEXT        NOT NULL,"
                            TABLE_PLACE         " TINYTEXT        NOT NULL,"
                            TABLE_PRICE         " TINYTEXT        NOT NULL,"
                            TABLE_TELEPHONE     " TINYTEXT        NOT NULL,"
                            TABLE_DESCRIPTION   " TEXT            NOT NULL,"
                            TABLE_PASSWORD      " TINYTEXT        NOT NULL"
                        " )"
                    )){
        qDebug() << "DataBase: error of create " << TABLE;
        qDebug() << query.lastError().text();
        return false;
    } else {
        return true;
    }
}

/* Метод для вставки записи в базу данных
 * */
bool DataBase::insertIntoTable(const QByteArray &pic, const QString &title, const QString &place, const QString &price, const QString &telephone, const QString &description, const QString &password)
{

    QSqlQuery query;

    query.prepare("INSERT INTO " TABLE " ( "
                                  TABLE_PICTURE ", "
                                  TABLE_TITLE ", "
                                  TABLE_PLACE ", "
                                  TABLE_PRICE ", "
                                  TABLE_TELEPHONE ", "
                                  TABLE_DESCRIPTION ", "
                                  TABLE_PASSWORD " ) "
                    "VALUES (:Pic, :Title, :Place, :Price, :Telephone, :Description, :Password)");

    query.bindValue(":Pic", pic);
    query.bindValue(":Title", title);
    query.bindValue(":Place", place);
    query.bindValue(":Price", price);
    query.bindValue(":Telephone", telephone);
    query.bindValue(":Description", description);
    query.bindValue(":Password", password);

    // После чего выполняется запросом методdом exec()QQQ
    if(!query.exec()){
        qDebug() << "error insert into " << TABLE;
        qDebug() << query.lastError().text();
        return false;
    } else {
        return true;
    }
}

bool DataBase::editInTable(const int &id, const QByteArray &pic, const QString &title, const QString &place, const QString &price, const QString &telephone, const QString &description, const QString &password)
{
    QSqlQuery query(db);

    query.prepare("UPDATE " TABLE " SET "
                              TABLE_PICTURE         "=:Pic, "
                              TABLE_TITLE           "=:Title, "
                              TABLE_PLACE           "=:Place, "
                              TABLE_PRICE           "=:Price, "
                              TABLE_TELEPHONE       "=:Telephone, "
                              TABLE_DESCRIPTION     "=:Description, "
                              TABLE_PASSWORD        "=:Password "
                            "WHERE " TABLE_ID "=:Id");


    query.bindValue(":Pic", pic);
    query.bindValue(":Title", title);
    query.bindValue(":Place", place);
    query.bindValue(":Price", price);
    query.bindValue(":Telephone", telephone);
    query.bindValue(":Description", description);
    query.bindValue(":Password", password);
    query.bindValue(":Id",     id);
    if(!query.exec()){
        qDebug() << "ERROR: Can't edit record in table " << TABLE;
        qDebug() << query.lastError().text();
        return false;
    }
    else
        return true;

}

bool DataBase::deleteFromDatabase(const int id)
{
    QSqlQuery query(db);

    query.prepare("DELETE FROM " TABLE " WHERE " TABLE_ID "= :ID ;");
    query.bindValue(":ID", id);

    if(!query.exec()){
        qDebug() << "ERROR: Can't delete from table " << TABLE;
        qDebug() << query.lastError().text();
        return false;
    } else {
        return true;
    }


}
