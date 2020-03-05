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

#endif // DIE_NODE_H
