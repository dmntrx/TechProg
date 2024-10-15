#include "functionsforserver.h"
#include <database.h>

int hash_func_name(const QString& func_name) {
    if (func_name == "auth") return 0;
    if (func_name == "reg") return 1;
    if (func_name == "check") return 2;
    if (func_name == "stat") return 3;
    return -1;
}

QByteArray auth(int socketDescr, QString log, QString pass) {
    if((log == "") || (pass == "")) {
        return "auth-";
    }
    SHA1 sha1;
    sha1.update(pass.toUtf8());
    QByteArray hashedPass = sha1.final();

    database *db = database::getInstance();
    return db -> auth(socketDescr, log, hashedPass);
}

QByteArray reg(QString log, QString pass, QString mail) {
    if((log == "") || (pass == "") || (mail == "")) {
        return "reg-";
    }
    SHA1 sha1;
    qDebug() << log << pass << mail;
    sha1.update(pass.toUtf8());
    QByteArray hashedPass = sha1.final();

    database *db = database::getInstance();
    return db ->reg(log, hashedPass, mail);
}




QByteArray check(int socketDescr, QString var, QString userAnsw) {

    return "check\r\n";
}

bool userDisconnect(int socketDescr) {
    database *db = database::getInstance();
    return db ->userDisconnect(socketDescr);
}

QByteArray parsing(int socketDescr, QString data_from_client) {
    // NameOfFunc&Param1&Param2&Param3 to NameOfFunc(param1,param2,param3)
    QStringList data_from_client_list = data_from_client.split(QLatin1Char('&'));
    qDebug() << data_from_client_list;

    if (data_from_client_list.size() < 2) {
        return "???";
    }

    QString func_name = data_from_client_list.first();
    data_from_client_list.removeFirst();

    switch (hash_func_name(func_name)) {
    case 0: // auth
        if (data_from_client_list.size()!= 2) {
            return "auth-";
        }
        return auth(socketDescr,data_from_client_list.at(0), data_from_client_list.at(1).trimmed());

    case 1: // reg
        if (data_from_client_list.size()!= 3) {
            return "reg-";
        }
        return reg(data_from_client_list.at(0), data_from_client_list.at(1), data_from_client_list.at(2).trimmed());

    case 2: // check
        if (data_from_client_list.size() != 2) {
            return "error";
        }

        return check(socketDescr, data_from_client_list.at(0), data_from_client_list.at(1).trimmed());

    default:
        return "There is no command with that syntax";
    }
}
