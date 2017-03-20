#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
        string ofxGetSerialString(ofSerial &serial, char until);
        string ofxTrimStringRight(string str);
        string ofxTrimStringLeft(string str);
        string ofxTrimString(string str);
		
        ofSerial	serial;
        float		readTime;					// when did we last read?
        string      serialString;
    
        float x;
        float y;
        float z;
    
        ofCamera camera;
    
        vector<ofBoxPrimitive> boxes;
        vector<ofColor> colors;
};
