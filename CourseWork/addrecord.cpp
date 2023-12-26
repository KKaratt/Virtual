#include "addrecord.h"
#include "ui_addrecord.h"

AddRecord::AddRecord(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddRecord)
{
    ui->setupUi(this);
    this->setMaximumSize(this->width(),this->height());
    this->setMinimumSize(this->width(),this->height());
}

AddRecord::~AddRecord()
{
    delete ui;
}

void AddRecord::on_uploadPicture_clicked()
{
    pathImage = QFileDialog::getOpenFileName(nullptr, "Выберите изображение", QDir::currentPath(), "*.png *.jpg *.gif *.jpeg *.webp");
    if (pathImage != ""){
        QImage image(pathImage);
        QPixmap pic = QPixmap::fromImage(image);
        ui->picture->setPixmap(pic);
        ui->picture->setPixmap(pic.scaled(ui->picture->width(),ui->picture->height(),Qt::KeepAspectRatio));
        ui->uploadPicture->setText("Изменить изображение");
    }

}

void AddRecord::on_CancelButton_clicked()
{

    ui->picture->clear();
    ui->picture->setText("Изображение\nотсутствует");
    ui->titleLineEdit->clear();
    ui->placeLineEdit->clear();
    ui->priceLineEdit->clear();
    ui->telephoneLineEdit->clear();
    ui->descriptionTextEdit->clear();
    ui->passwordLineEdit->clear();
    ui->uploadPicture->setText("Выберите изображение");
    pathImage = "";
    close();
}

void AddRecord::on_SaveButton_clicked()
{

    QString title = ui->titleLineEdit->text();
    if (title == ""){
       QMessageBox::information(nullptr, "Уведомление", "Заполните поле \"Название\"");
       return;
    }

    QString place = ui->placeLineEdit->text();
    if (place == ""){
       QMessageBox::information(nullptr, "Уведомление", "Заполните поле \"Место сделки\"");
       return;
    }
    QString price = ui->priceLineEdit->text();
    if (price == ""){
       QMessageBox::information(nullptr, "Уведомление", "Заполните поле \"Цена\"");
       return;
    }

    QString telephone = ui->telephoneLineEdit->text();
    if (telephone == ""){
       QMessageBox::information(nullptr, "Уведомление", "Заполните поле \"Телефон\"");
       return;
    }

    QString description = ui->descriptionTextEdit->toPlainText();
    if (description == ""){
       QMessageBox::information(nullptr, "Уведомление", "Заполните поле \"Описание\"");
       return;
    }

    QString password = ui->passwordLineEdit->text();
    if (password == ""){
       QMessageBox::information(nullptr, "Уведомление", "Введите пароль");
       return;
    }

    if (pathImage == ""){
       QMessageBox::information(nullptr, "Уведомление", "Загрузите изображение");
       return;
    }
    QPixmap inPixmap;
    inPixmap.load(pathImage);
    QByteArray inByteArray;
    QBuffer inBuffer( &inByteArray);
    inBuffer.open(QIODevice::WriteOnly);
    inPixmap.save(&inBuffer, "PNG");

    emit sendToWidget(inByteArray, title, place, price, telephone, description, password);
    QMessageBox::information(nullptr, "Уведомление", "Объявление размещено!");

    ui->picture->clear();
    ui->picture->setText("Изображение\nотсутствует");
    ui->titleLineEdit->clear();
    ui->placeLineEdit->clear();
    ui->priceLineEdit->clear();
    ui->telephoneLineEdit->clear();
    ui->descriptionTextEdit->clear();
    ui->passwordLineEdit->clear();
    ui->uploadPicture->setText("Выберите изображение");
    pathImage = "";
    close();


}
