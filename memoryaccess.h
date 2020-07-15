//
// Created by Jlhsmall on 2020/7/8.
//

#ifndef RESCV_MEMORYACCESS_HPP
#define RESCV_MEMORYACCESS_HPP
#include "type.h"
#include "execute.h"
class memory_access_manager{
public:
    types Type;
    unsigned rd,val;
    int wait;
    bool kill;
    memory_access_manager(){
        wait=1;
    }
    void get();
};
extern memory_access_manager mam;
extern int mem_clock;
#endif //RESCV_MEMORYACCESS_HPP
