//
//  OrbbecSettings.h
//  Sal-OF
//
//  Created by fuse on 08/10/24.
//

#pragma once
#include <stdio.h>
#include <string>
#include "ofxOrbbecCamera.h"


class OrbbecConfig {
    
public:

    ofxOrbbec::Settings orbbecSetting;
    
    //extra settings from previous sw versions
    int minDistance = 1, maxDistance = 10000;
    float leftMargin = 0, rightMargin = 0, topMargin = 0, bottomMargin = 0;
    float vertCorrection = 1;
    float keystone = 0;
    float fisheye = 0.0;
};
