//
//  Marquee.h
//  standupTimer_v1
//
//  Created by jan everaert on 17/02/15.
//
//

#pragma once
#include "ofMain.h"
#include "Digit.h"


class Marquee{
public:
    void setup(string text, ofTrueTypeFont cFont);
    void write();
    
    ofTrueTypeFont cf;
    std::string txet;
    std::vector <Digit> digits;
    
    
    //own input
    int startTime; //in military format
    int endTime;
    
    int passedFrames;
    
    bool scrolling;
    bool isset;
    
};