//
// Created by Jlhsmall on 2020/7/8.
//

#ifndef RESCV_WRITEBACK_HPP
#define RESCV_WRITEBACK_HPP
#include "type.hpp"
#include "instructiondecode.hpp"
class write_back_manager{
public:
    types Type;
    unsigned _pc;bool _jump;
    write_back_manager(const memory_access_manager &mam){
        if(_jump=mam._jump)_pc=mam._pc;
        switch(Type=mam.Type){
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
                if(mam.rd)reg[mam.rd]=mam.val;
        }
    }
};
#endif //RESCV_WRITEBACK_HPP
