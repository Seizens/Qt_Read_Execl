#ifndef XLSXREADER_H
#define XLSXREADER_H

#include <QtXlsx>
#include "comm.h"

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

    void init_execl();
    void get_current_sheet(unsigned int index);
    void get_current_sheet(QString sheetname);
    int get_first_row_for_value(QString value);

private:
    char temp[200];

    void init_data();
    void get_work_sheet_col_row();
    void display_current_sheet_values();
    void test_func();
};

#endif // XLSXREADER_H
