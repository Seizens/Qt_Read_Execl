#ifndef DIE_NODE_H
#define DIE_NODE_H

class Die_node {
public:
    int bytesize;
    int totalsize;
    int bitsize;
    char name[200];
    char type_name[200];
    Die_node(){
      bytesize = 0;
      totalsize = 0;
      bitsize = 0;
    }
};

class Vector_Plural_node{
public:
    bool is_plural;
    int array_num;
    int base_size;
    int totals_size;
    char base_type_name[200];
    Vector_Plural_node(){
        is_plural = false;
        array_num = 0;
        base_size = 0;
        totals_size = 0;
    }
};

#endif // DIE_NODE_H
