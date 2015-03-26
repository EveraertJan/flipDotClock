//
//  Clock.cpp
//  standupTimer_v1
//
//  Created by jan everaert on 16/02/15.
//
//

#include "Clock.h"

void Clock::setup(ofTrueTypeFont customFont){
    Digit d = *new Digit(ofToString(1), 1, 1);
    digits.push_back(d);
    d = *new Digit(ofToString(1), 5, 1);
    digits.push_back(d);
    d = *new Digit(ofToString(1), 10, 1);
    digits.push_back(d);
    d = *new Digit(0, 14, 1);
    digits.push_back(d);
    CF = customFont;
    size = 280;
}
void Clock::update(){
    sec = getSecondsSinceMidnight();
    fillDigits();
}
void Clock::drawTime(){
    int adjX= 0;
    ofSetColor(0, 0, 0);
    int sizzl = digits.size();
    for(int i = 0; i<sizzl; i++){
        digits[i].draw(CF, adjX);
        if(digits[i].charWidth<60){
            adjX-=2;
        }
    }
}
string Clock::getTime(){
    //return time in hh:mm
    string h;
    string m;
    if(sec.tm_hour<10){
        h = "0"+ofToString(sec.tm_hour, 0);
    } else {
        h = ofToString(sec.tm_hour, 0);
    }
    if(sec.tm_min<10){
        m = "0"+ofToString(sec.tm_min, 0);
    } else {
        m = ofToString(sec.tm_min, 0);
    }
    timeString = h+m;
    return timeString;
}


tm Clock::getSecondsSinceMidnight(){
    time_t curr;
    time_t t = time(&curr);
    tm* d = localtime(&t);
    return *d;
}


void Clock::fillDigits(){
    int h = sec.tm_hour;
    int d0 = floor(h/10);
    int d1 = h-(d0*10);
    
    int m = sec.tm_min;
    int d2 = floor(m/10);
    int d3 = m-(d2*10);
    digits[0].val = ofToString(d0, 0);
    digits[1].val = ofToString(d1, 0);
    digits[2].val = ofToString(d2, 0);
    digits[3].val = ofToString(d3, 0);
}