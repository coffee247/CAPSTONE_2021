#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSettings>
#include <QCryptographicHash>

class database : public QObject
{
    Q_OBJECT

private:
    void setDBName_QSetting(QString dbName);
    void readServerSettings(bool includeDBName);


public:
    explicit database(QObject *parent = nullptr);
    QSqlDatabase conn;
    bool connectToServer(QString host, QString port, QString user, QString pass);
    void setDBname(QString dbName);
    void writeServerSettings(QString host, QString port , QString user, QString pass);
    bool openConn(bool withDbName);
    void clearSettings();
    bool doBDQuery(QString theQuery);

signals:

};

#endif // DATABASE_H
