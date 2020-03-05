#include "xlsxreader.h"
#include <QObject>
#include <vector>

XlsxReader::XlsxReader(QString filename)
{
    this->init_data();
    this->fileName = filename;
    this->init_execl();
}

XlsxReader::XlsxReader(char *filename)
{
    this->init_data();
    this->fileName =  QString(QLatin1String(filename));
    this->init_execl();
}

void XlsxReader::init_data()
{
    this->fileName.clear();
    this->workBook = NULL;
    this->workSheet = NULL;
    this->colCount = 0;
    this->rowCount = 0;
    this->firstCol = 0;
    this->firstRow = 0;
    this->lastCol = 0;
    this->lastRow = 0;
    this->init_work_data();
}

void XlsxReader::init_execl()
{
    QFileInfo fileInfo;
    fileInfo = QFileInfo(this->fileName);
    QString file_name, file_suffix;
    file_name = fileInfo.fileName();
    file_suffix = fileInfo.suffix();
    if (QString::compare(file_suffix, QObject::tr("xlsx"))!=0){
      __print(QObject::tr("this is not xlsx file"));
        exit(0);
    }
    sprintf(temp, "xlsx file path is %s .", this->fileName.toUtf8().data());
    __print(temp);

    this->xlsx = new QXlsx::Document(this->fileName);
    this->workBook = xlsx->workbook();
}

void XlsxReader::display_current_sheet_values()
{
    for (unsigned int i = this->firstRow; i< this->rowCount; i++){
        for(unsigned int j = this->firstCol; j< this->colCount; j++){
            QXlsx::Cell *cell = this->workSheet->cellAt(i, j);
            if(cell == NULL) continue;
#ifdef DEBUG_PRINT
            sprintf(temp, "Row is %d, Col is %d, Value is %s", i, j, cell->value().toString().toUtf8().data());
            __print(temp);
#endif // DEBUG_PRINT
        }
    }
}

void XlsxReader::get_current_sheet(unsigned int index)
{

    this->workSheet = static_cast<QXlsx::Worksheet*>(this->workBook->sheet(index));
    this->get_current_sheet_col_row();

#ifdef DEBUG_PRINT
    this->display_current_sheet_values();
#endif //DEBUG_PRINT

}

void XlsxReader::get_current_sheet(QString sheetname)
{
    unsigned int sheet_count = this->workBook->sheetCount();
    for(unsigned int i=0; i<sheet_count; i++){
        if (QString::compare(sheetname, this->workBook->sheet(i)->sheetName())==0){
            this->get_current_sheet(i);
            break;
        }
    }
}


void XlsxReader::get_current_sheet_col_row()
{
    if (this->workSheet == NULL){
        __print(QObject::tr("Pls select worksheet !!!"));
        return;
    }
    this->rowCount = this->workSheet->dimension().rowCount();
    this->firstRow = this->workSheet->dimension().firstRow();
    this->lastRow = this->workSheet->dimension().lastRow();

    this->colCount = this->workSheet->dimension().columnCount();
    this->firstCol = this->workSheet->dimension().firstColumn();
    this->lastCol = this->workSheet->dimension().lastColumn();

#ifdef DEBUG_PRINT
    sprintf(temp, "start row is %d, last row is %d, Count row is %d .", \
            this->firstRow, this->lastRow, this->rowCount);
    __print(temp);

    sprintf(temp, "start col is %d, last col is %d, Count col is %d .",\
            this->firstCol, this->lastCol, this->colCount);
    __print(temp);

#endif  //DEBUG_PRINT

}

CellRect XlsxReader::get_value_index_from_row(QString value)
{
    CellRect index;
    if (this->workSheet == NULL){
        __print(QObject::tr("Pls select which worksheet !!!"));
        return index;
    }
    for (unsigned int i = this->firstRow; i< this->rowCount; i++){
        for(unsigned int j = this->firstCol; j< this->colCount; j++){
            if (this->compare_cell_value(value, this->workSheet->cellAt(i, j)) == true){
                index.col = j;
                index.row = i;
                return index;
            }
        }
    }
    __print("not find");
    return index;
}

CellRect XlsxReader::get_value_index_from_col(QString value)
{
    CellRect index;
    if (this->workSheet == NULL){
        __print(QObject::tr("Pls select which worksheet !!!"));
        return index;
    }
    for (unsigned int i = this->firstCol; i< this->colCount; i++){
        for(unsigned int j = this->firstRow; j< this->rowCount; j++){
            if (this->compare_cell_value(value, this->workSheet->cellAt(j, i)) == true){
                index.col = i;
                index.row = j;
                return index;
            }
        }
    }
    __print("not find");
    return  index;
}

bool XlsxReader::compare_cell_value(QString value, QXlsx::Cell *cell)
{
    if(cell == NULL) return false;
//    if (cell->isRichString()){
        QString temp_value = cell->value().toString();
        if (QString::compare(temp_value, value) == 0){
            return true;
        }
//    }
    return false;
}

void XlsxReader::init_work_data()
{
    this->inputValue.clear();
    this->outputValue.clear();
    this->otherValueList.clear();
    this->otherRectList.clear();
    this->workRow = -1;
}

void XlsxReader::set_work_reader_config(QString inputValue, QString outputValue, QStringList otherValueList)
{
    this->init_work_data();
    this->inputValue = inputValue;
    this->outputValue = outputValue;
    this->otherValueList = otherValueList;
    this->get_work_first_row();
}

void XlsxReader::get_work_first_row()
{
    this->inputRect = this->get_value_index_from_row(this->inputValue);
    int row = this->inputRect.row;
    this->outputRect = this->get_value_index_from_row(this->outputValue);
    if (row != this->outputRect.row){
        return;
    }

    int size = this->otherValueList.size();
    for (int i=0;i<size; i++){
        CellRect tempRect = this->get_value_index_from_row(this->otherValueList[i]);
        this->otherRectList.append(tempRect);
       if (row != tempRect.row){
           return;
       }
    }
    this->workRow = row;

#ifdef DEBUG_PRINT
    sprintf(temp, "work row is %d", this->workRow);
    __print(temp);
#endif //DEBUG_PRINT

}

int XlsxReader::search_by_value(QString inputValue, PdeTraces *pdeTraces){
    unsigned int inputCol = this->inputRect.col;
    unsigned int matchRow = 0;
    int res = -1;
    PdeTraces valueTraces;
    for(unsigned int i= this->workRow+1; i< this->rowCount; i++){
        QXlsx::Cell *cell = this->workSheet->cellAt(i, inputCol);
        if (cell == NULL) continue;
        if(QString::compare(cell->value().toString(), inputValue)==0){
              valueTraces.name = this->workSheet->cellAt(i, this->outputRect.col)->value().toString();
              valueTraces.address = cell->value().toString();
              valueTraces.values.append(this->get_single_value(i));
              matchRow = i;
              res = 0;
              break;
        }
    }
    if (res == 0){
        for(unsigned int i= matchRow+1; i< this->rowCount; i++){
            QXlsx::Cell *cell = this->workSheet->cellAt(i, inputCol);
            if (cell != NULL){
                break;
            }
            valueTraces.values.append(this->get_single_value(i));
        }
        *pdeTraces = valueTraces;
    }
    return res;
}

TracesValue XlsxReader::get_single_value(unsigned int row)
{
    TracesValue value;
    value.value_1 = this->workSheet->cellAt(row, this->otherRectList[0].col)->value().toString();
    value.value_2 = this->workSheet->cellAt(row, this->otherRectList[1].col)->value().toString();
    return value;
}

void XlsxReader::get_all_struct_info()
{
    if (this->workRow == -1){
        __print("PlS set work config !!!");
        return;
    }
//    for(int i=this->workRow; i<this->rowCount; i++){

//    }
}




