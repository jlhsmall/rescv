//
// Created by Jlhsmall on 2020/7/8.
//

#ifndef RESCV_INSTRUCTIONFETCH_HPP
#define RESCV_INSTRUCTIONFETCH_HPP
#include "type.hpp"
class instruction_fetch_manager {
public:
    unsigned instruction;

    instruction_fetch_manager(bool _jump, unsigned _pc) {
        if (_jump)pc = _pc; else pc += 4;
        instruction = *reinterpret_cast<int *>(memory+pc);
    }
};

#endif //RESCV_INSTRUCTIONFETCH_HPP
