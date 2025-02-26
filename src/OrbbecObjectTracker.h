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
    
    void setStageX(float &size);
    void setStageY(float &size);
    void setStageZ(float &size);
    
    int getMinArea();
    int getMaxArea();
    
    float getStageX() {
        return stageX;
    };
    float getStageY() {
        return stageY;
    };
    float getStageZ() {
        return stageZ;
    };
    
    bool showingBlobs();
    void drawBlobs(float x, float y, float width, float height);
    vector<ofxCvBlob> getBlobs();

    OrbbecDevice *orbbec;
protected:
    ofPixels depthPixels;
    ofxCvContourFinder contourFinder;
    
private:
    int objectMinArea = 10, objectMaxArea = 10000;
    
    float stageX = 9000, stageY = 9000, stageZ = 9000;
    
    ofxCvColorImage colorImage;
    ofxCvGrayscaleImage grayImage;
    
    bool showBlobs = true;
    ofFbo fbo;
    
    std::vector<ofVec3f> objectsTracked;

};
    
