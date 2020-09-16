#include "database.h"
#include <QDebug>


database::database(QObject *parent) : QObject(parent)
{
    QSqlDatabase conn = QSqlDatabase::addDatabase("QPSQL");
    this->conn = conn;
}

void database::setDBname(QString dbName)
{
    this->conn.close();
    this->conn.setDatabaseName(dbName);
    setDBName_QSetting(dbName);
    this->conn.open();
}

void database::writeServerSettings(QString host, QString port , QString user, QString pass)
{
    QSettings settings("DUPONT", "RBIMS");
    settings.beginGroup("Database");
    settings.setValue("host", host);
    settings.setValue("port", port);
    settings.setValue("user", user);
    settings.setValue("pass", pass);
    settings.endGroup();
}

bool database::openConn(bool withDbName)
{
    readServerSettings(withDbName);
    return this->conn.open();
}

void database::clearSettings()
{
    QSettings settings("DUPONT", "RBIMS");
    settings.beginGroup("Database");
    settings.clear();
    settings.endGroup();
}

bool database::doBDQuery(QString theQuery)
{
    QSqlQuery query;
    query.prepare(theQuery);
    if (query.exec()) return true;
    return false;
}

void database::readServerSettings(bool includeDBName)
{
    QSettings settings("DUPONT", "RBIMS");
    settings.beginGroup("Database");
    this->conn.setHostName(settings.value("host").toString());
    this->conn.setPort(settings.value("port").toInt());
    this->conn.setUserName(settings.value("user").toString());
    this->conn.setPassword(settings.value("pass").toString());
    if (includeDBName) {
        this->conn.setDatabaseName("rbims");
    }
    settings.endGroup();
}


void database::setDBName_QSetting(QString dbName)
{
    QSettings settings("DUPONT", "rbims");
    settings.beginGroup("Database");
    settings.setValue("dbName", dbName);
    settings.endGroup();
}

bool database::connectToServer(QString host, QString port, QString user, QString pass)
{
    this->conn.setHostName(host);
    this->conn.setPort(port.toInt());
    this->conn.setUserName(user);
    this->conn.setPassword(pass); /* ToDo SHA3-512 hash this password before sending to backend. */
    if (this->conn.open()){
        setDBname("rbims");
        writeServerSettings(host, port, user, pass);
        return true;
    }
    return false;
}

