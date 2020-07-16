#include <iostream>
#include "init.h"
#include "type.h"
#include "instructionfetch.h"
#include "instructiondecode.h"
#include "execute.h"
#include "memoryaccess.h"
#include "writeback.h"
//unsigned  reg2[32];
int main() {
  //  freopen("r.in","r",stdin);
    //freopen("w2.out","w",stdout);
    init();
    jump=1;
    while(wbm.wait!=-1){
//        if(reg[10]==172)
 //           reg[10]=172;
        wbm.get();
 //       if(memory[4956]==7)
 //           memory[4956]=7;
        mam.get();
        em.get();
        idm.get();
        ifm.get();
      //  int i;
     //   for(i=0;i<32;++i)if(reg[i]!=reg2[i])break;
    //    if(i<32) {
     //       for (i = 0; i < 32; ++i)printf("%6d ", reg2[i] = reg[i]);
      //      std::cout << std::endl;
    //    }
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
