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
    serial.setup("/dev/tty.usbmodem1421", baud);
    
    // generate n boxes at random points on the surface of a sphere centered at the origin
    int sphereRadius = 1000;
    for (int i = 0; i < 500; i++) {
        float phi = ofRandom(0, TWO_PI);
        float cosTheta = ofRandom(-1, 1);
        float u = ofRandom(0, 1);
        
        float theta = acos(cosTheta);
        float r = sphereRadius * cbrt(u);
        
        ofBoxPrimitive box;
        box.set(20);
        box.setPosition(r * sin(theta) * cos(phi), r * sin(theta) * sin(phi), r * cos(theta));
        boxes.push_back(box);
        colors.push_back(ofColor::fromHsb(ofRandom(0, 255), ofRandom(0, 255), ofRandom(0, 255)));
    }
    
    firstContact = false;
    serial.flush();
    establishSerialContact();
}

//--------------------------------------------------------------
void ofApp::update(){
    ofQuaternion currentRotation = readOrientationPacketWithHandshake();
    
    cout << "w: " << currentRotation.w() << ", x: " << currentRotation.x() << ", y: " << currentRotation.y() << ", z: " << currentRotation.z() << endl;
        
//    ofMatrix4x4 rotationMatrix = ofMatrix4x4::newRotationMatrix(currentRotation);
//    rotationMatrix *= ofMatrix4x4::newScaleMatrix(-1, 1, 1);
    
//    currentRotation.set(rotationMatrix.getInverse());
    
    camera.setOrientation(currentRotation);
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(255);

    camera.begin();

    for (int i = 0; i < boxes.size(); i++) {
        ofSetColor(colors[i]);
        auto box = boxes[i];
        box.draw();
    }

    camera.end();
}

//--------------------------------------------------------------
void ofApp::establishSerialContact() {
    serial.flush();
    while (serial.available() <= 0) {
        cout << "writing contact byte..." << endl;
        serial.writeByte(FIRST_CONTACT_BYTE);
        ofSleepMillis(300);
    }
}

//--------------------------------------------------------------
ofQuaternion ofApp::readOrientationPacketWithHandshake() {
    if (serial.available() > 0) {
        int inByte = serial.readByte();
        if (!firstContact) {
            if (inByte == OF_SERIAL_ERROR) {
                ofLog(OF_LOG_ERROR, "Unrecoverable error after reading from serial.");
            } else if (inByte == FIRST_CONTACT_BYTE) {
                serial.flush();
                firstContact = true;
                cout << "first contact" << endl;
                serial.writeByte(REQUEST_PACKET_BYTE);
            }
        } else {
            int bytesRequired = 16; // four 4-byte floats
            unsigned char serialInArray[bytesRequired];
            serialInArray[0] = inByte;
            int bytesRemaining = bytesRequired - 1;
            
            memset(serialInArray, 0, bytesRequired + 1);
            
            // loop until we've read bytesRemaining bytes
            while (bytesRemaining > 0) {
                int serialInArrayOffset = bytesRequired - bytesRemaining;
                int result = serial.readBytes(&serialInArray[serialInArrayOffset], bytesRemaining);
                
                if (result == OF_SERIAL_ERROR) {
                    ofLog(OF_LOG_ERROR, "Unrecoverable error after reading from serial.");
                    break;
                } else if (result == OF_SERIAL_NO_DATA) {
                    continue;
                } else {
                    bytesRemaining -= result;
                }
            }
            
            unsigned char * bytePtr = serialInArray;
            
            float w = *(float *)bytePtr;
            float x = *(float *)(bytePtr + 4);
            float y = *(float *)(bytePtr + 8);
            float z = *(float *)(bytePtr + 12);
            
            readTime = ofGetElapsedTimef();
            
            serial.flush();
            serial.writeByte(REQUEST_PACKET_BYTE);
            
            return ofQuaternion(x, y, z, w);
        }
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
