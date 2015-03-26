//
//  flip.cpp
//  FDTest
//
//  Created by Kevin Verelst on 11/02/15.
//
//

#include "flip.h"


void Flip::setup(int horizontal_boards, int vertical_boards, bool testing_noSerial){
    testMode = testing_noSerial;
    threshold = 150;
    pointColor = false;
    debugMode = false;
    int adr = 0x01;
    for(int i = 0; i<horizontal_boards; i++){
        std::vector<Boards> tmp;
        for(int j = 0; j<vertical_boards; j++){
            Boards b = *new Boards(adr, pointColor, false);
            b.setup();
            tmp.push_back(b);
            adr++;
        }
        brds.push_back(tmp);
    }
    
    ver = vertical_boards;
    hor = horizontal_boards;
    
    if(testMode){
        
    } else {
        //serCon.listDevices();
        vector <ofSerialDeviceInfo> deviceList = serCon.getDeviceList();
        serCon.setup(0, 57600); //open the first device and talk to it at 57600 baud
    }
    debugState = false;
}

void Flip::draw(ofImage surface){
    
    int elW = surface.getWidth()/(hor);
    int elH = surface.getHeight()/(ver);
    
    ofSetColor(0);
    ofRect(0, 0, ofGetWidth(), ofGetHeight());
    
    debugState = !debugState;
    
    for(int i = 0; i<hor; i++){
        for(int j = 0; j<ver; j++){
            //surface.grabScreen(i*elW, j*elH, elW, elH);
            if(debugMode){
                brds[i][j].debug(debugState);
            } else {
                brds[i][j].draw(surface, threshold, i*elW, j*elH, elW, elH);
            }
        }
    }
}

void Flip::writeFull(){
    vector<unsigned char> b;
    for(int i = 0; i<hor; i++){
        for(int j = 0; j<ver; j++){
            b.push_back(0x80);
            b.push_back(0x83);
            b.push_back(brds[i][j].a);
            for(int k = 0; k<brds[i][j].points.size(); k++){
                b.push_back(brds[i][j].points[k]);
            }
            b.push_back(0x8F);
            
            
            brds[i][j].rfrsh();
        }
    }
    serCon.drain();
    serCon.writeBytes(&b[0], b.size());
    
}

void Flip::write(){
    if(!testMode){
        for(int i = 0; i<hor; i++){
            for(int j = 0; j<ver; j++){
                serCon.writeByte(0x80);
                serCon.writeByte(0x83);
                serCon.writeByte(brds[i][j].a);
                for(int k = 0; k<brds[i][j].points.size(); k++){
                    serCon.writeByte(brds[i][j].points[k]);
                }
                serCon.writeByte(0x8F);
                brds[i][j].rfrsh();
                
            }
        }
    }
}
