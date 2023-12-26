#ifndef PASS_EDIT_H
#define PASS_EDIT_H

#include <QWidget>
#include <QMessageBox>

namespace Ui {
class pass_edit;
}

class pass_edit : public QWidget
{
    Q_OBJECT

public:
    explicit pass_edit(QWidget *parent = 0);
    ~pass_edit();
    QString getPass();

signals:
    void OKPushButton_clicked();

private slots:
    void on_OKPushButton_clicked();

    void on_CancelPushButton_clicked();

    void on_passLineEdit_textEdited(const QString &arg1);

private:
    Ui::pass_edit *ui;
    QString m_userpass;
    friend class mainwindow;
};

#endif // PASS_EDIT_H
