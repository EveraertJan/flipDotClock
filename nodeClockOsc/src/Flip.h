//
//  flip.h
//  FDTest
//
//  Created by Kevin Verelst on 11/02/15.
//
//
#pragma once
#include "ofMain.h"
#include "Boards.h"


class Flip{
public:
    void setup(int horizontal_boards, int vertical_boards, bool tm);
    void draw(ofImage surface);
    void write();
    void writeFull();
    void writeNode(std::vector<int> nodePixels);
    void writeTop(std::vector<int> nodePixels);
void writeNodeFull(std::vector<int> nodePixels);
    ofSerial serCon;
    std::vector<std::vector< Boards > > brds;
    
    
    int threshold;
    int ver;
    int hor;
    
    bool pointColor;
    bool testMode;
    bool debugMode;
    bool debugState;
    
};
