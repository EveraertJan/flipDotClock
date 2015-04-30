#pragma once

#include "ofMain.h"
#include "BitChar.h"
#include "Flip.h"
#include "ofxOsc.h"


#define PORT 12345
#define NUM_MSG_STRINGS 20


class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    void addNum(int num);
    
    void getOscMessage();
    
    BitChar c;
    Flip flipdot;
    
    
    std::vector< int > toWrite;
    
    ofxOscReceiver receiver;
    
    int countDown;
    int current_msg_string;
    string msg_strings[NUM_MSG_STRINGS];
    
    
};
