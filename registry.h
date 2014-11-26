#ifndef REGISTRY_H
#define REGISTRY_H

/*
 * `Registry` class is a special static class which provide all
 * necessary information for correct work of 3D- and Physics-engine.
 *
 * `ControlWindow` class adjusts `Registry` class each time the 'Save'
 * button clicked.
 */

#include <QObject> // for `qreal`
#define SEC 1000.0
#define DELTA 0.01
#define MOUSE_SENSITIVITY 0.005
#define KEY_SENSITIVITY 0.5

class Registry
{
public: // Physical constants
    static qreal pcGravity;
    static qreal pcResist;
    static qreal FPSphys;
    static qreal FPSrender;

public: // Quadrotor's options
    static qreal qoMass;
    static qreal qoTorqueLim;
    static qreal qoActionProbability;
    static qreal qoCameraViewAngle;
    static qreal qoCameraViewDistance;

public:
    /*
     * Sensors' noise:
     *  - GPS (coordinates)
     *  - Gyroscope (angles)
     *  - Velocity sensor
     *  - Camera
     *  - TODO: Rangefinder
     *
     * Noise - randomly distributed random variable
     * which user can set up manually before starting
     * the simulation.
     */
    static qreal noiseGPS;
    static qreal noiseGPSExpectation;
    static qreal noiseGPSStd;

    static qreal noiseGyr;
    static qreal noiseGyrExpectation;
    static qreal noiseGyrStd;

    static qreal noiseVel;
    static qreal noiseVelExpectation;
    static qreal noiseVelStd;

    static qreal noiseCam;
    static qreal noiseCamExpectation;
    static qreal noiseCamStd;
};

#endif // REGISTRY_H
