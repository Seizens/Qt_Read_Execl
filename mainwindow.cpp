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
    char temp[200];
    XlsxReader *xlsxReader = new XlsxReader(tr("/home/books/test_execl.xlsx"));
    xlsxReader->get_current_sheet(0);
    CellRect index1 = xlsxReader->get_value_index_from_col("value_name_7");
    sprintf(temp, "1. col is %d, row is %d", index1.col, index1.row);
    __print(temp);

    CellRect index2 = xlsxReader->get_value_index_from_row("value_name_7");
    sprintf(temp, "2. col is %d, row is %d", index2.col, index2.row);
    __print(temp);
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
    filename = QFileDialog::getOpenFileName(this, tr("选择Execl文件"), tr("/home/books/"), tr(""));
    if (filename.isEmpty()){
        __print(tr("no select file"));
        return;
    }
    __print(filename);
//    XlsxReader *xlsxReader = new XlsxReader(filename);
}
