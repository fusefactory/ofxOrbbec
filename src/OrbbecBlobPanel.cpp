//
//  OrbbecBlobPanel.cpp
//  Sal-OF
//
//  Created by fuse on 09/10/24.
//
#include "OrbbecBlobPanel.h"

void OrbbecBlobPanel::addGuiComponents(OrbbecDevice *orbbecDevice, OrbbecObjectTracker *orbbecObjectTracker){
    OrbbecBasePanel::addGuiComponents(orbbecDevice);

    OrbbecBlobPanel::orbbecObjectTracker = orbbecObjectTracker;
    
    this->add(blobToggle.setup("BLOBS", true));
    blobToggle.addListener(orbbecObjectTracker, &::OrbbecObjectTracker::toggleBlobs);
   
    this->add(minAreaIntSlider.setup("MIN AREA", orbbecObjectTracker->getMinArea(), 0, 1000));
    minAreaIntSlider.addListener(orbbecObjectTracker, &::OrbbecObjectTracker::setMinArea);

    this->add(maxAreaIntSlider.setup("MAX AREA", orbbecObjectTracker->getMaxArea(), 1000, 50000));
    maxAreaIntSlider.addListener(orbbecObjectTracker, &::OrbbecObjectTracker::setMaxArea);
}
