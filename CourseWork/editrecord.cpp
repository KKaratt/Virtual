#include "editrecord.h"
#include "ui_editrecord.h"

EditRecord::EditRecord(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EditRecord)
{
    ui->setupUi(this);
    this->setMaximumSize(this->width(),this->height());
    this->setMinimumSize(this->width(),this->height());
}

EditRecord::~EditRecord()
{
    delete ui;
}

void EditRecord::on_uploadPicture_clicked()
{
    pathImage = QFileDialog::getOpenFileName(nullptr, "Выберите изображение", QDir::currentPath(), "*.png *.jpg *.gif *.jpeg *.webp");
    if (pathImage != ""){
        QImage image(pathImage);
        QPixmap pic = QPixmap::fromImage(image);

        qDebug() << pathImage;

        QPixmap inPixmap;
        inPixmap.load(pathImage);
        QByteArray inByteArray;
        QBuffer inBuffer( &inByteArray);
        inBuffer.open(QIODevice::WriteOnly);
        inPixmap.save(&inBuffer, "PNG");

        savePic = inByteArray;
        ui->picture->setPixmap(pic);
        ui->picture->setPixmap(pic.scaled(ui->picture->width(),ui->picture->height(),Qt::KeepAspectRatio));
    }

}

void EditRecord::catchInfo(const int &id, const QByteArray &pic, const QString &title, const QString &place, const QString &price, const QString &telephone, const QString &description, const QString &password)
{
    this->id = id;
    ui->titleLineEdit->setText(title);
    ui->placeLineEdit->setText(place);
    ui->priceLineEdit->setText(price);
    ui->telephoneLineEdit->setText(telephone);
    ui->descriptionTextEdit->setText(description);
    ui->passwordLineEdit->setText(password);
    QPixmap img = QPixmap();
    savePic = pic;
    img.loadFromData(pic);
    ui->picture->setPixmap(img.scaled(ui->picture->width(),ui->picture->height(),Qt::KeepAspectRatio));
}


void EditRecord::on_CancelButton_clicked()
{
    this->close();
}

void EditRecord::on_SaveButton_clicked()
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

    QByteArray pic = savePic;
    emit sendToWidgetUpdate(id, pic, title, place, price, telephone, description, password);
    QMessageBox::information(nullptr, "Уведомление", "Объявление успешно изменено!");

    close();
}
