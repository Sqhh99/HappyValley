#include "loginwidget.h"
#include "ui_loginwidget.h"
#include <QFile>
#include <QMessageBox>
#include <QSettings>
#include "widget.h"
#include <QStyle>

LoginWidget::LoginWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginWidget)
{
    ui->setupUi(this);
    ui->passwordEidt->setEchoMode(QLineEdit::Password);
    readCredentials();
    setWindowTitle("用户登录");

    setFixedSize(this->width(),this->height());
}
void LoginWidget::saveCredentials(const QString& username, const QString& password) {
    // 使用 QSettings 保存用户名和密码
    QSettings settings("config.ini", QSettings::IniFormat);
    settings.setValue("username", username);
    settings.setValue("password", password);
}

void LoginWidget::readCredentials() {
    QSettings settings("config.ini", QSettings::IniFormat);
    QString savedUsername = settings.value("username").toString();
    QString savedPassword = settings.value("password").toString();

    // 如果存在保存的用户名和密码，更新输入框的内容
    if (!savedUsername.isEmpty() && !savedPassword.isEmpty()) {
        ui->accountEdit->setText(savedUsername);
        ui->passwordEidt->setText(savedPassword);
        ui->checkBox->setChecked(true);
    }
}

bool LoginWidget::readUserCredentials(const QString& username, const QString& password) {
    QFile file("user_credentials.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList tokens = line.split("\t");

            if (tokens.length() == 2) {
                QString storedUsername = tokens[0].mid(tokens[0].indexOf(":") + 1).trimmed();
                QString storedPassword = tokens[1].mid(tokens[1].indexOf(":") + 1).trimmed();

                if (storedUsername == username && storedPassword == password) {
                    file.close();
                    return true; // 用户验证成功
                }
            }
        }
        file.close();
    }

    return false; // 用户验证失败
}

LoginWidget::~LoginWidget()
{
    delete ui;
}

void LoginWidget::on_zhucBtn_clicked()
{
    QString username = ui->accountEdit->text();
    QString password = ui->passwordEidt->text();
    // 验证输入是否为空
    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "注册", "用户名和密码不能为空");
        return; // 不进行注册操作
    }

    QFile file("user_credentials.txt");
    if (file.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);
        out << "Username: " << username << "\tPassword: " << password << "\n";
        file.close();
    } else {
        QMessageBox::critical(this, "错误", "注册失败");
    }
    QMessageBox::information(this, "注册", "注册成功");
}
void LoginWidget::on_LoginBtn_clicked()
{
    QString username = ui->accountEdit->text();
    QString password = ui->passwordEidt->text();

    if (readUserCredentials(username, password)) {
        QMessageBox::information(this, "登录", "登录成功");

        //跳转窗口
        this->hide(); //  隐藏登录窗口
        Widget *t = new Widget;
        t->show(); //  显示子窗口

        //  接受信号
        connect(t,&Widget::testSignal,this,&LoginWidget::show);

        if (ui->checkBox->isChecked())
        {
            if (ui->checkBox->isChecked()) {
                saveCredentials(username, password);
            }
        }
    } else {
        QMessageBox::warning(this, "登录", "用户名或密码不正确");
    }

}


