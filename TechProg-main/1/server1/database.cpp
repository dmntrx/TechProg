#include "database.h"

/*
create table user_info(login varchar(20) NOT NULL,
                      pass varchar(64) NOT NULL,
                      mail varchar(64) NOT NULL,
                      id_conn int
                      stat_task1 integer
                      stat_task2 integer)

*/


database *database::p_instance = nullptr;
databaseDestroyer database::destroyer;



database::database() {
    db = QSqlDatabase::addDatabase("QSQLITE");
    // db.setDatabaseName("C:\\Users\\marys\\Desktop\\uni\\2 semester\\ТиМП\\1\\server1\\sqlite.db");
    db.setDatabaseName("C:\\Users\\marys\\Desktop\\uni\\2 semester\\ТиМП\\TechProg-main\\1\\server1\\sqlite.db");
    if (!db.open()) {
        qDebug() << "Error opening database: " << db.lastError().text();
    }
}

database* database::getInstance() {
    if (!p_instance) {
        p_instance = new database();
        destroyer.initialize(p_instance);
    }
    return p_instance;
}

QStringList database::sendQuerry(const QString& text, const QVariantList& queryParams)
{
    QSqlQuery query(db);
    query.prepare(text);

    for (int i = 0; i < queryParams.size(); ++i) {
        query.bindValue(i, queryParams.at(i));
    }

    if (!query.exec()) {
        qDebug() << "Error executing query: " << query.lastError().text();
        return QStringList(  );
    }

    QStringList results;
    while (query.next()) {
        QStringList row;
        for (int i = 0; i < query.record().count(); i++) {
            row << query.value(i).toString();
        }
        results << row.join("\t");
    }
    return results;
}

bool database::userDisconnect(int socketDescr) {
    return p_instance->sendQuerry("UPDATE user_info set id_conn = NULL where id_conn = ?", {socketDescr}).isEmpty();
}

bool database::isUserCorrect(QString log, int socketDescr) {
    return !p_instance -> sendQuerry("SELECT 1 FROM user_info WHERE login = ? AND id_conn = ?", {log, socketDescr}).isEmpty();
}

QByteArray database::reg(QString log, QString hashedPass, QString mail) {
    qDebug() << log << " " << hashedPass.toUtf8() << " " << mail;

    QStringList result = p_instance->sendQuerry("SELECT * FROM user_info WHERE login = ?", {log});

    if (!result.isEmpty()) {
        return "reg-";
    }

    p_instance->sendQuerry(
        "INSERT INTO user_info (login,pass,mail,id_conn) VALUES (?, ?, ?, NULL) ",
        {log, hashedPass.toUtf8(), mail});

    return "reg+";
}

QByteArray database::auth(int socketDescr, QString log, QString hashedPass) {

    QStringList result = p_instance->sendQuerry("SELECT * FROM user_info WHERE login = ?", {log});
    if (result.isEmpty()) {
        return "auth-";
    }

    result = p_instance->sendQuerry("SELECT * FROM user_info WHERE login = ? AND pass = ?", {log, hashedPass.toUtf8()});
    if (result.isEmpty()) {
        return "auth-";
    }

    p_instance->sendQuerry(
        "UPDATE user_info set id_conn = ? where login = ?",
        {socketDescr, log}
        );

    return "auth+";
}


bool database::update_task_1(const QString& log) {
    return true;
}

bool database::update_task_2(const QString& log) {
    return true;
}

