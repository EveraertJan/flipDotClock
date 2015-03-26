//
//  Timer.h
//  standupTimer_v1
//
//  Created by jan everaert on 17/02/15.
//
//

#pragma once
#include "ofMain.h"

class Timr{
public:
    void setup(int length);
    void write();
    
    
    //own input
    int startTime; //in military format
    int endTime;
    
    int passedFrames;
    
    int lengthInMin;
    int rectLength;
    int secondsPassed;
};