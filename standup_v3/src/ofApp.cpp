#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofTrueTypeFont customFont;
    ofSetFrameRate(10);
    customFont.loadFont("flipdot.ttf", 210, true, false, true);
    time.setup(customFont);
    cf = customFont;
    
    flip.setup(1, 2, false);
    flip.pointColor = true;
    
    //decoder.decode("gif.gif");
    //gifFile = decoder.getFile();
}


//--------------------------------------------------------------
void ofApp::getRules(ofTrueTypeFont cf){
    ofXml xml;
    try{
        ofHttpResponse resp = ofLoadURL("http://crashlab.be/beyond/rules.xml");
        
        
        
        
        xml.loadFromBuffer(resp.data);
        cout << resp.data << "\n";
        cout << "went online, ";
        
    } catch( ... ){
        ofFile file;
        file.open("rules.xml"); // open a file
        ofBuffer buffer = file.readToBuffer(); // read to a buffer
        xml.loadFromBuffer(buffer);
        cout << " but it failed, yet ";
    }
    xml.setTo("doc");
    xml.setTo("rules");
    int nChildren  =xml.getNumChildren();
    ofXml t = xml;
    int n = 0;
    for(int i = 0; i<nChildren; i++){
        t.setToChild(i);
        Rule r = *new Rule();
        if(t.getAttribute("type") == "timr"){
            int start = atoi(t.getAttribute("start").c_str());
            int l = atoi(t.getAttribute("length").c_str());
            r.setupCountDown(start , l);
            r.name = t.getValue();
        } else if(t.getAttribute("type") == "marquee"){
            int start =atoi(t.getAttribute("start").c_str());
            int end = atoi(t.getAttribute("end").c_str());
            r.setupString(t.getValue(), cf, start, end);
            r.name = t.getValue();
        }
        int rL = rules.size();
        int match = 0;
        for(int i = 0; i<rL; i++){
            if(r.name == rules[i].name){
                match++;
            }
        }
        if(match==0){
            rules.push_back(r);
            n++;
        }
        t.setToSibling();
    }
    cout << rules.size() << " rules loaded succesfully, " << n << " of which are new \n";
}

//--------------------------------------------------------------
void ofApp::update(){
    time.update();
    if(ofGetFrameNum()%150 == 0){
        getRules(cf);
    }
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofFbo fbo;
    ofEnableAlphaBlending();
    fbo.allocate(840, 420);
    fbo.begin();
    
    ofClear(0, 0, 0);
    ofBackground(10, 10, 10);
    
    int rsizzl = rules.size();
    ofSetColor(255, 150, 0);
    ofRect(0, 0, 840, 210);
    
    time.drawTime();
    
    for(int i = 0; i<rsizzl; i++){
        ofSetColor(255, 255, 0);
        rules[i].draw(time.getTime());
    }
    fbo.end();
    ofImage img;
    
    ofPixels p;
    fbo.readToPixels(p);
    img.setFromPixels(p);
    //img.draw(0, 0);
    flip.draw(img);
    //ofSetColor(255, 255, 255, 50);
    //fbo.draw(0, 0);
    flip.writeFull();
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    //cout << key << "\n";
    switch(key){
        case 32:
            flip.debugMode = true;
             ofSetFrameRate(8);
        break;
            
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    if(key == 32){
        flip.debugMode = false;
        ofSetFrameRate(20);
    }
    
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
