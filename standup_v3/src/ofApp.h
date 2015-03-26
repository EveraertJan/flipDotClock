#pragma once

#include "ofMain.h"
#include "Digit.h"
#include "Clock.h"
#include "Rule.h"
#include "Flip.h"

#include "ofxGifDecoder.h"
#include "ofxGifFile.h"


class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
        void draw();
        void getRules(ofTrueTypeFont cf);

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    vector<Rule> rules;
    Clock time;
    
    ofTrueTypeFont cf;
    
    Flip flip;
    
    ofxGifDecoder decoder;
    ofxGifFile gifFile;
    
};
