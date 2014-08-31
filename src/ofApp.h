#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    
    ofSerial serial;
    
    void updateUArm();
    void setUArm();
    
    bool status = false;
    bool stopper = false;
    
    int mouseX;
    int mouseY;
    int keyVertical = 0;
    int keyHorizontal = 0;
    
    int posX;
    int posY;
    int posZ;
    int handRot;
    int gripper;
    
};
