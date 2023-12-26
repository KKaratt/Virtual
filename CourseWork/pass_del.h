#ifndef PASS_DEL_H
#define PASS_DEL_H

#include <QWidget>
#include <QMessageBox>

namespace Ui {
class pass_del;
}

class pass_del : public QWidget
{
    Q_OBJECT

public:
    explicit pass_del(QWidget *parent = 0);
    ~pass_del();
    QString getPass();

signals:
    void OKPushButton_clicked();

private slots:
    void on_OKPushButton_clicked();

    void on_CancelPushButton_clicked();

    void on_passLineEdit_textEdited(const QString &arg1);

private:
    Ui::pass_del *ui;
    QString m_userpass;
    friend class mainwindow;
};

#endif // PASS_DEL_H
