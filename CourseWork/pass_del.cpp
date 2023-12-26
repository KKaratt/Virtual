#include "pass_del.h"
#include "ui_pass_del.h"

pass_del::pass_del(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::pass_del)
{
    ui->setupUi(this);
}

pass_del::~pass_del()
{
    delete ui;
}

void pass_del::on_OKPushButton_clicked()
{
    emit OKPushButton_clicked();
    ui->passLineEdit->clear();
}

void pass_del::on_CancelPushButton_clicked()
{
    ui->passLineEdit->clear();
    close();
}

void pass_del::on_passLineEdit_textEdited(const QString &arg1)
{
    pass_del::m_userpass = arg1;
}

QString pass_del::getPass()
{
    return pass_del::m_userpass;
}
