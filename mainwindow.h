#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAction>
#include "comm.h"
#include "xlsxreader.h"
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include "Die_Node.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QTreeWidget *header_tree;
    void init_view();
    QAction *openAction;

    void xlsx_reader();
    void vector_reader();
    void Die_info(Die_node *node);
    void print_value(unsigned int inaddr, char *type_name, unsigned int bytesize, QTreeWidgetItem *item);
    void handle_base(Die_node *node, unsigned int baseaddr, QTreeWidgetItem *item);

private:
    Ui::MainWindow *ui;

private slots:
    void select_execl();
};
#endif // MAINWINDOW_H
