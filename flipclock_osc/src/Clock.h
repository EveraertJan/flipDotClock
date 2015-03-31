//
//  Clock.h
//  standupTimer_v1
//
//  Created by jan everaert on 16/02/15.
//
//

#pragma once
#include "ofMain.h"
#include "Digit.h"
#include "ofUtils.h"

class Clock{
public:
    void setup(ofTrueTypeFont customFont);
    void update();
    string getTime();
    void drawTime();
    tm getSecondsSinceMidnight();
    void fillDigits();
    void writeDigit();
    tm sec;
    string timeString;
    vector<Digit> digits;
    
    int x;
    int y;
    int size;
    
    ofTrueTypeFont CF;
};
