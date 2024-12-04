//
//  OrbbecBasePanel.hpp
//  Sal-OF
//
//  Created by fuse on 09/10/24.
//

#include <stdio.h>
#include "ofxGui.h"
#include "OrbbecDevice.h"
#include "OrbbecParameters.h"

class OrbbecBasePanel : public ofxPanel{
    public:
        void addGuiComponents(OrbbecDevice *orbbecDevice);
        void addGuiComponents(OrbbecDevice *orbbecDevice, OrbbecParameters settings);
    
        void save();
        string &getFilename(){return filename;}
    
    protected:
        OrbbecDevice *orbbecDevice;
        ofxButton     connectReleaseButton;
        ofxIntSlider  minDistanceIntSlider;
        ofxIntSlider  maxDistanceIntSlider;
        ofxFloatSlider  leftMarginIntSlider;
        ofxFloatSlider  rightMarginIntSlider;
        ofxFloatSlider  topMarginIntSlider;
        ofxFloatSlider  bottomMarginIntSlider;
        ofxFloatSlider  vertCorrectionFloatSlider;
        ofxFloatSlider  keystoneFloatSlider;
        ofxFloatSlider  fisheyeFloatSlider;
        ofxButton     clearImageButton;
    
        ofxButton     saveButton;
};
