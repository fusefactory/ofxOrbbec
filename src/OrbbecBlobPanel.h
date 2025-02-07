//
//  OrbbecBlobPanel.hpp
//  Sal-OF
//
//  Created by fuse on 09/10/24.
//

#include <stdio.h>

#include <stdio.h>
#include "OrbbecBasePanel.h"
#include "OrbbecPositionObjectTracker.h"

class OrbbecBlobPanel : public OrbbecBasePanel{
    public:
        void addGuiComponents(OrbbecDevice *orbbecDevice, OrbbecObjectTracker *orbbecObjectTracker);

        ofxToggle       blobToggle;
        ofxIntSlider    minAreaIntSlider;
        ofxIntSlider    maxAreaIntSlider;
    
    protected:
        OrbbecObjectTracker *orbbecObjectTracker;
};
