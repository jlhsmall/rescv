//
// Created by Jlhsmall on 2020/7/14.
//

#include "type.h"
#include "instructiondecode.h"
#include "execute.h"
#include "memoryaccess.h"
#include "instructionfetch.h"
#include <iostream>
unsigned pc;
bool jump;
unsigned reg[32];
int use[32];
unsigned get_reg_val(unsigned x,int &wait){
    if(use[x]){
        if(em.rd==x){
            switch(em.Type){
                case LB:
                case LH:
                case LW:
                case LBU:
                case LHU:
                    wait=1;
            }
            return em.val;
        }
        return mam.val;
    }
    return reg[x];
}
Rtype::Rtype(const unsigned &instruction){
    rd=(instruction>>7u)&31u;
    rs1=(instruction>>15u)&31u;
    rs2=(instruction>>20u)&31u;
}
Itype::Itype(const unsigned &instruction){
    rd=(instruction>>7u)&31u;
    rs1=(instruction>>15u)&31u;
    imm=(instruction>>31u)*4294963200u+(instruction>>20u);
}
Stype::Stype(const unsigned &instruction){
    rs1=(instruction>>15u)&31u;
    rs2=(instruction>>20u)&31u;
    imm=(instruction>>31u)*4294963200u+(instruction>>25u<<5u)+((instruction&4095u)>>7u);
}
Btype::Btype(const unsigned &instruction){
    rs1=(instruction>>15u)&31u;
    rs2=(instruction>>20u)&31u;
    imm=(instruction>>31u)*4294963200u+((instruction&2113929216u)>>20u)+((instruction&3840u)>>7u)+((instruction&128u)<<4u);
    _pc=ifm._pc;
}
Utype::Utype(const unsigned &instruction){
    rd=(instruction>>7u)&31u;
    imm=instruction&4294963200u;
}
Jtype::Jtype(const unsigned &instruction){
    rd=(instruction>>7u)&31u;
    imm=(instruction>>31u)*4293918720u+(instruction&1044480u)+((instruction&1048576u)>>9u)+((instruction&2145386496u)>>20u);
}