//
//  OrbbecBasePanel.cpp
//  Sal-OF
//
//  Created by fuse on 09/10/24.
//

#include "OrbbecBasePanel.h"

void OrbbecBasePanel::addGuiComponents(OrbbecDevice *orbbecDevice){
    OrbbecParameters sett = getDefaultParams();
    addGuiComponents(orbbecDevice, sett);
}

void OrbbecBasePanel::addGuiComponents(OrbbecDevice *orbbecDevice, OrbbecParameters orbbecParams){
    OrbbecBasePanel::orbbecDevice = orbbecDevice;

    this->add(connectReleaseButton.setup("CONNECT / RELEASE"));
    connectReleaseButton.addListener(orbbecDevice, &OrbbecDevice::connectRelease);

    this->add(saveButton.setup("SAVE"));
    saveButton.addListener(this, &OrbbecBasePanel::save);

    //this->add(minDistanceIntSlider.setup("MIN DISTANCE", orbbecParams.minDistance.d, orbbecParams.minDistance.min, orbbecParams.minDistance.max));
    //minDistanceIntSlider.addListener(orbbecDevice, &OrbbecDevice::setMinDistance);
 
    /*
    this->add(maxDistanceIntSlider.setup("MAX DISTANCE", orbbecParams.maxDistance.d, orbbecParams.maxDistance.min, orbbecParams.maxDistance.max));
    maxDistanceIntSlider.addListener(orbbecDevice, &::OrbbecDevice::setMaxDistance);
    
    this->add(leftMarginIntSlider.setup("LEFT MARGIN", orbbecParams.leftMargin.d, orbbecParams.leftMargin.min, orbbecParams.leftMargin.max));
    leftMarginIntSlider.addListener(orbbecDevice, &::OrbbecDevice::setLeftMargin);
    
    this->add(rightMarginIntSlider.setup("RIGHT MARGIN", orbbecParams.rightMargin.d, orbbecParams.rightMargin.min, orbbecParams.rightMargin.max));
    rightMarginIntSlider.addListener(orbbecDevice, &::OrbbecDevice::setRightMargin);
    
    this->add(topMarginIntSlider.setup("TOP MARGIN", orbbecParams.topMargin.d, orbbecParams.topMargin.min, orbbecParams.topMargin.max));
    topMarginIntSlider.addListener(orbbecDevice, &::OrbbecDevice::setTopMargin);
    
    this->add(bottomMarginIntSlider.setup("BOTTOM MARGIN", orbbecParams.bottomMargin.d, orbbecParams.bottomMargin.min, orbbecParams.bottomMargin.max));
    bottomMarginIntSlider.addListener(orbbecDevice, &::OrbbecDevice::setBottomMargin);
    
    this->add(keystoneFloatSlider.setup("KEYSTONE", orbbecParams.keystone.d, orbbecParams.keystone.min, orbbecParams.keystone.max));
    keystoneFloatSlider.addListener(orbbecDevice, &::OrbbecDevice::setKeystone);
    
    this->add(vertCorrectionFloatSlider.setup("VERTICAL CORRECTION", orbbecParams.vertCorrection.d, orbbecParams.vertCorrection.min, orbbecParams.vertCorrection.max));
    vertCorrectionFloatSlider.addListener(orbbecDevice, &::OrbbecDevice::setVertCorrection);
    
    this->add(clearImageButton.setup("CLEAR IMAGE"));
    clearImageButton.addListener(orbbecDevice, &OrbbecDevice::clearImage);*/
}

void OrbbecBasePanel::save(){
    if(filename.size() > 1){
        this->saveToFile(filename);
    }
    else if(orbbecDevice != NULL){
        filename = orbbecDevice->getName()+ "orbbec.xml";
    }
    else{
        filename = "orbbecBasePanel.xml";
        ofLogWarning("KinectBasePanal", "filename not setted");
    }
    
    saveToFile(filename);
}