#ifndef COMM_H
#define COMM_H

#include <QDebug>
#include <iostream>

using namespace std;

#define int8 short int
#define int16 int
#define int32 long
#define int64 long long

#define DEBUG_PRINT

enum ITEM_
{
    VAR_NAME = 0,
    VAR_DEC_SIZE,
    VAR_HEX_SIZE,
    VAR_TYPE,
    VAR_SIZE,
    VAR_ADDRESS,
    VAR_STRING,
};
//<tr(" 变量名 ")<<tr(" 数值(16进制) ")<<tr(" 数值(10进制) ")\
//             <<tr(" 变量类型 ")<<tr(" 变量大小 ")<<tr(" 地址 ")<<tr(" 字符串 ");
void __print(QString info);
void __print(char *info);

int  separate_chess_type_name(char *type_name, int *array_num,  bool *is_plural, int *type_size);
int which_type_size(int byte_size, char *type_name);

#endif // COMM_H
