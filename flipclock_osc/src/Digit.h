//
//  Digit.h
//  standupTimer_v1
//
//  Created by jan everaert on 16/02/15.
//
//

#pragma once
#include "ofMain.h"
class Digit{
public:
    Digit(int startValue, int xp, int yp);
    Digit(string startValue, int xp, int yp);
    void setup(int startValue, int xPosition, int yPosition);
    void draw(ofTrueTypeFont cFont, int xAdj);
    
    int x;
    int y;
    string val;
    int startX;
    
    int charWidth;
};