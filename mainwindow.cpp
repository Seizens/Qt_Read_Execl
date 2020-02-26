#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    this->init_view();

    XlsxReader *xlsxReader = new XlsxReader(tr("/home/books/test_execl.xlsx"));
//    xlsxReader->init_execl();
    xlsxReader->get_current_sheet(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init_view()
{
    QFont font("Consolas", 14, 50);

    QMenu *fileMenu = ui->menubar->addMenu("&File");
    fileMenu->setFont(font);
    openAction = new QAction(tr("&Open"), this);
    connect(openAction, SIGNAL(triggered()), this, SLOT(select_execl()));
    fileMenu->addAction(openAction);

}

void MainWindow::select_execl()
{
    QString filename;
    filename = QFileDialog::getOpenFileName(this, tr("Select"), tr("/home/books/"), tr(""));
    if (filename.isEmpty()){
        __print(tr("no select file"));
        return;
    }
    __print(filename);
    XlsxReader *xlsxReader = new XlsxReader(filename);
}
