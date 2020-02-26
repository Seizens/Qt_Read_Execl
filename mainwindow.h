#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAction>
#include "comm.h"
#include "xlsxreader.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void init_view();
    QAction *openAction;

    void xlsx_reader();

private:
    Ui::MainWindow *ui;

private slots:
    void select_execl();
};
#endif // MAINWINDOW_H
