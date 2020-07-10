//
// Created by Jlhsmall on 2020/7/8.
//

#ifndef RESCV_INSTRUCTIONDECODE_HPP
#define RESCV_INSTRUCTIONDECODE_HPP
#include "type.hpp"
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
class instruction_decode_manager{
public:
    types Type;
    Rtype *rtype;
    Itype *itype;
    Stype *stype;
    Btype *btype;
    Utype *utype;
    Jtype *jtype;
    instruction_decode_manager(const unsigned &instruction){
        Type=gettype(instruction);
        rtype=NULL;itype=NULL;stype=NULL;btype=NULL;utype=NULL;jtype=NULL;
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
                rtype=new Rtype(instruction);
                break;
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
                itype=new Itype(instruction);
                break;
            case SB:
            case SH:
            case SW:
                stype=new Stype(instruction);
                break;
            case BEQ:
            case BNE:
            case BLT:
            case BGE:
            case BLTU:
            case BGEU:
                btype=new Btype(instruction);
                break;
            case LUI:
            case AUIPC:
                utype=new Utype(instruction);
                break;
            case JAL:
                jtype=new Jtype(instruction);
        }
    }
    ~instruction_decode_manager(){
        if(rtype!=NULL)delete rtype;
        else if(itype!=NULL)delete itype;
        else if(itype!=NULL)delete stype;
        else if(itype!=NULL)delete btype;
        else if(itype!=NULL)delete utype;
        else delete jtype;
    }
};

#endif //RESCV_INSTRUCTIONDECODE_HPP
