//
// Created by Jlhsmall on 2020/7/8.
//

#ifndef RESCV_TYPE_HPP
#define RESCV_TYPE_HPP
unsigned pc;
unsigned reg[32];
enum types{
    LUI,AUIPC,JAL,JALR,BEQ,BNE,BLT,BGE,BLTU,BGEU,LB,LH,LW,LBU,LHU,SB,SH,SW,ADDI,SLTI,SLTIU,XORI,ORI,ANDI,SLLI,SRLI,SRAI,ADD,SUB,SLL,SLT,SLTU,XOR,SRL,SRA,OR,AND
};
class Rtype{
public:
    unsigned vrs2,vrs1,rd;
    Rtype(const unsigned &instruction){
        rd=(instruction>>7u)&31u;
        vrs1=reg[(instruction>>15u)&31u];
        vrs2=reg[(instruction>>20u)&31u];
    }
};
class Itype{
public:
    unsigned imm,vrs1,rd;
    Itype(const unsigned &instruction){
        rd=(instruction>>7u)&31u;
        vrs1=reg[(instruction>>15u)&31u];
        imm=(instruction>>31u)*4294963200u+(instruction>>20u);
    }
};
class Stype{
public:
    unsigned imm,vrs2,vrs1;
    Stype(const unsigned &instruction){
        vrs1=reg[(instruction>>15u)&31u];
        vrs2=reg[(instruction>>20u)&31u];
        imm=(instruction>>31u)*4294963200u+(instruction>>25u<<5u)+((instruction&4095u)>>7u);
    }
};
class Btype{
public:
    unsigned imm,vrs2,vrs1;
    Btype(const unsigned &instruction){
        vrs1=reg[(instruction>>15u)&31u];
        vrs2=reg[(instruction>>20u)&31u];
        imm=(instruction>>31u)*4294963200u+((instruction&2113929216u)>>20u)+((instruction&3840u)>>7u)+((instruction&128u)<<4u);
    }
};
class Utype{
public:
    unsigned imm,rd;
    Utype(const unsigned &instruction){
        rd=(instruction>>7u)&31u;
        imm=instruction&4294963200u;
    }
};
class Jtype{
public:
    unsigned imm,rd;
    Jtype(const unsigned &instruction){
        rd=(instruction>>7u)&31u;
        imm=(instruction>>31u)*4293918720u+(instruction&1044480u)+((instruction&1048576u)>>9u)+((instruction&2145386496u)>>20u);
    }
};
#endif //RESCV_TYPE_HPP
