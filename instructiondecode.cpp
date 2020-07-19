//
// Created by Jlhsmall on 2020/7/13.
//

#include <iostream>
#include "instructiondecode.h"
#include "instructionfetch.h"
#include "execute.h"
#include "memoryaccess.h"
#include "predictor.h"
instruction_decode_manager idm;
types gettype(const unsigned &instruction){
    switch(instruction&127u){
        case 0b0110111:return LUI;
        case 0b0010111:return AUIPC;
        case 0b1101111:return JAL;
        case 0b1100111:return JALR;
        case 0b1100011:
            switch((instruction>>12u)&7u){
                case 0b000:return BEQ;
                case 0b001:return BNE;
                case 0b100:return BLT;
                case 0b101:return BGE;
                case 0b110:return BLTU;
                case 0b111:return BGEU;
            }
        case 0b0000011:
            switch((instruction>>12u)&7u){
                case 0b000:return LB;
                case 0b001:return LH;
                case 0b010:return LW;
                case 0b100:return LBU;
                case 0b101:return LHU;
            }
        case 0b0100011:
            switch((instruction>>12u)&7u){
                case 0b000:return SB;
                case 0b001:return SH;
                case 0b010:return SW;
            }
        case 0b0010011:
            switch((instruction>>12u)&7u){
                case 0b000:return ADDI;
                case 0b010:return SLTI;
                case 0b011:return SLTIU;
                case 0b100:return XORI;
                case 0b110:return ORI;
                case 0b111:return ANDI;
                case 0b001:return SLLI;
                case 0b101:return instruction>>30u?SRAI:SRLI;
            }
        case 0b0110011:
            switch((instruction>>12u)&7u){
                case 0b000:return instruction>>30u?SUB:ADD;
                case 0b001:return SLL;
                case 0b010:return SLT;
                case 0b011:return SLTU;
                case 0b100:return XOR;
                case 0b101:return instruction>>30u?SRA:SRL;
                case 0b110:return OR;
                case 0b111:return AND;
            }
    }
}
void instruction_decode_manager::cancel_use(){
    if(rtype!=NULL)--use[rtype->rd];
    if(itype!=NULL&&itype->rd)--use[itype->rd];
    if(utype!=NULL)--use[utype->rd];
    if(jtype!=NULL&&jtype->rd)--use[jtype->rd];
}
void instruction_decode_manager::get(){
    if(mem_clock)return;
    if(kill==1){
        kill=0;em.kill=1;wait=0;return;
    }
    if(wait){//wait>0||wait==-1
        if(wait>0)--wait,++em.wait;
        else em.wait=-1;return;
    }
    if(ifm.decoded==2){
        if(rtype!=NULL){
            if(rtype->rs1==mam.rd)rtype->vrs1=mam.val;
            else rtype->vrs2=mam.val;
        }
        if(itype!=NULL)itype->vrs1=mam.val;
        if(stype!=NULL){
            if(stype->rs1==mam.rd)stype->vrs1=mam.val;
            else stype->vrs2=mam.val;
        }
        if(btype!=NULL){
            if(btype->rs1==mam.rd)btype->vrs1=mam.val;
            else btype->vrs2=mam.val;
        }
        ifm.decoded=1;
        return;
    }
    ifm.decoded=1;
    if(rtype!=NULL){delete rtype;rtype=NULL;}
    if(itype!=NULL){delete itype;itype=NULL;}
    if(stype!=NULL){delete stype;stype=NULL;}
    if(btype!=NULL){delete btype;btype=NULL;}
    if(utype!=NULL){delete utype;utype=NULL;}
    if(jtype!=NULL){delete jtype;jtype=NULL;}
    Type=gettype(ifm.instruction);
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
            rtype=new Rtype(ifm.instruction);
            rtype->vrs1=get_reg_val(rtype->rs1,wait);
            rtype->vrs2=get_reg_val(rtype->rs2,wait);
            ++use[rtype->rd];
            if(wait){wait=0;++em.wait;ifm.decoded=2;}
            break;
        case JALR:
            ++ifm.wait;jump=1;
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
            itype=new Itype(ifm.instruction);
            itype->vrs1=get_reg_val(itype->rs1,wait);
            if(itype->rd)++use[itype->rd];
            if(wait){wait=0;++em.wait;ifm.decoded=2;}
            break;
        case SB:
        case SH:
        case SW:
            stype=new Stype(ifm.instruction);
            stype->vrs1=get_reg_val(stype->rs1,wait);
            stype->vrs2=get_reg_val(stype->rs2,wait);
            if(wait)wait=0,++em.wait,ifm.decoded=2;
            break;
        case BEQ:
        case BNE:
        case BLT:
        case BGE:
        case BLTU:
        case BGEU:
            btype=new Btype(ifm.instruction);
            btype->vrs1=get_reg_val(btype->rs1,wait);
            btype->vrs2=get_reg_val(btype->rs2,wait);
            if(wait)wait=0,++em.wait,ifm.decoded=2;
            if(btype->_jump=pred[btype->_pc>>2&15u].jump_or_not())pc=btype->_pc+btype->imm,jump=1;
            break;
        case LUI:
        case AUIPC:
            utype=new Utype(ifm.instruction);
            ++use[utype->rd];
            break;
        case JAL:
            ++ifm.wait;jump=1;
            jtype=new Jtype(ifm.instruction);
            if(jtype->rd)++use[jtype->rd];
    }
}