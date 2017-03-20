#include "ofApp.h"
#include <regex>

//--------------------------------------------------------------
void ofApp::setup(){
    serial.listDevices();
    vector <ofSerialDeviceInfo> deviceList = serial.getDeviceList();
    
    // this should be set to whatever com port your serial device is connected to.
    // (ie, COM4 on a pc, /dev/tty.... on linux, /dev/tty... on a mac)
    // arduino users check in arduino app....
    int baud = 9600;
    serial.setup("/dev/cu.usbmodem1421", baud);

    serialString = "";
//    
//    for (int i = 0; i < 100; i++) {
//        ofBoxPrimitive box;
//        box.set(20);
//        box.setPosition(ofRandom(0, ofGetWidth()), ofRandom(0, ofGetHeight()), ofRandom(-1000, 1000));
//        boxes.push_back(box);
//        colors.push_back(ofColor::fromHsb(ofRandom(0, 255), ofRandom(0, 255), ofRandom(0, 255)));
//    }
}

//--------------------------------------------------------------
void ofApp::update(){
    serialString = "";
    serialString = ofxGetSerialString(serial,'\n'); //read until end of line
    if (serialString.length() > 0) {
        readTime = ofGetElapsedTimef();
        
        regex re("X: (.*)\tY: (.*)\tZ: (.*)");
        smatch match;
        if (regex_match(serialString, match, re) && match.size() > 1) {
            x = stof(match.str(1));
            y = stof(match.str(2));
            z = stof(match.str(3));
            cout << "x: " << match.str(1) << ", y: " << match.str(2) << ", z: " << match.str(3) << endl;
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
//    ofBackground(255);
//    
//    camera.begin();
//    
//    ofPushMatrix();
//    
//    ofTranslate(0, 0, 0);
//    ofRotateX(ofMap(y, 0, 360, 0, 360) + ofMap(ofGetMouseX(), 0, ofGetWidth(), -360, 360));
//    ofRotateY(ofMap(x, -80, 80, 0, 360) + ofMap(ofGetMouseY(), 0, ofGetHeight(), -360, 360));
//    ofRotateZ(ofMap(z, -180, 180, 0, 360));
//    
//    ofSetColor(ofColor::black);
//    for (int i = 0; i < boxes.size(); i++) {
//        auto box = boxes[i];
//        box.draw();
//    }
//    
//    ofPopMatrix();
//    
//    camera.end();

    int h = ofMap(x, 0, 360, 0, 255);
    int b = ofMap(y, -80, 80, 0, 255);
    int s = ofMap(z, -180, 180, 0, 255);
    ofColor color = ofColor::fromHsb(h, s, b);
    ofBackground(color);
}

//--------------------------------------------------------------
string ofApp::ofxGetSerialString(ofSerial &serial, char until) {
    static string str;
    stringstream ss;
    char ch;
    int ttl=1000;
    while ((ch=serial.readByte())>0 && ttl-->0 && ch!=until) {
        ss << ch;
    }
    str+=ss.str();
    if (ch==until) {
        string tmp=str;
        str="";
        return ofxTrimString(tmp);
    } else {
        return "";
    }
}

//--------------------------------------------------------------
// trim trailing spaces
string ofApp::ofxTrimStringRight(string str) {
    size_t endpos = str.find_last_not_of(" \t\r\n");
    return (string::npos != endpos) ? str.substr( 0, endpos+1) : str;
}

//--------------------------------------------------------------
// trim trailing spaces
string ofApp::ofxTrimStringLeft(string str) {
    size_t startpos = str.find_first_not_of(" \t\r\n");
    return (string::npos != startpos) ? str.substr(startpos) : str;
}

//--------------------------------------------------------------
string ofApp::ofxTrimString(string str) {
    return ofxTrimStringLeft(ofxTrimStringRight(str));;
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
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

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
