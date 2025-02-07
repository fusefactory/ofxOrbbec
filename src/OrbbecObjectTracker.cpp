#include "OrbbecObjectTracker.h"

OrbbecObjectTracker::OrbbecObjectTracker(OrbbecDevice *cam) {
    OrbbecObjectTracker::orbbec = cam;
    
    colorImage.allocate(orbbec->getResolution().x, orbbec->getResolution().y);
    grayImage.allocate(orbbec->getResolution().x, orbbec->getResolution().y);
    
    fbo.allocate(orbbec->getResolution().x, orbbec->getResolution().y, GL_RGBA);
    fbo.getTexture().setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
}

void OrbbecObjectTracker::setMinArea(int &area) {
    objectMinArea = area;
}

int OrbbecObjectTracker::getMinArea() {
    return objectMinArea;
}

void OrbbecObjectTracker::setMaxArea(int &area) {
    objectMaxArea = area;
}

int OrbbecObjectTracker::getMaxArea() {
    return objectMaxArea;
}

void OrbbecObjectTracker::toggleBlobs(bool &value) {
    showBlobs = value;
}

bool OrbbecObjectTracker::showingBlobs() {
    return showBlobs;
}

void OrbbecObjectTracker::update(int maxBlobs) {
    orbbec->getProcessedTexture().readToPixels(depthPixels);
    colorImage.setFromPixels(depthPixels);
    grayImage = colorImage;
    
    contourFinder.findContours(grayImage, objectMinArea, objectMaxArea, maxBlobs, false);
}

vector<ofxCvBlob> OrbbecObjectTracker::getBlobs() {
    return contourFinder.blobs;
}

void OrbbecObjectTracker::drawBlobs(float x, float y, float width, float height) {
    float factor = fbo.getWidth() / width;
    
    fbo.begin();
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    
    ofPushStyle();
    ofSetLineWidth(factor);
    
    for (int i = 0; i < contourFinder.blobs.size(); i++ ) {
        ofxCvBlob& blob = contourFinder.blobs.at(i);
        
        int col = i > 0 ? 255 : 0;
        ofSetColor(col, 255, 0, 127);
        ofDrawRectangle(blob.boundingRect.x, blob.boundingRect.y, blob.boundingRect.width, blob.boundingRect.height);
        ofFill();
        ofSetColor(col, 255, 255, 255);
        ofDrawEllipse(blob.centroid.x, blob.centroid.y, 10 * factor, 10 * factor);
        
    }
    fbo.end();
    ofPopStyle();
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    ofSetColor(255);
    fbo.draw(x, y, width, height);
    glDisable(GL_BLEND);
}
