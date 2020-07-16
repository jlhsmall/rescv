//
// Created by Jlhsmall on 2020/7/14.
//

#ifndef RISCV_PREDICTOR_H
#define RISCV_PREDICTOR_H
#include <cstdio>

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
        suc+=jump_or_not()==b;++tot;
        cur=nxt[cur][b];
    }
    void get_suc_rate(){
        printf("%.2lf%c\n",100.0*suc/tot,'%');
    }
};
extern predictor pred[8];
#endif //RISCV_PREDICTOR_H
