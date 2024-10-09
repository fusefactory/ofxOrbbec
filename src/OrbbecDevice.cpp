#include "OrbbecDevice.h"

OrbbecDevice::OrbbecDevice(ofxOrbbecCamera* camera, ofxOrbbec::Settings _setting)
: camera(camera), resolution(_setting.depthFrameSize.requestWidth, _setting.depthFrameSize.requestHeight),
      fieldOfViewDegree(50), minDistance(0), maxDistance(10000), leftMargin(0), rightMargin(0),
topMargin(0), bottomMargin(0), keystone(0), vertCorrection(0), bClearImage(false), name("Orbbec"), fullName(_setting.deviceSerial) {
        fieldOfViewRad.set(ofDegToRad(fieldOfViewDegree.x), ofDegToRad(fieldOfViewDegree.y));
        XtoZ = (float)tan(fieldOfViewRad.x / 2) * 2;
        YtoZ = (float)tan(fieldOfViewRad.y / 2) * 2;
    texture.allocate(resolution.x, resolution.y, GL_R16F);
        texture.setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
          
          currentSettings = _setting;
}


void OrbbecDevice::start() {
    camera->open(currentSettings);
}

void OrbbecDevice::stop() {
    camera->close();
}

bool OrbbecDevice::isRunning() {
    return camera->isConnected();
}

void OrbbecDevice::update() {
    camera->update();

    if (camera->isFrameNewDepth()) {
        auto depthPix = camera->getDepthPixels();
        texture.loadData(depthPix);
    }
}

ofVec2f OrbbecDevice::getResolution() {
    return resolution;
}

std::string OrbbecDevice::getName() {
    return name;
}

void OrbbecDevice::setAspect(float x, float y) {
    setAspect(x, y, resolution.x, resolution.y);
}

void OrbbecDevice::setAspect(float x, float y, float width, float height) {
    aspectPosition.set(x, y);
    aspectSize.set(width, height);
}

ofVec2f OrbbecDevice::getAspectPosition() {
    return aspectPosition;
}

ofVec2f OrbbecDevice::getAspectSize() {
    return aspectSize;
}

void OrbbecDevice::setMinDistance(int distance) {
    minDistance = distance;
}

int OrbbecDevice::getMinDistance() {
    return minDistance;
}

void OrbbecDevice::setMaxDistance(int distance) {
    maxDistance = distance;
}

int OrbbecDevice::getMaxDistance() {
    return maxDistance;
}

void OrbbecDevice::setLeftMargin(float margin) {
    leftMargin = margin;
}

float OrbbecDevice::getLeftMargin() {
    return leftMargin;
}

void OrbbecDevice::setRightMargin(float margin) {
    rightMargin = margin;
}

float OrbbecDevice::getRightMargin() {
    return rightMargin;
}

void OrbbecDevice::setTopMargin(float margin) {
    topMargin = margin;
}

float OrbbecDevice::getTopMargin() {
    return topMargin;
}

void OrbbecDevice::setBottomMargin(float margin) {
    bottomMargin = margin;
}

float OrbbecDevice::getBottomMargin() {
    return bottomMargin;
}

void OrbbecDevice::setKeystone(float keystone) {
    this->keystone = keystone;
}

float OrbbecDevice::getKeystone() {
    return keystone;
}

void OrbbecDevice::setVertCorrection(float vertCorrection) {
    this->vertCorrection = vertCorrection;
}

float OrbbecDevice::getVertCorrection() {
    return vertCorrection;
}

void OrbbecDevice::clearImage() {
    /* ofPixels pixels(resolution.x, resolution.y, OF_IMAGE_GRAYSCALE);
    memset(pixels.getData(), 0, resolution.x * resolution.y);
    texture.loadData(pixels);*/
}

ofTexture& OrbbecDevice::getTexture() {
    return texture;
}

ofVec3f& OrbbecDevice::getCom() {
    return com;
}

void OrbbecDevice::draw() {
    ofSetColor(255);
    if (texture.isAllocated()) {
        texture.draw(aspectPosition.x, aspectPosition.y, aspectSize.x, aspectSize.y);
    }
    ofDrawBitmapStringHighlight(fullName, aspectPosition.x + 20, aspectPosition.y + 20);
    if (isRunning()) {
        ofSetColor(0, 255, 0, 255);
    } else {
        ofSetColor(255, 0, 0, 255);
    }
    ofDrawRectangle(aspectPosition.x + 10, aspectPosition.y + 6, 4, 20);
    ofSetColor(0, 0, 255);
    ofDrawLine(aspectPosition.x + aspectSize.x / 2.0, aspectPosition.y, aspectPosition.x + aspectSize.x / 2.0, aspectPosition.y + aspectSize.y);
}

void OrbbecDevice::drawSelected() {
    ofSetColor(20, 97, 189);
    ofDrawRectangle(aspectPosition.x + 4, aspectPosition.y + 6, 4, 20);
}

float OrbbecDevice::convertToRealWorldX(float x, float depth) {
    return (x / resolution.x - 0.5f) * depth * XtoZ;
}

float OrbbecDevice::convertToRealWorldY(float y, float depth) {
    return (0.5f - y / resolution.y) * depth * YtoZ;
}
