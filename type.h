//
// Created by Jlhsmall on 2020/7/8.
//

#ifndef RESCV_TYPE_H
#define RESCV_TYPE_H
#include <iostream>
#include "instructionfetch.h"
extern unsigned pc;
extern bool jump;
extern unsigned reg[32];
extern int use[32];
enum types{
    LUI,AUIPC,JAL,JALR,BEQ,BNE,BLT,BGE,BLTU,BGEU,LB,LH,LW,LBU,LHU,SB,SH,SW,ADDI,SLTI,SLTIU,XORI,ORI,ANDI,SLLI,SRLI,SRAI,ADD,SUB,SLL,SLT,SLTU,XOR,SRL,SRA,OR,AND
};
unsigned get_reg_val(unsigned x,int &wait);
class Rtype{
public:
    unsigned vrs2,vrs1,rs1,rs2,rd;
    Rtype(const unsigned &instruction);
};
class Itype{
public:
    unsigned imm,vrs1,rs1,rd;
    Itype(const unsigned &instruction);
};
class Stype{
public:
    unsigned imm,vrs2,vrs1,rs1,rs2;
    Stype(const unsigned &instruction);
};
class Btype{
public:
    unsigned imm,vrs2,vrs1,rs1,rs2,_pc;
    Btype(const unsigned &instruction);
};
class Utype{
public:
    unsigned imm,rd;
    Utype(const unsigned &instruction);
};
class Jtype{
public:
    unsigned imm,rd;
    Jtype(const unsigned &instruction);
};
#endif //RESCV_TYPE_H
