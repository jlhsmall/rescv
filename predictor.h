//
// Created by Jlhsmall on 2020/7/14.
//

#ifndef RISCV_PREDICTOR_H
#define RISCV_PREDICTOR_H
#include <cstdio>
#include "instructiondecode.h"
class predictor {
public:
/*    struct Counter{
        int val;
        Counter &operator ++(){
            if(val<3)++val;
            return *this;
        }
        Counter &operator --(){
            if(val)--val;
            return *this;
        }
    }counter[4];
*/    static int nxt[4][2];
    int cur;
    static unsigned suc,tot;
    predictor(){
        cur=1;
    }
    bool jump_or_not(){
        return cur>=2;
    }
    void update(bool b){
        //printf("%d %d",idm.btype->_jump,b);std::cout<<std::endl;
        suc+=idm.btype->_jump==b;++tot;
        cur=nxt[cur][b];
    }
    void get_suc_rate(){
        printf("%.2lf%c\n",100.0*suc/tot,'%');
    }
};
extern predictor pred[16];
#endif //RISCV_PREDICTOR_H
