//
//  Digit.cpp
//  standupTimer_v1
//
//  Created by jan everaert on 16/02/15.
//
//
#include "Digit.h"
#include "ofUtils.h"
#include "ofTrueTypeFont.h"
Digit::Digit(int startValue, int xp, int yp){
    val = ofToString(startValue);
    x = xp;
    y = yp;
    charWidth = 0;
    
}
Digit::Digit(std::string startValue, int xp, int yp){
    val = startValue;
    x = xp;
    y = yp;
    
}

void Digit::setup(int startValue, int xPosition, int yPosition){
    val = startValue;
    x = (xPosition)*(ofGetWidth()/28);
    y = (yPosition) *(ofGetHeight()/14);
}


void Digit::draw(ofTrueTypeFont cFont, int xAdj){
    ofDisableAlphaBlending;
    int tx = (x+xAdj)*(ofGetWidth()/28);
    int ty = (y) *(ofGetHeight()/14)+(205*0.686989);
//    cFont.unbind();
    cFont.drawStringAsShapes(val, tx, ty);
    charWidth = cFont.stringWidth(val);
    
}
