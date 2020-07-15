#include <iostream>
#include "init.h"
#include "type.h"
#include "instructionfetch.h"
#include "instructiondecode.h"
#include "execute.h"
#include "memoryaccess.h"
#include "writeback.h"
int main() {
    freopen("r.in","r",stdin);
    init();
    jump=1;
    while(wbm.wait!=-1){
        if(reg[10]==1561)
            reg[10]=1561;
        wbm.get();
        if(pc==4368)
            pc=4368;
        mam.get();
        em.get();
        idm.get();
        ifm.get();
        //printf("%d ",pc);for(int i=0;i<32;++i)printf("%6d ",reg[i]);std::cout<<std::endl;
    }
    std::cout<<(reg[10] & 255)<<std::endl;
   /* while(1){
         ifm(_jump,_pc);
        if(ifm.instruction==){
            std::cout<<(reg[10] & 255)<<std::endl;
            break;
        }
         idm(ifm.instruction);
         em(idm);
         mam(em);
         wbm(mam);
        if(_jump=wbm._jump)_pc=wbm._pc;
    }*/
    return 0;
}
