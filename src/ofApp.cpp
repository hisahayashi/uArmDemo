#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
//    scene setup
    ofSetVerticalSync(true);
    ofSetFrameRate( 12 );
    ofBackground( ofColor( 0, 0, 0 ) );
//    ofSetBackgroundAuto( false );
    ofSetCircleResolution( 8 );
    
//    screen setup
//    ofSetWindowPosition( 0, 0 );
//    ofSetWindowShape( ofGetScreenWidth(), ofGetScreenHeight() );
//    ofSetWindowShape( 640, 480 );
    
    posX = 0; // min: -90   max: 90
    posY = 40; // min: -180  max: 150
    posZ = 0; // min: 0     max: 210
    handRot = 0; // min: -90  max: 90
    gripper = 0x02; // 0x02 open, 0x01 close
    
    serial.setup("/dev/tty.usbserial-A6031WV6", 9600);
//    serial.listDevices();
//    ofLog() << "available: " << serial.available();
//    ofLog() << "isInitialized: " << serial.isInitialized();
    
    ofLog() << "ofGetWidth: " << ofGetWidth();
    ofLog() << "ofGetHeight: " << ofGetHeight();
}

//--------------------------------------------------------------
void ofApp::update(){
    
    if( serial.isInitialized() && !stopper ){
        status = true;
    }
    else{
        status = false;
    }
    
    updateUArm();
}

void ofApp::updateUArm(){
    if( status ){
        posX = ofMap( mouseX, 0, ofGetWidth(), -90, 90, true );
        posY = ofMap( mouseY, 0, ofGetHeight(), 150, 20, true );
        posZ = ofMap( keyVertical, -50, 50, 0, 210, true );
        handRot = ofMap( keyHorizontal, -50, 50, -90, 90, true );
        setUArm();
    }
    else{
        posX = 0;
        posY = 40;
        posZ = 0;
        handRot = 0;
        gripper = 0x00;
        setUArm();
    }
    
//    ofLog() << mouseX << ", " << mouseY << ", " << keyVertical << ", " << keyHorizontal;
//    ofLog() << posX << ", " << posY << ", " << posZ;
}

void ofApp::setUArm(){
    unsigned char serialBytes[11] = {
        0xFF,
        0xAA,
        (posX >> 8) & 0xFF, posX & 0xFF,
        (posY >> 8) & 0xFF, posY & 0xFF,
        (posZ >> 8) & 0xFF, posZ & 0xFF,
        (handRot >> 8) & 0xFF, handRot & 0xFF,
        gripper
    };
    serial.writeBytes( &serialBytes[0], 11);
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor( 255, 255, 255 );
    string text = "Stop when you press the [space key].\n";
    text += "Hand angle change when you press the [left or right key].\n";
    text += "Arm height change when you press the [top or bottom key].\n\n";
    text += "Stopper: " + ofToString(status) + "\n";
    text += "posX: " + ofToString(posX) + "\n";
    text += "posY: " + ofToString(posY) + "\n";
    text += "posZ: " + ofToString(posZ) + "\n";
    text += "handRot: " + ofToString(handRot) + "\n";
    text += "gripper: " + ofToString(gripper) + "\n\n";
    text += "fps: " + ofToString(ofGetFrameRate()) + "\n";
    ofDrawBitmapString( text, 50, 50 );
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    ofLog() << key;
    
    // top: 357, botom: 359
    if( key == 357 ) keyVertical++;
    if( key == 359 ) keyVertical--;
    
    // left: 356, right: 358
    if( key == 356 ) keyHorizontal--;
    if( key == 358 ) keyHorizontal++;
    
    // change stopper
    if( key == 32 ){
        stopper = (stopper)? false: true;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){
    mouseX = x;
    mouseY = y;
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    gripper = 0x01;
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    gripper = 0x02;
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