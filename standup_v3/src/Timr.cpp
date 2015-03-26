//
//  Timer.cpp
//  standupTimer_v1
//
//  Created by jan everaert on 17/02/15.
//
//

#include "Timr.h"

void Timr::setup(int length){
    rectLength = 0;
    lengthInMin = length;
    passedFrames = 0;
    secondsPassed = 0;
}
void Timr::write(){
    ofSetColor(255, 0, 255);
    passedFrames++;
    if(passedFrames % int(ofGetFrameRate()) == 0){
        secondsPassed++;
        rectLength = secondsPassed*(ofGetWidth()/(60*lengthInMin));
    }
    ofRect(0, 210, rectLength, 210);
}


