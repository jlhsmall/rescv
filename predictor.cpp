//
// Created by Jlhsmall on 2020/7/14.
//

#include "predictor.h"
predictor pred[8];
int predictor::nxt[4][2]={{0,1},{0,3},{0,3},{2,3}};
unsigned predictor::suc=0;
unsigned predictor::tot=0;