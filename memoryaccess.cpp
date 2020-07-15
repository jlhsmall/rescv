//
// Created by Jlhsmall on 2020/7/13.
//
#include "memoryaccess.h"
#include "instructiondecode.h"
#include "instructionfetch.h"
#include "execute.h"
#include "writeback.h"
#include "init.h"
memory_access_manager mam;
int mem_clock;
void memory_access_manager::get(){
    if(mem_clock){
        --mem_clock;return;
    }
    if(kill==1){
        kill=0;wbm.kill=1;return;
    }
    if(wait){//wait>0||wait==-1
        if(wait>0)--wait,++wbm.wait;
        else wbm.wait=-1;return;
    }
    rd=em.rd;
    switch(Type=em.Type){
        case LB:val=static_cast<int>(memory[em.val]);mem_clock=2;break;
        case LH:val=static_cast<int>(*reinterpret_cast<unsigned short*>(memory+em.val));mem_clock=2;break;
        case LW:val=*reinterpret_cast<unsigned*>(memory+em.val);mem_clock=2;break;
        case LBU:val=memory[em.val];mem_clock=2;break;
        case LHU:val=*reinterpret_cast<unsigned short*>(memory+em.val);mem_clock=2;break;
        case SB:memory[em.val]=em.val2;mem_clock=2;break;
        case SH:*reinterpret_cast<unsigned short*>(memory+em.val)=em.val2;mem_clock=2;break;
        case SW:*reinterpret_cast<unsigned*>(memory+em.val)=em.val2;mem_clock=2;break;
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
        case JAL:val=em.val;
    }
}