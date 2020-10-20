#include "commonutils.h"
#include <QMessageBox>

CommonUtils::CommonUtils(QObject *parent) : QObject(parent)
{

}


void CommonUtils::displayMessage(QString message)
{
    QMessageBox msgBox;
    msgBox.setText(message);
    msgBox.exec();
}
