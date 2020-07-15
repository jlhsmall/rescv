//
// Created by Jlhsmall on 2020/7/13.
//
#include "instructionfetch.h"
#include "instructiondecode.h"
#include "init.h"
#include "memoryaccess.h"
instruction_fetch_manager ifm;
void instruction_fetch_manager::get(){
    if(kill==1){
        kill=0;idm.kill=1;return;
    }
    if(mem_clock||decoded!=1)return;
    if(wait){//wait>0||wait==-1
        if(wait>0)--wait,++idm.wait;
        else idm.wait=-1;return;
    }
    decoded=0;
    if (!jump)pc += 4;else jump=0;
    _pc=pc;
    instruction = *reinterpret_cast<int *>(memory+pc);
    if(instruction==0x0ff00513)wait=-1;
}
