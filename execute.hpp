//
// Created by Jlhsmall on 2020/7/8.
//

#ifndef RESCV_EXECUTE_HPP
#define RESCV_EXECUTE_HPP

#include "type.hpp"
#include "instructiondecode.hpp"
class execute_manager{
public:
    types Type;
    unsigned rd,val,_pc;bool _jump;
    execute_manager(const instruction_decode_manager &idm){
        if(idm.rtype!=NULL)rd=idm.rtype->rd;
        if(idm.itype!=NULL)rd=idm.itype->rd;
        if(idm.utype!=NULL)rd=idm.utype->rd;
        if(idm.jtype!=NULL)rd=idm.jtype->rd;
        _jump=0;
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
            case JALR:val=pc+4u;_jump=1;_pc=idm.itype->imm+idm.itype->vrs1&4294967294u;break;

            case SB:
            case SH:
            case SW:val=idm.stype->vrs1+idm.stype->imm;_pc=idm.stype->vrs2;break;

            case BEQ:if(idm.btype->vrs1==idm.btype->vrs2)_jump=1;_pc=pc+idm.btype->imm;break;
            case BNE:if(idm.btype->vrs1!=idm.btype->vrs2)_jump=1;_pc=pc+idm.btype->imm;break;
            case BLT:if(static_cast<int>(idm.btype->vrs1)<static_cast<int>(idm.btype->vrs2))_jump=1;_pc=pc+idm.btype->imm;break;
            case BGE:if(static_cast<int>(idm.btype->vrs1)>=static_cast<int>(idm.btype->vrs2))_jump=1;_pc=pc+idm.btype->imm;break;
            case BLTU:if(idm.btype->vrs1<idm.btype->vrs2)_jump=1;_pc=pc+idm.btype->imm;break;
            case BGEU:if(idm.btype->vrs1>=idm.btype->vrs2)_jump=1;_pc=pc+idm.btype->imm;break;

            case LUI:val=idm.utype->imm;break;
            case AUIPC:val=idm.utype->imm+pc;break;

            case JAL:val=pc+4u;_jump=1;_pc=pc+idm.jtype->imm;
        }
    }
};
#endif //RESCV_EXECUTE_HPP
