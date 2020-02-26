#ifndef XLSXREADER_H
#define XLSXREADER_H

#include <QtXlsx>
#include "comm.h"
#include "xlsxstruct.h"

#define DEBUG_PRINT


class XlsxReader
{
public:
    XlsxReader(QString filename);
    XlsxReader(char *filename);
    QString fileName;
    QXlsx::Document *xlsx;
    QXlsx::Workbook *workBook;
    QXlsx::Worksheet *workSheet;
    unsigned int rowCount;
    unsigned int firstRow;
    unsigned int lastRow;
    unsigned int colCount;
    unsigned int firstCol;
    unsigned int lastCol;

    // 与Trace 相关信息
    QString inputValue;
    QString outputValue;
    QStringList otherValueList;

    int workRow;
    CellRect inputRect;
    CellRect outputRect;
    QList<CellRect> otherRectList;

    void init_execl();
    void get_current_sheet(unsigned int index);
    void get_current_sheet(QString sheetname);
    CellRect get_value_index_from_row(QString value);
    CellRect get_value_index_from_col(QString value);
    bool compare_cell_value(QString value, QXlsx::Cell *cell);

    void set_work_reader_config(QString inputValue, QString outputValue, QStringList otherValueList);
    void get_work_first_row();
    int search_by_value(QString inputValue);

private:
    char temp[200];

    void init_data();
    void init_work_data();
    void get_current_sheet_col_row();
    void display_current_sheet_values();
    void get_all_struct_info();
};

#endif // XLSXREADER_H
