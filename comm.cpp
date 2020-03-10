#include "comm.h"
#include <QDateTime>
#include <QRegExpValidator>
#include <QValidator>
#include <stdio.h>

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

int separate_chess_type_name(char *type_name, Vector_Plural_node *node){
    int res = 1;
    QString str = QString(QLatin1String(type_name));
    __print("检查的 type_name " + str);
    QRegExp vectorRX("^(v(\\d+))?(c?)(u?)(int(\\d+))_t$");

    int pos = str.indexOf(vectorRX);
//    __print(QString::number(pos));
    if (pos >= 0){
#ifdef DEBUG_PRINT
        __print(vectorRX.cap(0));
        __print(vectorRX.cap(1));
        __print(vectorRX.cap(2));
        __print(vectorRX.cap(3));
        __print(vectorRX.cap(4));
        __print(vectorRX.cap(5));
#endif
        node->array_num = vectorRX.cap(1).isEmpty()? 1: vectorRX.cap(2).toInt();
        node->is_plural = vectorRX.cap(3).isEmpty()? false: true;
        if (vectorRX.cap(4).isEmpty()) sprintf(node->base_type_name, "%s", vectorRX.cap(5).toLatin1().data());
        else sprintf(node->base_type_name, "unsigned %s", vectorRX.cap(5).toLatin1().data());
        node->base_size = vectorRX.cap(6).toInt()/8;
        res = 0;
    }
    return res;
}

//int which_type_size(int byte_size,  char *type_name)
//{
//    int res = 0;
//    switch (byte_size) {
//    case 1:
//        strcpy(type_name, "int8");
//        break;
//    case 2:
//        strcpy(type_name, "int16");
//        break;
//    case 4:
//        strcpy(type_name, "int32");
//        break;
//    case 8:
//        strcpy(type_name, "int64");
//        break;
//    default:
//        strcpy(type_name, "unkown");
//        res = -1;
//        break;
//    }
//    return res;
//}
