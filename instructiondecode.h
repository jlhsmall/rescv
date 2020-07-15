//
// Created by Jlhsmall on 2020/7/8.
//

#ifndef RESCV_INSTRUCTIONDECODE_HPP
#define RESCV_INSTRUCTIONDECODE_HPP
#include "type.h"
types gettype(const unsigned &instruction);
class instruction_decode_manager{
public:

    types Type;
    Rtype *rtype;
    Itype *itype;
    Stype *stype;
    Btype *btype;
    Utype *utype;
    Jtype *jtype;
    int wait;
    bool kill;
    instruction_decode_manager(){
        rtype=NULL;itype=NULL;stype=NULL;btype=NULL;utype=NULL;jtype=NULL;
        wait=1;
    };
    void cancel_use();
    void get();
    ~instruction_decode_manager(){
        if(rtype!=NULL)delete rtype;
        else if(itype!=NULL)delete itype;
        else if(stype!=NULL)delete stype;
        else if(btype!=NULL)delete btype;
        else if(utype!=NULL)delete utype;
        else delete jtype;
    }
};
extern instruction_decode_manager idm;

#endif //RESCV_INSTRUCTIONDECODE_HPP
