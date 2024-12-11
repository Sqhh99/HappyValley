#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QWidget>

namespace Ui {
class LoginWidget;
}

class LoginWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LoginWidget(QWidget *parent = nullptr);
    ~LoginWidget();

private slots:
    void on_zhucBtn_clicked();

    void on_LoginBtn_clicked();

private:
    Ui::LoginWidget *ui;
    bool readUserCredentials(const QString& username, const QString& password);

    void saveCredentials(const QString& username, const QString& password);

    void readCredentials();

};

#endif // LOGINWIDGET_H
