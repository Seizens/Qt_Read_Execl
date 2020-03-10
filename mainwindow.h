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
    void print_value(unsigned int inaddr, char *type_name, unsigned int bytesize, QTreeWidgetItem *item,\
                     unsigned int core_id, unsigned int thread_id);
    void handle_base(Die_node *node, unsigned int baseaddr, QTreeWidgetItem *item, \
                     unsigned int core_id, unsigned int thread_id);
    void handle_vector(unsigned int baseaddr, QTreeWidgetItem *item, \
                        Vector_Plural_node *vp_node, unsigned int core_id, unsigned int thread_id);
    void handle_plural(unsigned int baseaddr, QTreeWidgetItem *item, \
                       Vector_Plural_node *vp_node , unsigned int core_id, unsigned int thread_id);
    void print_vector_base(unsigned int inaddr, char *type_name, unsigned int base_size, char *base_name ,\
                           QTreeWidgetItem *item, unsigned int core_id, unsigned int thread_id);

private:
    Ui::MainWindow *ui;
    char temp[200];

private slots:
    void select_execl();
};
#endif // MAINWINDOW_H
