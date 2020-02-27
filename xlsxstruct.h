#ifndef XLSXSTRUCT_H
#define XLSXSTRUCT_H
#include <QStringList>

struct CellRect{
    int col;
    int row;
    CellRect(){
        col = -1;
        row = -1;
    }
};

struct TracesValue{
    QString value_1;
    QString value_2;
    TracesValue(){
        value_1 = "";
        value_2 = "";
    }
};

struct PdeTraces{
    QString address;
    QString name;
    QList<TracesValue> values;
};


#endif // XLSXSTRUCT_H
