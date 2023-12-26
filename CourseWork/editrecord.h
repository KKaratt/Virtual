#ifndef EDITRECORD_H
#define EDITRECORD_H

#include <QWidget>
#include <QFileDialog>
#include <QMessageBox>
#include <QBuffer>
#include <QDebug>

namespace Ui {
class EditRecord;
}

class EditRecord : public QWidget
{
    Q_OBJECT

public:
    explicit EditRecord(QWidget *parent = nullptr);
    ~EditRecord();
public slots:
    void catchInfo(const int &id, const QByteArray &pic, const QString &title, const QString &place, const QString &price, const QString &telephone, const QString &description, const QString &password);

private slots:
    void on_uploadPicture_clicked();

    void on_CancelButton_clicked();

    void on_SaveButton_clicked();

signals:
    void sendToWidgetUpdate(const int &id, const QByteArray &pic, const QString &title, const QString &place, const QString &price, const QString &telephone, const QString &description, const QString &password);
private:
    Ui::EditRecord *ui;
    QString pathImage;
    QByteArray savePic;
    int id;
};

#endif // EDITRECORD_H
