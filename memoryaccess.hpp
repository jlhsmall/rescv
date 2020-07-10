//
// Created by Jlhsmall on 2020/7/8.
//

#ifndef RESCV_MEMORYACCESS_HPP
#define RESCV_MEMORYACCESS_HPP
#include "type.hpp"
#include "execute.hpp"
class memory_access_manager{
public:
    types Type;
    unsigned rd,val,_pc;bool _jump;
    memory_access_manager(const execute_manager &em){
        rd=em.rd;if(_jump=em._jump)_pc=em._pc;
        switch(Type=em.Type){
            case LB:val=static_cast<int>(memory[em.val]);break;
            case LH:val=static_cast<int>(*reinterpret_cast<unsigned short*>(memory+em.val));break;
            case LW:val=*reinterpret_cast<unsigned*>(memory+em.val);break;
            case LBU:val=memory[em.val];break;
            case LHU:val=*reinterpret_cast<unsigned short*>(memory+em.val);break;
            case SB:memory[em.val]=em._pc;break;
            case SH:*reinterpret_cast<unsigned short*>(memory+em.val)=em._pc;break;
            case SW:*reinterpret_cast<unsigned*>(memory+em.val)=em._pc;break;
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
};
#endif //RESCV_MEMORYACCESS_HPP
