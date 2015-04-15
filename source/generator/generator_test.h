#ifndef GENERATOR_TEST_H
#define GENERATOR_TEST_H

#include "generator.h"
#include "generator_primitive.h"

using namespace std;

namespace aserver {
namespace generator {

/** \brief Test configuration for the signal primitives generated.
*/

struct TestConfigData : ConfigData {
    unsigned transitionPeriod = 22050;
    float frequencyScaleFactor = 1.5;
    double distance = 5.;
    double angleStep = M_PI/4.;
    double initialAngle = M_PI/2.;

};

/**
 * Contains the script instructions for altering the properties of the primitive during playback.
 * This script is a map with key=frame  and Entry=Location
 */

class Test :public Primitive {
private:
    unsigned transitionPeriod;
    unsigned remainingFrames;
    float frequencyScaleFactor;

    double distance; // overrides source location...
    double angleStep;
    double initialAngle;
    double currentAngle;

public:
    Test(unsigned periodSize);
    ~Test() {};
    void config(const ConfigData *configData) override;
    virtual void render() override;
};

} //end generator namespace
} //end aserver namespace

#endif