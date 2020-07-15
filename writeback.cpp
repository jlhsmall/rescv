//
// Created by Jlhsmall on 2020/7/13.
//

#include "writeback.h"
#include "memoryaccess.h"
#include "instructionfetch.h"
write_back_manager wbm;
void write_back_manager::get(){
    if(mem_clock)return;
    if(kill==1){
        kill=0;return;
    }
    if(wait){//wait>0||wait==-1
        if(wait>0)--wait;return;
    }
    if(ifm.wait>1){
        wait=ifm.wait-1;return;
    }
    if(ifm.wait==-1){
        wait=-1;return;
    }
    Type=mam.Type;
    if(mam.rd==32||!mam.rd)return;--use[mam.rd];
    switch(Type){
        case ADD:
        case SUB:
        case XOR:
        case OR:
        case AND:
        case SLL:
        case SRL:
        case SRA:
        case SLT:
        case SLTU:
        case LB:
        case LH:
        case LW:
        case LBU:
        case LHU:
        case ADDI:
        case XORI:
        case ORI:
        case ANDI:
        case SLLI:
        case SRLI:
        case SRAI:
        case SLTI:
        case SLTIU:
        case JALR:

        case LUI:
        case AUIPC:

        case JAL:
            reg[mam.rd]=mam.val;
    }
}