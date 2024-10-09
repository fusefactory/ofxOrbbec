#pragma once
#include "OrbbecDevice.h"
#include <ofxOpenCv.h>

class OrbbecObjectTracker : public ofThread {
public:
    OrbbecObjectTracker(OrbbecDevice* camera);
    virtual void update(int maxBlobs);
    
    void setMinArea(int &area);
    void setMaxArea(int &area);
    void toggleBlobs(bool &value);
    
    int getMinArea();
    int getMaxArea();
    
    bool showingBlobs();
    void drawBlobs(float x, float y, float width, float height);
    vector<ofxCvBlob> getBlobs();

protected:
    OrbbecDevice *orbbec;
    ofPixels depthPixels;
    ofxCvContourFinder contourFinder;
    
private:
    int objectMinArea = 10, objectMaxArea = 10000;
    
    ofxCvColorImage colorImage;
    ofxCvGrayscaleImage grayImage;
    
    bool showBlobs = true;
    ofFbo fbo;
    
    std::vector<ofVec3f> objectsTracked;

};
    
