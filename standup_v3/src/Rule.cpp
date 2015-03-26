//
//  Rule.cpp
//  standupTimer_v1
//
//  Created by jan everaert on 16/02/15.
//
//

#include "Rule.h"


void Rule::setupString(string toShow, ofTrueTypeFont customFont, int st, int et){
    floatV = 0.0f;
    CF = customFont;
    int startTime = st;
    int endTime = et;
    if(floor(startTime/100) == floor(endTime/100)){
        val = (endTime)-startTime;
    } else {
        val = (endTime-40)-startTime;
    }
    val = (val*60*10);
    marq = *new Marquee();
    marq.setup(toShow, customFont);
    marq.startTime = startTime;
    marq.endTime = endTime;
}

void Rule::setupCountDown(int st, int length){
    int startTime = st;
    int endTime = st+length;
    if(endTime-(floor(endTime/100)*100)>60){
        endTime-=60;
        endTime+=100;
    }
    timr = *new Timr();
    timr.setup(length);
    timr.startTime = startTime;
    timr.endTime = endTime;
}

void Rule::draw(std::string time){
    int timeVal = atoi(time.c_str());
    if(timeVal<marq.endTime && timeVal>=marq.startTime){
        marq.write();
    } else if(timeVal<timr.endTime && timeVal>=timr.startTime){
        timr.write();
    }
}
