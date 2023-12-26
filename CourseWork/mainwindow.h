#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QSqlTableModel>
#include <QDebug>

#include "addrecord.h"
#include "editrecord.h"
#include "helpinformation.h"
#include "database.h"
#include "pass_edit.h"
#include "pass_del.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void saveSettings();
    void loadSettings();

public slots:
    void slotAdd();
    void slotEdit();
    void slotDel();
    void slotInfo();
    void slotAbout();
    void updateTable();
    void passVerifEdit();
    void passVerifDel();
    void addRecordDataBase(const QByteArray &pic, const QString &title, const QString &place, const QString &price, const QString &telephone, const QString &description, const QString &password);
    void editRecordDataBase(const int &id, const QByteArray &pic, const QString &title, const QString &place, const QString &price, const QString &telephone, const QString &description, const QString &password);

signals:
    void sendForEdit(const int &ip, const QByteArray &pic, const QString &title, const QString &place, const QString &price, const QString &telephone, const QString &description, const QString &password);

private slots:
    void on_tableView_clicked(const QModelIndex &index);

    void on_lineEdit_returnPressed();

private:
    Ui::MainWindow *ui;
    AddRecord  *addForm;
    EditRecord *editForm;
    pass_edit passEdit;
    QString m_userpass_edit;
    pass_del passDel;
    QString m_userpass_del;

    DataBase* db;
    QSqlTableModel *model;
    int currRow = -1;
    int currID = -1;
};

#endif // MAINWINDOW_H
