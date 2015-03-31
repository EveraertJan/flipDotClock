//
//  Boards.cpp
//  FDTest
//
//  Created by Kevin Verelst on 11/02/15.
//
//

#include "Boards.h"
Boards::Boards(int adress, bool pointColor, bool tm){
    a = adress;
    pc = pointColor;
    testMode = tm;
    w = 28;
    h = 7;
}

Boards::Boards(int adress, bool pointColor, int width, int height, bool tm){
    a = adress;
    w = width;
    h = height;
    testMode = tm;
    
    pc = pointColor;
}

void Boards::setup(){
    for(int i = 0; i<w; i++){
        points.push_back( 0x7F);
    }
    rfrsh();
}

void Boards::draw(ofImage surface, int threshold, int x, int y, int elW, int elH){
    for(int i = 0; i<w; i++){
        int sub = 1;
        for(int j = 0; j<h; j++){
            
            ofVec2f p = *new ofVec2f(((elW/w)*i), (elH/h)*j);
            
            ofColor_<unsigned char> c;
            ofTexture oft;
            
            c = surface.getColor(p.x+x+9, p.y+y+9);
            
            int r = ((p.x+(elW/w))-p.x)/6;
            
            
            
            if(c.r+c.g+c.b<threshold){
                points[i] = points[i]-sub;
            } else {
                ofSetColor(250, 250, 150);
                ofEllipse((p.x+x+9)+(r), (p.y+y+9)+(r), r, r);
            }
            sub = sub*2;
        }
    }
    
}
void Boards::debug(bool state){
    if(state){
        for(int i = 0; i<points.size(); i++){
            points[i] = 0x00;
        }
    } else {
        for(int i = 0; i<points.size(); i++){
            points[i] = 0x7F;
        }
    }
}
void Boards::rfrsh(){
    for(int i = 0; i<w; i++){
        points[i] = 0x7F;
    }
}