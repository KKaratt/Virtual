#include "pass_edit.h"
#include "ui_pass_edit.h"

pass_edit::pass_edit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::pass_edit)
{
    ui->setupUi(this);
}

pass_edit::~pass_edit()
{
    delete ui;
}

void pass_edit::on_OKPushButton_clicked()
{
    emit OKPushButton_clicked();
    ui->passLineEdit->clear();
}

void pass_edit::on_CancelPushButton_clicked()
{
    ui->passLineEdit->clear();
    close();
}

void pass_edit::on_passLineEdit_textEdited(const QString &arg1)
{
    pass_edit::m_userpass = arg1;
}

QString pass_edit::getPass()
{
    return pass_edit::m_userpass;
}
