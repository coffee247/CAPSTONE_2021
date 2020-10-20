#ifndef COMMONUTILS_H
#define COMMONUTILS_H

#include <QObject>

class CommonUtils : public QObject
{
    Q_OBJECT
public:
    explicit CommonUtils(QObject *parent = nullptr);
    void displayMessage(QString message);


signals:

};

#endif // COMMONUTILS_H
