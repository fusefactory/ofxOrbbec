//
//  OrbbecBasePanel.cpp
//  Sal-OF
//
//  Created by fuse on 09/10/24.
//

#include "OrbbecBasePanel.hpp"

void OrbbecBasePanel::addGuiComponents(OrbbecDevice *orbbecDevice){
    ofxOrbbec::Settings kinectSettings = getDefaultKinectSettings();
    
    addGuiComponents(orbbecDevice, kinectSettings);
}

void OrbbecBasePanel::addGuiComponents(OrbbecDevice *orbbecDevice, ofxOrbbec::Settings kinectSettings){
    OrbbecBasePanel::orbbecDevice = orbbecDevice;
    
    this->add(connectReleaseButton.setup("CONNECT / RELEASE"));
    /*connectReleaseButton.addListener(orbbecDevice, &OrbbecDevice::connectRelease);
    
    this->add(saveButton.setup("SAVE"));
    saveButton.addListener(this, &OrbbecBasePanel::save);
    
    this->add(minDistanceIntSlider.setup("MIN DISTANCE", kinectSettings.minDistance.d, kinectSettings.minDistance.min, kinectSettings.minDistance.max));
    minDistanceIntSlider.addListener(orbbecDevice, &OrbbecDevice::setMinDistance);
    
    this->add(maxDistanceIntSlider.setup("MAX DISTANCE", kinectSettings.maxDistance.d, kinectSettings.maxDistance.min, kinectSettings.maxDistance.max));
    maxDistanceIntSlider.addListener(orbbecDevice, &OrbbecDevice::setMaxDistance);
    
    this->add(leftMarginIntSlider.setup("LEFT MARGIN", kinectSettings.leftMargin.d, kinectSettings.leftMargin.min, kinectSettings.leftMargin.max));
    leftMarginIntSlider.addListener(orbbecDevice, &OrbbecDevice::setLeftMargin);
    
    this->add(rightMarginIntSlider.setup("RIGHT MARGIN", kinectSettings.rightMargin.d, kinectSettings.rightMargin.min, kinectSettings.rightMargin.max));
    rightMarginIntSlider.addListener(orbbecDevice, &OrbbecDevice::setRightMargin);
    
    this->add(topMarginIntSlider.setup("TOP MARGIN", kinectSettings.topMargin.d, kinectSettings.topMargin.min, kinectSettings.topMargin.max));
    topMarginIntSlider.addListener(orbbecDevice, &OrbbecDevice::setTopMargin);
    
    this->add(bottomMarginIntSlider.setup("BOTTOM MARGIN", kinectSettings.bottomMargin.d, kinectSettings.bottomMargin.min, kinectSettings.bottomMargin.max));
    bottomMarginIntSlider.addListener(orbbecDevice, &OrbbecDevice::setBottomMargin);
    
    this->add(keystoneFloatSlider.setup("KEYSTONE", kinectSettings.keystone.d, kinectSettings.keystone.min, kinectSettings.keystone.max));
    keystoneFloatSlider.addListener(orbbecDevice, &OrbbecDevice::setKeystone);
    
    this->add(vertCorrectionFloatSlider.setup("VERTICAL CORRECTION", kinectSettings.vertCorrection.d, kinectSettings.vertCorrection.min, kinectSettings.vertCorrection.max));
    vertCorrectionFloatSlider.addListener(orbbecDevice, &OrbbecDevice::setVertCorrection);
    
    this->add(clearImageButton.setup("CLEAR IMAGE"));
    clearImageButton.addListener(orbbecDevice, &OrbbecDevice::clearImage);
     */
}

void OrbbecBasePanel::save(){
    if(filename.size() > 1){
        this->saveToFile(filename);
    }
    else if(orbbecDevice != NULL){
        filename = orbbecDevice->getName()+ "kinect.xml";
    }
    else{
        filename = "kinectPasePanel.xml";
        ofLogWarning("KinectBasePanal", "filename not setted");
    }
    
    saveToFile(filename);
}
