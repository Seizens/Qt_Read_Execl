#include "comm.h"
#include <QDateTime>


void __print(char *info)
{
    QString temp = QString(QLatin1String(info));
    __print(temp);
}

void __print(QString info)
{
    QString temp ="[";
    QDateTime local(QDateTime::currentDateTime());
    QString localTime = local.toString("yyyy-MM-dd:hh:mm:ss");
    temp.append(localTime);
    temp.append("]  ");
    temp.append(info);
    qDebug()<<qPrintable(temp);

}
