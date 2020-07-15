//
// Created by Jlhsmall on 2020/7/8.
//

#ifndef RESCV_WRITEBACK_H
#define RESCV_WRITEBACK_H
#include "type.h"
#include "instructiondecode.h"
class write_back_manager{
public:
    types Type;
    int wait;
    bool kill;
    write_back_manager(){
        wait=1;
    }
    void get();
};
extern write_back_manager wbm;
#endif //RESCV_WRITEBACK_H
