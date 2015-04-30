//
//  Char.cpp
//  newClock
//
//  Created by jan everaert on 24/04/15.
//
//

#include "BitChar.h"

void BitChar::setup(){
    setNum(0, 62, 34, 62);
    setNum(1, 0, 0, 62);
    setNum(2, 58, 42, 46);
    setNum(3, 42, 42, 62);
    setNum(4, 14, 8, 62);
    setNum(5, 46, 42, 58);
    setNum(6, 62, 42, 58);
    setNum(7, 2, 2, 62);
    setNum(8, 62, 42, 62);
    setNum(9, 46, 42, 62);
}


void BitChar::setNum(int i, int o, int p, int q){
    bitNum.push_back(0x7F-o);
    bitNum.push_back(0x7F-p);
    bitNum.push_back(0x7F-q);
}