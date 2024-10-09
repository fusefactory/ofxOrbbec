//
//  OrbbecBlobPanel.cpp
//  Sal-OF
//
//  Created by fuse on 09/10/24.
//

#include "OrbbecBlobPanel.hpp"
#include <stdio.h>
#include "KinectBasePanel.hpp"
#include "KinectHandTracker.h"
#include "KinectPositionObjectTracker.h"

class KinectBlobPanel : public KinectBasePanel{
    public:
        void addGuiComponents(KinectDevice *kinectDevice, KinectObjectTracker *kinectObjectTracker);

        ofxToggle       blobToggle;
        ofxIntSlider    minAreaIntSlider;
        ofxIntSlider    maxAreaIntSlider;
    
    protected:
        KinectObjectTracker *kinectObjectTracker;
};
#endif /* KinectBlobPanel_hpp */
