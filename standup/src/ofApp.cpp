#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(10);
    ofTrueTypeFont customFont;
    cf.loadFont("flipdot.ttf", 210, true, false, true);
    clock.setup(cf);
    
    flipdot.setup(1, 2, false);
    
    
    //cout << "listening for osc messages on port " << (int)PORT << "\n";
    receiver.setup(PORT);
    
    current_msg_string = 0;
}

//--------------------------------------------------------------
void ofApp::update(){
    clock.update();
    getOscMessage();
}
//--------------------------------------------------------------
void ofApp::getOscMessage(){
    while(receiver.hasWaitingMessages()){
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
//--------------------------------------------------------------
void ofApp::draw(){
 	if(countDown>-1){
	countDown--;
	}
//	cout << countDown << "\n";
   ofFbo fbo;
    fbo.allocate(840, 420);
    fbo.begin();
    ofClear(0, 0, 0);
    
    ofSetColor(255, 150, 0);
    ofRect(0, 0, 840, 210);
    
    clock.drawTime();
    fbo.end();
    ofImage img;
    ofPixels p;
    fbo.readToPixels(p);
    img.setFromPixels(p);
if(countDown>0){

} else {
    flipdot.draw(img);
flipdot.write();
}


}
//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
