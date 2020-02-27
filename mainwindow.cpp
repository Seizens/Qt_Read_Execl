#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    this->init_view();

    this->xlsx_reader();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::xlsx_reader()
{
    // 1. 导入Execl文件
    XlsxReader *xlsxReader = new XlsxReader(tr("/home/books/test_execl.xlsx"));

    // 2. 选择需要工作的worksheets，可以是index也可以是sheetname
    xlsxReader->get_current_sheet(0);

    //3. 设置配置信息,输入的匹配，输出的匹配
    QString inputValue = "value_name_3";
    QString outputValue = "value_name_1";
    QStringList otherValueList;
    otherValueList<<"value_name_4"<<"value_name_5";
    xlsxReader->set_work_reader_config(inputValue, outputValue, otherValueList);


    //4. 查询
    PdeTraces value;
    int res = xlsxReader->search_by_value("0x00003", &value);
    if (res != 0){
        __print(tr(" not find ."));
        exit(0);
    }
    __print(tr("name is ") + value.name + tr(", address is ")+ value.address + tr("."));

    int size = value.values.size();
    for(int i = 0; i < size; i++){
        __print("No."+QString::number(i+1)+tr(" value_1 is ") + value.values[i].value_1 + tr(", value_2 is ")\
                + value.values[i].value_2 + tr("."));
    }
}

void MainWindow::init_view()
{
    QFont font("Consolas", 14, 50);

    QMenu *fileMenu = ui->menubar->addMenu(tr("  &文件  "));
    fileMenu->setFont(font);
    openAction = new QAction(tr("&打开"), this);
    connect(openAction, SIGNAL(triggered()), this, SLOT(select_execl()));
    fileMenu->addAction(openAction);

}

void MainWindow::select_execl()
{
    QString filename;
    filename = QFileDialog::getOpenFileName(this, tr("选择Execl文件"), tr("./"), tr("*.xlsx"));
    if (filename.isEmpty()){
        __print(tr("no select file"));
        return;
    }
    __print(filename);
//    XlsxReader *xlsxReader = new XlsxReader(filename);
}
