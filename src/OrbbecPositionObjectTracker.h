#pragma once
#include "OrbbecObjectTracker.h"
#include "OrbbecDevice.h"

class OrbbecPositionObjectTracker : public OrbbecObjectTracker {
public:
    OrbbecPositionObjectTracker(OrbbecDevice* camera);

    void update(int maxBlobs = 10);
    std::vector<ofVec3f> &getPositionsTracked() {return positionsTracked;}

private:
    std::vector<ofVec3f> positionsTracked;

    void calculatePositionTracked();
};


