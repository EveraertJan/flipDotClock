//
//  flip.cpp
//  FDTest
//
//  Created by Kevin Verelst on 11/02/15.
//
//

#include "Flip.h"


void Flip::setup(int horizontal_boards, int vertical_boards, bool testing_noSerial){
    testMode = testing_noSerial;
    debugMode = false;
    if(testMode){
        
    } else {
        //serCon.listDevices();
        vector <ofSerialDeviceInfo> deviceList = serCon.getDeviceList();
        serCon.setup(0, 57600); //open the first device and talk to it at 57600 baud
    }
    debugState = false;
}

void Flip::writeFull(){
    if(!testMode){
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
}
void Flip::writeNode(std::vector<int> nodePixels){
    if(!testMode){
        serCon.writeByte(0x80);
        serCon.writeByte(0x83);
        serCon.writeByte(0x02);
        for(int k = 0; k<nodePixels.size(); k++){
            serCon.writeByte(nodePixels[k]);
        }
        serCon.writeByte(0x8F);
        serCon.drain();
        
    }
}

void Flip::writeTop(std::vector<int> nodePixels){
    if(!testMode){
        serCon.writeByte(0x80);
        serCon.writeByte(0x83);
        serCon.writeByte(0x01);
        for(int k = 0; k<nodePixels.size(); k++){
            serCon.writeByte(nodePixels[k]);
        }
        serCon.writeByte(0x8F);
        serCon.drain();
        
    }
}

void Flip::writeNodeFull(std::vector<int> nodePixels){
    if(!testMode){
        serCon.writeByte(0x80);
        serCon.writeByte(0x83);
        serCon.writeByte(0x01);
        for(int k = 0; k<28; k++){
            serCon.writeByte(nodePixels[k]);
        }
        serCon.writeByte(0x8F);
        serCon.writeByte(0x80);
        serCon.writeByte(0x83);
        serCon.writeByte(0x02);
        for(int k = 28; k<nodePixels.size(); k++){
            serCon.writeByte(nodePixels[k]);
        }
        serCon.writeByte(0x8F);
        serCon.drain();
        
    }
    cout << "init \n";
}
