//
// Created by Jlhsmall on 2020/7/13.
//

#include "init.h"
unsigned char memory[140000];
void init(){
    std::string s;
    int pos;
    while(std::cin>>s){
        if(s[0]=='@'){
            pos=std::stoi(s.substr(1,s.length()-1), nullptr,16);
        }
        else{
            memory[pos++]=std::stoi(s,nullptr,16);
        }
    }
}