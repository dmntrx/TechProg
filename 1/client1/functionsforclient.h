#ifndef FUNCTIONSFORCLIENT_H
#define FUNCTIONSFORCLIENT_H

#include "mainwindow.h"
#include "authregform.h"
#include "task_one.h"
#include <QObject>
#include "user_data.h"

#include <QVector>


class FunctionsForClient: public QObject
{
    Q_OBJECT
public:
    static void is_auth();
    static void on_reg();
    static void task_clicked(int i);
    static void return_to_menu();
    static void stat_clicked();
    static void send_clicked(int i);

    static void save_login(QString log);
    static QString return_login();

    // static QVector<UserData> return_user(); //

    FunctionsForClient();

signals:
    //void on_auth_ok();
private:
    static MainWindow *mainForm;
    static AuthRegForm * authregForm;
    static task_one *task;

    static QString login;
    // static QVector<UserData> users;  // took the vector out of the function, so i can return it and cout<< it out on admin screen

};


#endif // FUNCTIONSFORCLIENT_H
