#include "OrbbecPositionObjectTracker.h"



OrbbecPositionObjectTracker::OrbbecPositionObjectTracker(OrbbecDevice *cam) : OrbbecObjectTracker(cam) {
    
}

void OrbbecPositionObjectTracker::update(int maxBlobs) {
    OrbbecObjectTracker::update(maxBlobs);
    calculatePositionTracked();
}

void OrbbecPositionObjectTracker::calculatePositionTracked() {
    positionsTracked.clear();
    
    for (ofxCvBlob &blob : contourFinder.blobs) {
        // average blob/hand depth
        float posDepth = 0;
        int validPixels = 0;
        for (int x = 0; x < blob.boundingRect.width; x++) {
            for (int y = 0; y < blob.boundingRect.height; y++) {
                int index = depthPixels.getPixelIndex(blob.boundingRect.x + x, blob.boundingRect.y + y);
                float depth = (255 - depthPixels[index]) / 255.0 * (orbbec->getMaxDistance() - orbbec->getMinDistance()) + orbbec->getMinDistance();
                if (depth > 0) {
                    posDepth += depth;
                    validPixels++;
                }
            }
        }
        if (validPixels > 0) {
            posDepth /= (float)validPixels;
        }
        
        float posX = orbbec->convertToRealWorldX(blob.centroid.x, posDepth);
        float posY = orbbec->convertToRealWorldY(blob.centroid.y, posDepth); // not necessary here
        ofVec3f posTracked(posX, posY, posDepth);
        positionsTracked.push_back(posTracked);
    }
}
