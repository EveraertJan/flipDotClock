//
//  Marquee.cpp
//  standupTimer_v1
//
//  Created by jan everaert on 17/02/15.
//
//

#include "Marquee.h"


void Marquee::setup(std::string txt, ofTrueTypeFont cFont){
    txet = txt;
    scrolling = false;
    isset=false;
    passedFrames = 0;
    cf = cFont;
    int tsizzl = txt.size();
    for(int i = 0; i<tsizzl; i++){
        std::string cur;
        cur.push_back(txt.at(i));
        Digit d = *new Digit(cur, 29+((4*i)), 8);
        digits.push_back(d);
    }
    if(digits.size()>6){
        scrolling = true;
    }
    isset = true;
}
void Marquee::write(){
    passedFrames++;
    int adjX= 0;
    int sizzl = digits.size();
    for(int i = 0; i<sizzl; i++){
        ofSetColor(255, 255, 255);
        digits[i].draw(cf, adjX);
        if(digits[i].charWidth<60){
            adjX-=2;
        } else if(digits[i].charWidth > 120){
            adjX+=2;
        }
        if(scrolling && passedFrames%2 == 0){
            digits[i].x--;
            if(digits[i].x == (-4)*sizzl){
                digits[i].x = 50;
            }
        }
    }
    
}