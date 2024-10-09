#include "ofxOrbbecCamera.h"
#pragma once

class OrbbecDevice {
public:
    OrbbecDevice(ofxOrbbecCamera* camera, ofxOrbbec::Settings setting);

    void start();
    void stop();
    bool isRunning();
    void update();
    void connectRelease();

    ofVec2f getResolution();
    std::string getName();

    void setAspect(float x, float y);
    void setAspect(float x, float y, float width, float height);

    ofVec2f getAspectPosition();
    ofVec2f getAspectSize();

    void setMinDistance(int distance);
    int getMinDistance();
    void setMaxDistance(int distance);
    int getMaxDistance();

    void setLeftMargin(float margin);
    float getLeftMargin();
    void setRightMargin(float margin);
    float getRightMargin();
    void setTopMargin(float margin);
    float getTopMargin();
    void setBottomMargin(float margin);
    float getBottomMargin();

    void setKeystone(float keystone);
    float getKeystone();
    void setVertCorrection(float vertCorrection);
    float getVertCorrection();

    void clearImage();

    ofTexture& getTexture();
    ofVec3f& getCom();

    void draw();
    void drawSelected();

    float convertToRealWorldX(float x, float depth);
    float convertToRealWorldY(float y, float depth);

private:
    ofxOrbbec::Settings currentSettings;
    ofxOrbbecCamera* camera;
    ofVec2f resolution;
    ofVec2f fieldOfViewDegree;
    ofVec2f fieldOfViewRad;
    int minDistance;
    int maxDistance;
    float leftMargin;
    float rightMargin;
    float topMargin;
    float bottomMargin;
    float keystone;
    float vertCorrection;
    bool bClearImage;
    std::string name;
    std::string fullName;
    ofTexture texture;
    ofVec3f com;
    ofVec2f aspectPosition;
    ofVec2f aspectSize;
    float XtoZ;
    float YtoZ;
};
