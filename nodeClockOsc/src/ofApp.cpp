#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetWindowShape(840, 420);
    ofSetFrameRate(10);
    c.setup();
    
    flipdot.setup(1, 2, false);
    
    cout << "listening for osc messages on port " << (int)PORT << "\n";
    receiver.setup(PORT);
    
    current_msg_string = 0;
    
}

//--------------------------------------------------------------
void ofApp::update(){
    int h = ofGetHours();
    int m = ofGetMinutes();
    
    toWrite.push_back(0x7F);
    addNum(h);
    toWrite.push_back(0x7F);
    toWrite.push_back(0x7F);
    addNum(m);
    
    while(toWrite.size()<28){
        toWrite.push_back(0x7F);
    }
}

void ofApp::addNum(int num){
    if(num>=10){
        int tN = floor(num/10);
        if(tN != 1){
            toWrite.push_back(c.bitNum.at(tN*3));
            toWrite.push_back(c.bitNum.at((tN*3)+1));
            toWrite.push_back(c.bitNum.at((tN*3)+2));
        } else {
            toWrite.push_back(c.bitNum.at((tN*3)+2));
        }
        toWrite.push_back(0x7F);
        if((num-(tN*10))!=1){
            toWrite.push_back(c.bitNum.at(((num-(tN*10))*3)));
            toWrite.push_back(c.bitNum.at(((num-(tN*10))*3)+1));
            toWrite.push_back(c.bitNum.at(((num-(tN*10))*3)+2));
        } else {
            toWrite.push_back(c.bitNum.at((1*3)+2));
        }
    } else {
        toWrite.push_back(c.bitNum.at(0));
        toWrite.push_back(c.bitNum.at(1));
        toWrite.push_back(c.bitNum.at(2));
        toWrite.push_back(0x7F);
        if(num!=1){
            toWrite.push_back(c.bitNum.at((num*3)));
            toWrite.push_back(c.bitNum.at((num*3)+1));
            toWrite.push_back(c.bitNum.at((num*3)+2));
        } else {
            toWrite.push_back(c.bitNum.at((num*3)+2));
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    if(countDown>-1){
        countDown--;
    }
    if(countDown>0){
        
    } else {
        flipdot.writeTop(toWrite);
    }
    
}

void ofApp::getOscMessage(){

    while(receiver.hasWaitingMessages()){
        cout << "got message";
     std::vector<int> toDraw;
     // get the next message
     ofxOscMessage m;
     receiver.getNextMessage(&m);
     string msg_string;
     for(int i = 0; i < m.getNumArgs(); i++){
     if(m.getArgType(i) == OFXOSC_TYPE_INT32){
     msg_string += ofToString(m.getArgAsInt32(i));
     toDraw.push_back(m.getArgAsInt32(i));
     }
     else if(m.getArgType(i) == OFXOSC_TYPE_FLOAT){
     msg_string += ofToString(m.getArgAsFloat(i));
     }
     else if(m.getArgType(i) == OFXOSC_TYPE_STRING){
     msg_string += m.getArgAsString(i);
     }
     else{
     msg_string += "unknown";
     }
     msg_string+="\n";
     }
     if(countDown>0){	} else {
     //	cout << toDraw.size()<<"\n";
     if(toDraw.size() < 30){
     flipdot.writeNode(toDraw);
     } else {
     countDown = 50;
     flipdot.writeNodeFull(toDraw);
     }
     }
     }
}