#include "OrbbecDevice.h"

OrbbecDevice::OrbbecDevice(ofxOrbbecCamera* camera, ofxOrbbec::Settings _setting) : camera(camera), currentSettings(_setting), fullName(ofToString(_setting.ip)){

    resolution.x = currentSettings.depthFrameSize.requestWidth;
    resolution.y = currentSettings.depthFrameSize.requestHeight;
    
    setFieldOfView(resolution.x);
    
    std::transform(fullName.begin(), fullName.end(), fullName.begin(), ::toupper);

    XtoZ = (float)tan(fieldOfViewRad.x / 2) * 2;
    YtoZ = (float)tan(fieldOfViewRad.y / 2) * 2;

    const int numOfPixels = resolution.x * resolution.y;
    lastData = new float[numOfPixels];		
    texture.allocate(resolution.x, resolution.y, GL_R16F);
    texture.setTextureMinMagFilter(GL_NEAREST, GL_NEAREST); // for collison map
    processedTexture.allocate(resolution.x, resolution.y, GL_RGB);

    // init black texture
    float *data = new float[numOfPixels];
    for (int i = 0; i < resolution.x * resolution.y * 3; i++) {
        data[i] = 0.0;
    }
    texture.loadData(data, resolution.x, resolution.y, GL_R16F);
    delete[] data;

    depthShader = new ofxAutoReloadedShader();
    depthShader->load("shaders/depth");

    float viewW = resolution.x;
    float viewH = resolution.y;

    float fov = 60.0;
    float eyeX = viewW / 2.0;
    float eyeY = viewH / 2.0;
    float halfFov = PI * fov / 360;
    float theTan = tanf(halfFov);
    float cameraDist = eyeY / theTan;
    float aspect = (float) viewW /  (float)viewH;
    float nearDist = cameraDist / 10.0f;
    float farDist = cameraDist * 10.0f;
    projectionFlat.makeIdentityMatrix();
    projectionFlat.makePerspectiveMatrix(fov, aspect, nearDist, farDist);
    modelviewFlat.makeIdentityMatrix();
    modelviewFlat.makeLookAtViewMatrix(ofVec3f(eyeX, eyeY, cameraDist), ofVec3f(eyeX, eyeY, 0), ofVec3f(0.0, 1.0, 0.0));
    
    }
    void OrbbecDevice::start() {
        camera->open(currentSettings);
    }
     
    void OrbbecDevice::stop() {
        if (camera->isConnected())
            camera->close();
    }
     
    bool OrbbecDevice::isRunning() {
        return camera->isConnected();
    }

    void OrbbecDevice::connectRelease(){
        if (isRunning()) {
            stop();
        } else {
            start();
        }
    }

    void OrbbecDevice::setMinDistance(int &distance) {
        minDistance = distance;
    }

    int OrbbecDevice::getMinDistance() {
        return minDistance;
    }

    void OrbbecDevice::setMaxDistance(int &distance) {
        maxDistance = distance;
    }

    int OrbbecDevice::getMaxDistance() {
        return maxDistance;
    }

    void OrbbecDevice::setLeftMargin(float &margin) {
        leftMargin = margin;
    }

    float OrbbecDevice::getLeftMargin() {
        return leftMargin;
    }

    void OrbbecDevice::setRightMargin(float &margin) {
        rightMargin = margin;
    }

    float OrbbecDevice::getRightMargin() {
        return rightMargin;
    }

    void OrbbecDevice::setTopMargin(float &margin) {
        topMargin = margin;
    }

    float OrbbecDevice::getTopMargin() {
        return topMargin;
    }

    void OrbbecDevice::setBottomMargin(float &margin) {
        bottomMargin = margin;
    }

    float OrbbecDevice::getBottomMargin() {
        return bottomMargin;
    }

    void OrbbecDevice::setKeystone(float &_keystone) {
        keystone = _keystone;
    }

    void OrbbecDevice::setFisheye(float &_fisheye) {
        fisheye = _fisheye;
    }

    float OrbbecDevice::getKeystone() {
        return keystone;
    }

    float OrbbecDevice::getFisheye() {
        return fisheye;
    }
    void OrbbecDevice::setVertCorrection(float &_vertCorrection) {
        vertCorrection = _vertCorrection;
    }

    float OrbbecDevice::getVertCorrection() {
        return vertCorrection;
    }

    void OrbbecDevice::clearImage(){
        bClearImage = true;
    }

void OrbbecDevice::setFieldOfView(int resX){
    switch(resX){
        case 512:
        case 1024:
            fieldOfViewDegree.set(120, 120);
            break;
        case 640:
        case 320:
            fieldOfViewDegree.set(75, 65);
            break;
        default:
            break;
    }
    fieldOfViewRad.set(ofDegToRad(fieldOfViewDegree.x), ofDegToRad(fieldOfViewDegree.y));
}

    void OrbbecDevice::loadKinectRecording(string _filename){
        kinectRecordingFilename = _filename;
        if(kinectRecording.load(kinectRecordingFilename)){
            kinectRecording.setLoopState(OF_LOOP_NORMAL);
            kinectRecording.play();
            readKinectRecording = true;
        }
    }

    void OrbbecDevice::update() {
        ofFbo texTest2;
        texTest2.allocate(320,288,GL_RGB);
        texTest2.begin();
        ofClear(0.0, 0.0, 0.0, 255.0);
        float depth = blob1DemoPos.z * 255.0;
        ofSetColor(depth);
        ofDrawEllipse(1.5*blob1DemoPos.x*320.0, blob1DemoPos.y*288.0, 40, 40);
        depth = blob2DemoPos.z * 255.0;
        ofDrawEllipse(1.5*blob2DemoPos.x*320.0, blob2DemoPos.y*288.0, 40, 40);
        texTest2.end();
        
        if (true) { //isRunning()){
            camera->update();
         
            if (camera->isFrameNewDepth()) {
                auto depthPix = camera->getDepthPixels();
                texture.loadData(depthPix);
            }
            
            glDisable(GL_BLEND);
            processedTexture.begin();
            depthShader->begin();
            
            depthShader->setUniform1f("kinectWidth", resolution.x);
            depthShader->setUniform1f("kinectHeight", resolution.y);
            depthShader->setUniform1f("kinectHalfWidth", resolution.x / 2.0f);
            depthShader->setUniform1f("kinectHalfHeight", resolution.y / 2.0f);
            
            depthShader->setUniformMatrix4f("modelview", modelviewFlat);
            depthShader->setUniformMatrix4f("projection", projectionFlat);
           
            float inc = 0.01;
            blob1DemoNoise.x += inc;
            blob1DemoPos.x = ofNoise(blob1DemoNoise.x);
            blob1DemoNoise.y += inc;
            blob1DemoPos.y = ofNoise(blob1DemoNoise.y);
            blob1DemoNoise.z += inc;
            blob1DemoPos.z = ofNoise(blob1DemoNoise.z);

            blob2DemoNoise.x += inc;
            blob2DemoPos.x = ofNoise(blob2DemoNoise.x);
            blob2DemoNoise.y += inc;
            blob2DemoPos.y = ofNoise(blob2DemoNoise.y);
            blob2DemoNoise.z += inc;
            blob2DemoPos.z = ofNoise(blob2DemoNoise.z);
            

            
            ofImage texTest;
            texTest.load(ofToDataPath("patterns/test_pattern_fuse_512x512.png"));
            
            depthShader->setUniformTexture("tex0", texture, 0);
//            depthShader->setUniformTexture("tex0", texTest2.getTexture(), 0);
            
            depthShader->setUniform1f("onlyDepth", 1);
            depthShader->setUniform1f("maxDistance", 10000);
            
            //distance
            depthShader->setUniform1f("near", minDistance);
            depthShader->setUniform1f("far", maxDistance);
            
            depthShader->setUniform1f("lens", 1.0); //lensFactor);
            
            //crop
            depthShader->setUniform1f("top", topMargin * resolution.y);
            depthShader->setUniform1f("bottom", resolution.y - bottomMargin * resolution.y);
            depthShader->setUniform1f("right", resolution.x - rightMargin * resolution.x);
            depthShader->setUniform1f("left", leftMargin * resolution.x);
            
            //offset
            depthShader->setUniform1f("x", 0.0); //-xKinect);
            depthShader->setUniform1f("y", 0.0); //yKinect);
           
            depthShader->setUniform2f("mouse", ofVec2f(float(ofGetMouseX())/float(ofGetWidth()), float(ofGetMouseY())/float(ofGetHeight()))); //yKinect);

            depthShader->setUniform1f("noiseT", 1.0); //scaleKinect);
            
            //Scale
            depthShader->setUniform1f("scale", 1.0); //scaleKinect);
            
            //keystone
            depthShader->setUniform1f("keystone", keystone);
            depthShader->setUniform1f("fisheye", fisheye);

            //correction
            depthShader->setUniform1f("correction", vertCorrection); //correctionKinect);
            
            ofClear(0, 0, 0, 255);
            ofSetColor(255,255,255,255);
            texture.draw(0.0,0.0, resolution.x, resolution.y);
//            texTest2.getTexture().draw(0.0,0.0, resolution.x, resolution.y);
            
            depthShader->end();
            processedTexture.end();
        }

        if(readKinectRecording){
            kinectRecording.update();
            processedTexture.begin();
            ofClear(0, 0, 0, 255);
            ofSetColor(255,255,255,255);
            kinectRecording.draw(0.0,0.0, resolution.x, resolution.y);
            processedTexture.end();
        }
    }

    ofTexture &OrbbecDevice::getTexture() {
        return texture;
    }

ofTexture &OrbbecDevice::getProcessedTexture() {
    return processedTexture.getTexture();
    }

    ofVec3f &OrbbecDevice::getCom() {
        return com;
    }

    void OrbbecDevice::setAspect(float x, float y){
        setAspect(x, y, resolution.x, resolution.y);
    }

    void OrbbecDevice::setAspect(float x, float y, float width, float height) {
        OrbbecDevice::aspectPosition.set(x, y);
        OrbbecDevice::aspectSize.set(width, height);
    }

    void OrbbecDevice::draw() {
        ofSetColor(255);
            if(texture.isAllocated() && processedTexture.isAllocated())
                processedTexture.draw(aspectPosition.x, aspectPosition.y, aspectSize.x, aspectSize.y);
        
        ofDrawBitmapStringHighlight(fullName, aspectPosition.x + 20, aspectPosition.y + 20);
        if (isRunning() || readKinectRecording) {
            ofSetColor(0, 255, 0, 255);
        } else {
            ofSetColor(255, 0, 0, 255);
        }
        ofDrawRectangle(aspectPosition.x + 10, aspectPosition.y + 6, 4, 20);
        ofSetColor(0, 0, 255);
        ofDrawLine(aspectPosition.x + aspectSize.x / 2.0, aspectPosition.y, aspectPosition.x + aspectSize.x / 2.0, aspectPosition.y + aspectSize.y);
        ofDrawLine(aspectPosition.x, aspectPosition.y + aspectSize.y / 2.0, aspectPosition.x + aspectSize.x, aspectPosition.y + aspectSize.y /2.0);
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

