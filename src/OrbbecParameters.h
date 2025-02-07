//
//  OrbbecParameters.h
//  Sal-OF
//
//  Created by fuse on 09/10/24.
//

class intParam {
public:
    void set(int _d, int _min, int _max){
        d = _d;
        min = _min;
        max = _max;
    }
    
    int d;
    int min;
    int max;
};

class floatParam {
public:
    void set(float _d, float _min, float _max){
        d = _d;
        min = _min;
        max = _max;
    }
    float d;
    float min;
    float max;
};

class OrbbecParameters {
    
public:
    OrbbecParameters(){};
    
    intParam minDistance;
    intParam maxDistance;
    floatParam leftMargin;
    floatParam rightMargin;
    floatParam topMargin;
    floatParam bottomMargin;
    floatParam keystone;
    floatParam fisheye;
    floatParam vertCorrection;
};

static OrbbecParameters getDefaultParams(){
    OrbbecParameters orbbecParams;
    orbbecParams.minDistance.set(1, 0, 5000);
    orbbecParams.maxDistance.set(10000, 1, 15000);
    orbbecParams.leftMargin.set(0, 0, 0.5);
    orbbecParams.rightMargin.set(0, 0, 0.5);
    orbbecParams.topMargin.set(0,0 ,0.5);
    orbbecParams.bottomMargin.set(0, 0, 0.5);
    orbbecParams.keystone.set(0.3, -1.0, 1.0);
    orbbecParams.fisheye.set(0.0, -1.0, 1.0);
    orbbecParams.vertCorrection.set(1.0, -2.0, 2.0);

    return orbbecParams;
}
