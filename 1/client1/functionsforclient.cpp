#include "functionsforclient.h"
#include <QRegularExpression>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>


MainWindow * FunctionsForClient::mainForm;
AuthRegForm * FunctionsForClient::authregForm;
task_one * FunctionsForClient::task;

QString FunctionsForClient::login;

// QVector<UserData> FunctionsForClient::users;

FunctionsForClient::FunctionsForClient() {
    authregForm = new AuthRegForm();
    authregForm->show();
    mainForm = new MainWindow();
}

void FunctionsForClient::is_auth()
{
    //return client::sendmsg("auth&"+log+"&"+pass);

        authregForm->close();
        mainForm->show();


    //authregForm->showerr();

}

void FunctionsForClient::save_login(QString log)
{
    login = log;
}

QString FunctionsForClient::return_login()
{
    return login;
}

void FunctionsForClient::return_to_menu()
{
    task->hide();
    mainForm->show();
}

void FunctionsForClient::task_clicked(int i)
{
    mainForm->hide();
    if(task==nullptr)
        task =new task_one();
    task->set_task_number(i);
    task->show();
}

void FunctionsForClient::stat_clicked()
{
    mainForm->hide();
    if(task==nullptr)
        task =new task_one();
    task->set_task_stat();
    task->show();
}

void FunctionsForClient::send_clicked(int i)
{
    task->check_plus(i);
}



