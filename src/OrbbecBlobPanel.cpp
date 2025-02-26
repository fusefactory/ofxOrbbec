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
   
    this->add(minAreaIntSlider.setup("MIN AREA", orbbecObjectTracker->getMinArea(), 0, 10000));
    minAreaIntSlider.addListener(orbbecObjectTracker, &::OrbbecObjectTracker::setMinArea);

    this->add(maxAreaIntSlider.setup("MAX AREA", orbbecObjectTracker->getMaxArea(), 100, 100000));
    maxAreaIntSlider.addListener(orbbecObjectTracker, &::OrbbecObjectTracker::setMaxArea);
//    
//    this->add(stageX.setup("STAGE X", orbbecObjectTracker->getStageX(), 100, 20000));
//    stageX.addListener(orbbecObjectTracker, &::OrbbecObjectTracker::setStageX);
//    
//    this->add(stageY.setup("STAGE Y", orbbecObjectTracker->getStageY(), 100, 20000));
//    stageY.addListener(orbbecObjectTracker, &::OrbbecObjectTracker::setStageY);
//    
//    this->add(stageZ.setup("STAGE Z", orbbecObjectTracker->getStageZ(), 100, 20000));
//    stageZ.addListener(orbbecObjectTracker, &::OrbbecObjectTracker::setStageZ);
    
}
