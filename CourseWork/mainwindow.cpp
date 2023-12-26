#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QLabel>
#include "QSettings"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setMaximumSize(this->width(),this->height());
    this->setMinimumSize(this->width(),this->height());

    db = new DataBase();
    db->connectToDataBase();

    model = new QSqlTableModel;
    model->setTable(TABLE);
    model->setHeaderData(0, Qt::Horizontal, "id");

    ui->tableView->setModel(model);
    ui->tableView->setColumnHidden(0, true);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);

    updateTable();

    editForm = new EditRecord();
    editForm->setWindowModality(Qt::ApplicationModal);
    addForm = new AddRecord();
    addForm->setWindowModality(Qt::ApplicationModal);

    connect(addForm, SIGNAL(sendToWidget(QByteArray, QString, QString, QString, QString, QString, QString)), this, SLOT(addRecordDataBase(QByteArray, QString, QString, QString, QString, QString, QString)));
    connect(this, SIGNAL(sendForEdit(int, QByteArray, QString, QString, QString, QString, QString, QString)), editForm, SLOT(catchInfo(int, QByteArray, QString, QString, QString, QString, QString, QString)));
    connect(editForm, SIGNAL(sendToWidgetUpdate(int, QByteArray, QString, QString, QString, QString, QString, QString)), this, SLOT(editRecordDataBase(int, QByteArray, QString, QString, QString, QString, QString, QString)));

    connect(ui->menu1_add_record,  SIGNAL(triggered()), this, SLOT(slotAdd()));
    connect(ui->addButton,         SIGNAL(clicked()), this, SLOT(slotAdd()));
    connect(ui->menu1_edit_record, SIGNAL(triggered()), this, SLOT(passVerifEdit()));
    connect(ui->editButton,        SIGNAL(clicked()), this, SLOT(passVerifEdit()));
    connect(&passEdit,             SIGNAL(OKPushButton_clicked()), this, SLOT(slotEdit()));
    connect(ui->menu1_del_record,  SIGNAL(triggered()), this, SLOT(passVerifDel()));
    connect(ui->delButton,         SIGNAL(clicked()), this, SLOT(passVerifDel()));
    connect(&passDel,              SIGNAL(OKPushButton_clicked()), this, SLOT(slotDel()));
    connect(ui->menu1_exit,        SIGNAL(triggered()), qApp, SLOT(quit()));
    connect(ui->menu2_help,        SIGNAL(triggered()), this, SLOT(slotInfo()));
    connect(ui->menu2_about,       SIGNAL(triggered()), this, SLOT(slotAbout()));

    loadSettings();
}


MainWindow::~MainWindow()
{
    saveSettings();
    delete ui;
}

void MainWindow::updateTable(){
        currRow = -1;
        currID = -1;
        model->select();
        model->setSort(8,Qt::AscendingOrder);
        if (currRow == -1){
            ui->menu1_edit_record->setEnabled(false);
            ui->menu1_del_record->setEnabled(false);
            ui->editButton->setEnabled(false);
            ui->delButton->setEnabled(false);
        }
        else{
            ui->menu1_edit_record->setEnabled(true);
            ui->menu1_del_record->setEnabled(true);
            ui->editButton->setEnabled(true);
            ui->delButton->setEnabled(true);
        }
        if (model->rowCount() == 0){
            ui->label->show();
            ui->tableView->hide();
            return;
        }
         ui->label->hide();
         ui->tableView->show();
         QPixmap pic = QPixmap();
        for (int i = 0; i < model->rowCount(); i++){
            pic.loadFromData(model->data(model->index(i, 1)).toByteArray());
            QLabel *imageLabel = new QLabel();
            imageLabel->setPixmap(pic.scaled(150, 400, Qt::KeepAspectRatio));
            ui->tableView->setIndexWidget(model->index(i, 1), imageLabel);
        }
        ui->tableView->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
        ui->tableView->horizontalHeader()->setSectionResizeMode(2, QHeaderView::ResizeToContents);
        ui->tableView->horizontalHeader()->setSectionResizeMode(3, QHeaderView::ResizeToContents);
        ui->tableView->horizontalHeader()->setSectionResizeMode(4, QHeaderView::ResizeToContents);
        ui->tableView->horizontalHeader()->setSectionResizeMode(5, QHeaderView::ResizeToContents);
        ui->tableView->horizontalHeader()->setSectionResizeMode(6, QHeaderView::Stretch);
        ui->tableView->horizontalHeader()->hideSection(7);

        ui->tableView->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
        ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void MainWindow::slotAdd(){
    addForm->show();
 }

void MainWindow::addRecordDataBase(const QByteArray &pic, const QString &title, const QString &place, const QString &price, const QString &description, const QString &telephone, const QString &password)
{
    db->insertIntoTable(pic, title, place, price, description, telephone, password);
    updateTable();
    currRow = -1;
    currID = -1;
}

void MainWindow::passVerifEdit()
{
    passEdit.show();
}

void MainWindow::slotEdit()
{
    m_userpass_edit = passEdit.getPass();
    QString userpass = model->data(model->index(currRow, 7)).toString();
    qDebug() << "m_userpass: " << m_userpass_edit;
    qDebug() << "userpass: " << userpass;
    if(m_userpass_edit != userpass)
    {
        QMessageBox::warning(nullptr, "Ошибка", "Введен неверный пароль");
    }
    else{
        passEdit.close();
        if(currRow != -1)
        {
            QString title = model->data(model->index(currRow, 2)).toString();
            QString place = model->data(model->index(currRow, 3)).toString();
            QString price =  model->data(model->index(currRow, 4)).toString();
            QString telephone =  model->data(model->index(currRow, 5)).toString();
            QString description = model->data(model->index(currRow, 6)).toString();
            QString password = model->data(model->index(currRow, 7)).toString();

            QByteArray inByteArray = model->data(model->index(currRow, 1)).toByteArray();
            emit sendForEdit(currID, inByteArray, title, place, price, telephone, description, password);
            editForm->show();
        }
    }
}

void MainWindow::editRecordDataBase(const int &id, const QByteArray &pic, const QString &title, const QString &place, const QString &price, const QString &telephone, const QString &description, const QString &password)
{
    currRow = -1;
    currID = -1;
    db->editInTable(id,pic, title, place, price, telephone, description, password);
    updateTable();
}

void MainWindow::passVerifDel()
{
    passDel.show();
}

void MainWindow::slotDel()
{
//    int n = QMessageBox::warning(0,
//                                 "Удаление",
//                                 "Вы действительно хотите удалить запись?",
//                                 "Да",
//                                 "Нет",
//                                 QString(),
//                                 0,
//                                 1
//                                );
//    if(!n) {
    //    }
    m_userpass_del = passDel.getPass();
    QString userpass = model->data(model->index(currRow, 7)).toString();
    qDebug() << "m_userpass: " << m_userpass_del;
    qDebug() << "userpass: " << userpass;
    if(m_userpass_del != userpass)
    {
        QMessageBox::warning(nullptr, "Ошибка", "Введен неверный пароль");
    }
    else
    {
        passDel.close();
        if(currRow != -1)
        {
            db->deleteFromDatabase(currID);
            updateTable();
            QMessageBox::information(nullptr, "Уведомление", "Объявление успешно удалено");
            currRow = -1;
            currID = -1;
        }
    }
}


void MainWindow::slotInfo(){
    HelpInformation* form = new HelpInformation();
    form->setWindowModality(Qt::ApplicationModal);
    form->show();
}


void MainWindow::slotAbout(){
    QMessageBox::about(this, "О программе", "Версия: 0.0.1 Alpha\n\nРазработчик: Третьяков Матвей, ИП-117\n\n            © 2023-2024 уч.год, СибГУТИ");
}

void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    ui->menu1_edit_record->setEnabled(true);
    ui->menu1_del_record->setEnabled(true);
    ui->editButton->setEnabled(true);
    ui->delButton->setEnabled(true);
    currID = model->data(model->index(index.row(), 0)).toInt();
    currRow = index.row();
}

void MainWindow::on_lineEdit_returnPressed()
{
    QString search = ui->lineEdit->text();
    model->setFilter("Title LIKE '%"+search+"%'");
    model->select();
    ui->editButton->setDisabled(true);
    ui->delButton->setDisabled(true);
    QPixmap pic = QPixmap();
    for (int i = 0; i < model->rowCount(); i++){
        pic.loadFromData(model->data(model->index(i, 1)).toByteArray());
        QLabel *imageLabel = new QLabel();
        imageLabel->setPixmap(pic.scaled(150, 400, Qt::KeepAspectRatio));
        ui->tableView->setIndexWidget(model->index(i, 1), imageLabel);
    }
}

void MainWindow::saveSettings(){
    QSettings settings("MySoft", "CorseWork");
    settings.setValue("current_id", this->currID);
    settings.setValue("currRow", this->currRow);
}

void MainWindow::loadSettings(){
    QSettings settings("MySoft", "CorseWork");
    ui->editButton->setEnabled(true);
    ui->delButton->setEnabled(true);
    currID = settings.value("current_id").toInt();
    currRow = settings.value("currRow").toInt();
    QModelIndex index = model->index(currRow, 0);
    ui->tableView->setCurrentIndex(index);
    //settings.setValue("current_id", this->currID);
}
