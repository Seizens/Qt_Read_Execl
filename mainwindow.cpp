#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QBoxLayout>
#include <QLabel>
#include <QHeaderView>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    this->init_view();

    this->xlsx_reader();
    this->vector_reader();
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

    QFont font_1("Consolas", 12, 50);
    header_tree = new QTreeWidget();
    header_tree->setColumnCount(7);
    header_tree->setFont(font_1);
    QStringList headerName;
    headerName<<tr(" 变量名 ")<<tr(" 数值(16进制) ")<<tr(" 数值(10进制) ")\
             <<tr(" 变量类型 ")<<tr(" 变量大小 ")<<tr(" 地址 ")<<tr(" 字符串 ");
    header_tree->header()->setSectionResizeMode(QHeaderView::ResizeToContents);
    header_tree->setHeaderLabels(headerName);

    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addWidget(header_tree);

    ui->centralwidget->setLayout(mainLayout);
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


void MainWindow::vector_reader()
{
    unsigned int core_id = 0;
    unsigned int thread_id = 0;
    Die_node *node_1 = new Die_node();
    strcpy(node_1->name,"test_1");
    strcpy(node_1->type_name,"v32cint16_t");
    node_1->bytesize = 0x80;
    node_1->totalsize = 0x80;

    QTreeWidgetItem *next_1 = new QTreeWidgetItem(header_tree);
//    next_1->setText(VAR_NAME, node_1->name);
//    next_1->setText(VAR_TYPE, node_1->type_name);

    handle_base(node_1, 0, next_1, core_id, thread_id);

    Die_node *node_2 = new Die_node();
    strcpy(node_2->name,"test_2");
    strcpy(node_2->type_name,"v32int8_t");
    node_2->bytesize = 0x20;
    node_2->totalsize = 0x20;

    QTreeWidgetItem *next_2 = new QTreeWidgetItem(header_tree);
//    next_2->setText(VAR_NAME, node_2->name);
//    next_2->setText(VAR_TYPE, node_2->type_name);

    handle_base(node_2, 0, next_2, core_id, thread_id);

    Die_node *node_3 = new Die_node();
    strcpy(node_3->name,"test_3");
    strcpy(node_3->type_name,"v64int32_t");
    node_3->bytesize = 0x100;
    node_3->totalsize = 0x100;

    QTreeWidgetItem *next_3 = new QTreeWidgetItem(header_tree);
//    next_3->setText(VAR_NAME, node_3->name);
//    next_3->setText(VAR_TYPE, node_3->type_name);

    handle_base(node_3, 0, next_3, core_id, thread_id);

    Die_node *node_4 = new Die_node();
    strcpy(node_4->name,"test_4");
    strcpy(node_4->type_name,"v1int64_t");
    node_4->bytesize = 0x8;
    node_4->totalsize = 0x8;

    QTreeWidgetItem *next_4 = new QTreeWidgetItem(header_tree);
//    next_4->setText(VAR_NAME, node_4->name);
//    next_4->setText(VAR_TYPE, node_4->type_name);

    handle_base(node_4, 0, next_4, core_id, thread_id);

    Die_node *node_5 = new Die_node();
    strcpy(node_5->name,"test_5");
    strcpy(node_5->type_name,"v8uint8_t");
    node_5->bytesize = 0x64;
    node_5->totalsize = 0x64;
    QTreeWidgetItem *next_5 = new QTreeWidgetItem(header_tree);
    handle_base(node_5, 0, next_5, core_id, thread_id);

    Die_node *node_6 = new Die_node();
    strcpy(node_6->name,"test_6");
    strcpy(node_6->type_name,"cint64_t");
    node_6->bytesize = 0x128;
    node_6->totalsize = 0x128;
    QTreeWidgetItem *next_6 = new QTreeWidgetItem(header_tree);
    handle_base(node_6, 0, next_6, core_id, thread_id);
}

void MainWindow::print_value(unsigned int inaddr, char *type_name, unsigned int bytesize, QTreeWidgetItem *item, \
                             unsigned int core_id, unsigned int thread_id)
{
    unsigned char read_data = 0;
    char datahex[100], datadec[100];
    char temp[200];
    unsigned int cu_addr;

    strcpy(datahex, "0x");
    cu_addr = inaddr + bytesize - 1;

}

void MainWindow::handle_base(Die_node *node, unsigned int baseaddr, QTreeWidgetItem *item,\
                             unsigned int core_id, unsigned int thread_id)
{
    item->setText(VAR_NAME, node->name);
    item->setText(VAR_TYPE, node->type_name);

    if(node->bitsize != 0){
        return;
    }
    else {
        int res = 0;
        Vector_Plural_node *vp_node = new Vector_Plural_node();
        res = separate_chess_type_name(node->type_name, vp_node);
        if (res == 0){
            vp_node->totals_size = node->bytesize;
#ifdef DEBUG_PRINT
            sprintf(temp, "array_num is %d", vp_node->array_num);
            __print(temp);
            sprintf(temp, "is plural is %d", vp_node->is_plural);
            __print(temp);
            sprintf(temp, "base type name is %s", vp_node->base_type_name);
            __print(temp);

#endif
            if (vp_node->is_plural){
                this->handle_plural(baseaddr, item,  vp_node, core_id, thread_id);
            }
            else{
                this->handle_vector(baseaddr, item, vp_node, core_id, thread_id);
            }
        }
        else {
            this->print_value(baseaddr, node->type_name, node->bytesize, item, core_id, thread_id);
        }
    }
}

void MainWindow::handle_plural(unsigned int baseaddr, QTreeWidgetItem *item,\
                              Vector_Plural_node *vp_node , unsigned int core_id, unsigned int thread_id)
{
    int array_num = vp_node->array_num;
    int base_size = vp_node->base_size;
    for (int i=0; i<array_num; i++){
        QTreeWidgetItem *next = new QTreeWidgetItem(item);

        if (array_num == 1) strcpy(temp, "Plural");
        else  sprintf(temp, "Plural[%d]", i);

        next->setText(VAR_NAME, temp);
        sprintf(temp, "%d", baseaddr + base_size*2*i);
        next->setText(VAR_ADDRESS, temp);
        sprintf(temp, "%d", base_size*2);
        next->setText(VAR_SIZE, temp);

        strcpy(temp, "real part");
        this->print_vector_base(baseaddr + base_size*2*i, temp,\
                                base_size, vp_node->base_type_name, next, core_id, thread_id);

        strcpy(temp, "imaginary part");
        this->print_vector_base(baseaddr + base_size*2*i+base_size, temp, \
                                base_size, vp_node->base_type_name, next, core_id, thread_id);
    }
}

void MainWindow::handle_vector(unsigned int baseaddr, QTreeWidgetItem *item, \
                               Vector_Plural_node *vp_node, unsigned int core_id, unsigned int thread_id)
{
    int array_num = vp_node->array_num;
    int base_size = vp_node->base_size;
    for (int i=0; i<array_num; i++){

//        QTreeWidgetItem *next = new QTreeWidgetItem(item);
//        sprintf(temp, "Vector[%d]", i);
//        next->setText(VAR_NAME, temp);
//        sprintf(temp, "%d", baseaddr + type_size*i);
//        next->setText(VAR_ADDRESS, temp);
//        sprintf(temp, "%d", type_size);
//        next->setText(VAR_SIZE, temp);

//        which_type_size(type_size, temp);
//        next->setText(VAR_TYPE, temp);
//        this->print_value(baseaddr + type_size*i, temp, type_size, next, core_id, thread_id);

        if (array_num == 1) strcpy(temp, "Vector");
        else  sprintf(temp, "Vector[%d]", i);
        this->print_vector_base(baseaddr + base_size*i, temp, \
                                base_size, vp_node->base_type_name, item, core_id, thread_id);
    }
}

void MainWindow::print_vector_base(unsigned int inaddr, char *type_name, unsigned int base_size, char *base_name ,\
                                   QTreeWidgetItem *item, unsigned int core_id, unsigned int thread_id)
{
    QTreeWidgetItem *next = new QTreeWidgetItem(item);
    sprintf(temp, "%s", type_name);
    next->setText(VAR_NAME, temp);
    sprintf(temp, "%d", inaddr);
    next->setText(VAR_ADDRESS, temp);
    sprintf(temp, "%d", base_size);
    next->setText(VAR_SIZE, temp);
    sprintf(temp, "%s", base_name);
    next->setText(VAR_TYPE, temp);
    this->print_value(inaddr, temp, base_size, next, core_id, thread_id);
}
