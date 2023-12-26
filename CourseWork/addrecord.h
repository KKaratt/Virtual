#ifndef ADDRECORD_H
#define ADDRECORD_H

#include <QWidget>
#include <QFileDialog>
#include <QBuffer>
#include <QMessageBox>
#include <QDebug>
#include "database.h"


namespace Ui {
class AddRecord;
}

class AddRecord : public QWidget
{
    Q_OBJECT

public:
    explicit AddRecord(QWidget *parent = nullptr);
    ~AddRecord();

private slots:
    void on_uploadPicture_clicked();

    void on_CancelButton_clicked();

    void on_SaveButton_clicked();

private:
    Ui::AddRecord *ui;
    DataBase* db;
    QString pathImage = "";


signals:
    void sendToWidget(const QByteArray &pic, const QString &title, const QString &place, const QString &price, const QString &telephone, const QString &description, const QString &password);
};

#endif // ADDRECORD_H
