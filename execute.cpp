//
// Created by Jlhsmall on 2020/7/13.
//
#include "execute.h"
#include "type.h"
#include "init.h"
#include "memoryaccess.h"
#include "predictor.h"
execute_manager em;
void execute_manager::get() {
    if(mem_clock)return;
    if(kill==1){
        kill=0;mam.kill=1;return;
    }
    if(wait){//wait>0||wait==-1
        if(wait>0)--wait,++mam.wait;
        else mam.wait=-1;return;
    }
    if(idm.rtype!=NULL)rd=idm.rtype->rd;
    else if(idm.itype!=NULL)rd=idm.itype->rd;
    else if(idm.utype!=NULL)rd=idm.utype->rd;
    else if(idm.jtype!=NULL)rd=idm.jtype->rd;
    else rd=32;
    switch(Type=idm.Type){
        case ADD:val=idm.rtype->vrs1+idm.rtype->vrs2;break;
        case SUB:val=idm.rtype->vrs1-idm.rtype->vrs2;break;
        case XOR:val=idm.rtype->vrs1^idm.rtype->vrs2;break;
        case OR:val=idm.rtype->vrs1|idm.rtype->vrs2;break;
        case AND:val=idm.rtype->vrs1&idm.rtype->vrs2;break;
        case SLL:val=idm.rtype->vrs1<<(idm.rtype->vrs2&31u);break;
        case SRL:val=idm.rtype->vrs1>>(idm.rtype->vrs2&31u);break;
        case SRA:val=static_cast<int>(idm.rtype->vrs1)>>(idm.rtype->vrs2&31);break;
        case SLT:val=static_cast<int>(idm.rtype->vrs1)<static_cast<int>(idm.rtype->vrs2);break;
        case SLTU:val=idm.rtype->vrs1<idm.rtype->vrs2;break;

        case LB:
        case LH:
        case LW:
        case LBU:
        case LHU:val=idm.itype->vrs1+idm.itype->imm;break;
        case ADDI:val=idm.itype->vrs1+idm.itype->imm;break;
        case XORI:val=idm.itype->vrs1^idm.itype->imm;break;
        case ORI:val=idm.itype->vrs1|idm.itype->imm;break;
        case ANDI:val=idm.itype->vrs1&idm.itype->imm;break;
        case SLLI:val=idm.itype->vrs1<<idm.itype->imm;break;
        case SRLI:val=idm.itype->vrs1>>idm.itype->imm;break;
        case SRAI:val=static_cast<int>(idm.itype->vrs1)>>idm.itype->imm;break;
        case SLTI:val=static_cast<int>(idm.itype->vrs1)<static_cast<int>(idm.itype->imm);break;
        case SLTIU:val=idm.itype->vrs1<idm.itype->imm;break;
        case JALR:val=pc+4u;pc=idm.itype->imm+idm.itype->vrs1&4294967294u;break;

        case SB:
        case SH:
        case SW:val=idm.stype->vrs1+idm.stype->imm;val2=idm.stype->vrs2;break;

        case BEQ:
            if(idm.btype->vrs1==idm.btype->vrs2) {
                if (!pred[idm.btype->_pc>>2&7u].jump_or_not()) {
                    pc = idm.btype->_pc + idm.btype->imm;jump=1;
                    idm.kill = ifm.kill= 1;idm.cancel_use();ifm.decoded=1;
                }
                pred[idm.btype->_pc>>2&7u].update(1);
            }
            else{
                if (pred[idm.btype->_pc>>2&7u].jump_or_not()) {
                    pc = idm.btype->_pc;jump=0;
                    idm.kill = ifm.kill= 1;idm.cancel_use();ifm.decoded=1;
                }
                pred[idm.btype->_pc>>2&7u].update(0);
            }break;
        case BNE:
            if(idm.btype->vrs1!=idm.btype->vrs2) {
                if (!pred[idm.btype->_pc>>2&7u].jump_or_not()) {
                    pc = idm.btype->_pc + idm.btype->imm;jump=1;
                    idm.kill = ifm.kill= 1;idm.cancel_use();ifm.decoded=1;
                }
                pred[idm.btype->_pc>>2&7u].update(1);
            }
            else{
                if (pred[idm.btype->_pc>>2&7u].jump_or_not()) {
                    pc = idm.btype->_pc;jump=0;
                    idm.kill = ifm.kill= 1;idm.cancel_use();ifm.decoded=1;
                }
                pred[idm.btype->_pc>>2&7u].update(0);
            }break;
        case BLT:
            if(static_cast<int>(idm.btype->vrs1)<static_cast<int>(idm.btype->vrs2)) {
                if (!pred[idm.btype->_pc>>2&7u].jump_or_not()) {
                    pc = idm.btype->_pc + idm.btype->imm;jump=1;
                    idm.kill = ifm.kill= 1;idm.cancel_use();ifm.decoded=1;
                }
                pred[idm.btype->_pc>>2&7u].update(1);
            }
            else{
                if (pred[idm.btype->_pc>>2&7u].jump_or_not()) {
                    pc = idm.btype->_pc;jump=0;
                    idm.kill = ifm.kill= 1;idm.cancel_use();ifm.decoded=1;
                }
                pred[idm.btype->_pc>>2&7u].update(0);
            }break;
        case BGE:
            if(static_cast<int>(idm.btype->vrs1)>=static_cast<int>(idm.btype->vrs2)) {
                if (!pred[idm.btype->_pc>>2&7u].jump_or_not()) {
                    pc = idm.btype->_pc + idm.btype->imm;jump=1;
                    idm.kill = ifm.kill= 1;ifm.decoded=1;
                }
                pred[idm.btype->_pc>>2&7u].update(1);
            }
            else{
                if (pred[idm.btype->_pc>>2&7u].jump_or_not()) {
                    pc = idm.btype->_pc;jump=0;
                    idm.kill = ifm.kill= 1;ifm.decoded=1;
                }
                pred[idm.btype->_pc>>2&7u].update(0);
            }break;
        case BLTU:
            if(idm.btype->vrs1<idm.btype->vrs2) {
                if (!pred[idm.btype->_pc>>2&7u].jump_or_not()) {
                    pc = idm.btype->_pc + idm.btype->imm;jump=1;
                    idm.kill = ifm.kill= 1;ifm.decoded=1;
                }
                pred[idm.btype->_pc>>2&7u].update(1);
            }
            else{
                if (pred[idm.btype->_pc>>2&7u].jump_or_not()) {
                    pc = idm.btype->_pc;jump=0;
                    idm.kill = ifm.kill= 1;ifm.decoded=1;
                }
                pred[idm.btype->_pc>>2&7u].update(0);
            }break;
        case BGEU:
            if(idm.btype->vrs1>=idm.btype->vrs2) {
                if (!pred[idm.btype->_pc>>2&7u].jump_or_not()) {
                    pc = idm.btype->_pc + idm.btype->imm;jump=1;
                    idm.kill = ifm.kill= 1;ifm.decoded=1;
                }
                pred[idm.btype->_pc>>2&7u].update(1);
            }
            else{
                if (pred[idm.btype->_pc>>2&7u].jump_or_not()) {
                    pc = idm.btype->_pc;jump=0;
                    idm.kill = ifm.kill= 1;ifm.decoded=1;
                }
                pred[idm.btype->_pc>>2&7u].update(0);
            }break;

        case LUI:val=idm.utype->imm;break;
        case AUIPC:val=idm.utype->imm+pc;break;

        case JAL:val=pc+4u;pc=pc+idm.jtype->imm;
    }
}