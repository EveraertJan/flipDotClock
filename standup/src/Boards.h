//
//  Boards.h
//  FDTest
//
//  Created by Kevin Verelst on 11/02/15.
//
//


#include <stdio.h>
#include "ofMain.h"


class Boards{
public:
    Boards(int adress, bool pointColor, bool testMode);
    Boards(int adress, bool pointColor, int width, int height, bool testMode);
    void setup();
    void refresh();
    void rfrsh();
    void debug(bool state);
    void draw(ofImage s, int threshold, int x, int y, int elW, int elH);
    
    int w;
    int h;
    
    bool testMode;
    bool debugMode;
    
    int a; //adress
    bool pc;
    std::vector<int> points;
    
};

