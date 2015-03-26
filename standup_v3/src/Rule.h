//
//  Rule.h
//  standupTimer_v1
//
//  Created by jan everaert on 16/02/15.
//
//
#pragma once
#include "ofMain.h"
#include "Digit.h"
#include "Marquee.h"
#include "Timr.h"

class Rule{
public:
    //give by program
    void setupString(string stringToShow, ofTrueTypeFont customFont, int startTime, int endTime);
    void setupCountDown(int startTime, int length);
    void draw(std::string time);
    
    
    
    
    Marquee marq;
    Timr timr;
    
    string name;
    //important
    
    vector<Digit> dig;
    int passedFrames;
    bool scrolling;
    ofTrueTypeFont CF;
    int val;
    float floatV;
    bool busy = false;
};