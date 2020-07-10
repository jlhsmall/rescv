#include <iostream>
#include "init.hpp"
#include "type.hpp"
#include "instructionfetch.hpp"
#include "instructiondecode.hpp"
#include "execute.hpp"
#include "memoryaccess.hpp"
#include "writeback.hpp"
int main() {
    //freopen("r.in","r",stdin);
    init();
    bool _jump=true;unsigned _pc=0;
    while(1){
        instruction_fetch_manager ifm(_jump,_pc);
        if(ifm.instruction==0x0ff00513){
            std::cout<<(reg[10] & 255)<<std::endl;
            break;
        }
        instruction_decode_manager idm(ifm.instruction);
        execute_manager em(idm);
        memory_access_manager mam(em);
        write_back_manager wbm(mam);
        if(_jump=wbm._jump)_pc=wbm._pc;
    }
    return 0;
}
