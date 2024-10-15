#include "singletonclient.h"
#include <functionsforclient.h>
#include "functionsforclient.h"


SingletonClient *SingletonClient::p_instance = nullptr;
SingletonDestroyer SingletonClient::destroyer;


SingletonClient::SingletonClient(QObject *parent) : QObject(parent)
{
    mTcpSocket = new QTcpSocket(this);
    mTcpSocket->connectToHost("127.0.0.1", 33333);

    connect(mTcpSocket, SIGNAL(readyRead()), this, SLOT(slotServerRead()));
    // FunctionsForClient functions;
    // mTcpSocket->waitForReadyRead();
    // slotServerRead();
}


SingletonClient* SingletonClient::getInstance()
{
    if (!p_instance)
    {
        p_instance = new SingletonClient();
        destroyer.initialize(p_instance);
    }
    return p_instance;
}

void SingletonClient::send_msg_to_server(QString log, QString pass)
{

    QString query = "auth&" + log + "&" + pass;
    qDebug() << query;
    mTcpSocket->write(query.toUtf8());
}


void SingletonClient::send_msg_to_server_reg(QString log, QString pass, QString email)
{

    QString query = "reg&" + log + "&" + pass + "&" + email;
    qDebug() << "authSending to server :" << query;
    mTcpSocket->write(query.toUtf8());
}

void SingletonClient::send_msg_to_server_check(QString task_number, QString first, QString second, QString answer)
{

    QString query = "check&" + task_number + "&" + first + "&" + second + "&" + answer;
    qDebug() << "authSending to server :" << query;
    mTcpSocket->write(query.toUtf8());
}



/*
QString SingletonClient::send_msg_to_server_check(QString task_number, QString first, QString second, QString answer)    // ked klikneme na task tak asi budeme potrebovat novu funkciu na poslanie
{                                                               // prosby na server task_number aby nam vygeneroval nejake random zadanie a vratil nam jeho parametre
    QString query = "check&" + task_number + "&" + first + "&" + second + "&" + answer;      // potom posielame check funkciu a pozerame ci dostaneme + alebo -
    mTcpSocket->write(query.toUtf8());      //okej, vyzera to tak ze generujeme random variant na kliente a posielame na back 3 argumenty + odpoved
    mTcpSocket->waitForReadyRead();
    return slotServerRead();
}
*/

QString SingletonClient::slotServerRead()
{
    //qDebug() << "slot\n";
    QString response = "";
    while(mTcpSocket->bytesAvailable() > 0)
    {
        QByteArray array = mTcpSocket->readAll();
        response.append(array);
    }


    qDebug() << "Сообщение до расшифровки"<< response;



    emit message_from_server(response);
    return response;
    //emit message_from_server(response);
}
