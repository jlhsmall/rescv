//
// Created by Jlhsmall on 2020/7/8.
//

#ifndef RESCV_EXECUTE_H
#define RESCV_EXECUTE_H

#include "type.h"
#include "instructiondecode.h"
class execute_manager{
public:
    types Type;
    unsigned rd,val,val2;
    int wait;
    bool kill;
    execute_manager(){
        wait=1;
    }
    void get();
};
extern execute_manager em;
#endif //RESCV_EXECUTE_H
