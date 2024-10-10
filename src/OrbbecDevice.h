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

       ofVec2f getResolution() {return resolution; }
       std::string getName()  { return name ;}
       
       void setAspect(float x, float y);
       void setAspect(float x, float y, float width, float height);
       
       ofVec2f getAspectPosition(){ return aspectPosition; }       //position where draw kinect
       ofVec2f getAspectSize(){ return aspectSize;}     //size for drawing kinect
       
       void setMinDistance(int &distance);
       int getMinDistance();
       void setMaxDistance(int &distance);
       int getMaxDistance();
       void setLeftMargin(float &margin);
       float getLeftMargin();
       void setRightMargin(float &margin);
       float getRightMargin();
       void setTopMargin(float &margin);
       float getTopMargin();
       void setBottomMargin(float &margin);
       float getBottomMargin();
       void setKeystone(float &_keystone);
       float getKeystone();
       void setVertCorrection(float &_vertCorrection);
       float getVertCorrection();
       void clearImage();
       void loadKinectRecording(string _filename);
       
       ofTexture &getTexture();
       ofTexture &getProcessedTexture();
    
       ofVec3f &getCom();
       void draw();
       void drawSelected();
       
       float convertToRealWorldX(float x, float depth);
       float convertToRealWorldY(float y, float depth);
       
       //recorder
       bool readKinectRecording = true;
       string kinectRecordingFilename = "";
       ofVideoPlayer kinectRecording;
       void setReadKinectRecording(bool _readKinectRecording){readKinectRecording = _readKinectRecording;};
       bool getReadKinectRecording(){return readKinectRecording;};
       ofFbo processedTexture;
       ofShader depthShader;
       ofMatrix4x4 projectionFlat;
       ofMatrix4x4 modelviewFlat;
       
   protected:
    ofxOrbbec::Settings currentSettings;
    ofxOrbbecCamera* camera;

       
       ofVec2f resolution;
       ofVec2f fieldOfViewDegree, fieldOfViewRad;
       int minDistance, maxDistance;
       float leftMargin, rightMargin, topMargin, bottomMargin;
       float keystone, vertCorrection;
       
       bool bClearImage = false;
       unsigned int bytesPerPixel;
       
       std::string name, fullName;
       ofTexture texture;
       float *lastData;
       ofVec3f com;
       int movement = 0;
       ofVec2f aspectPosition;
       ofVec2f aspectSize;
       float XtoZ, YtoZ;
};
