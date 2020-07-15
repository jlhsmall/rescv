//
// Created by Jlhsmall on 2020/7/8.
//

#ifndef RESCV_INSTRUCTIONFETCH_H
#define RESCV_INSTRUCTIONFETCH_H
#include "type.h"
class instruction_fetch_manager {
public:
    unsigned instruction,_pc;
    int wait,decoded;
    bool kill;
    instruction_fetch_manager() {
        wait=0;decoded=1;
    }
    void get();
};
extern instruction_fetch_manager ifm;

#endif //RESCV_INSTRUCTIONFETCH_H
