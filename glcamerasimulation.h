#ifndef GLCAMERASIMULATION_H
#define GLCAMERASIMULATION_H

#include "glcamera.h"

class GLCameraSimulation : public GLCamera
{
    Q_OBJECT
public:
    explicit GLCameraSimulation();

    virtual QMatrix4x4 getProjectionMatrix();

    void setViewAngle(qreal viewAngle);
    void setMinDist(qreal minDist);
    void setMaxDist(qreal maxDist);

private:
    qreal m_viewAngle;
    qreal m_minDist;
    qreal m_maxDist;
};

#endif // GLCAMERASIMULATION_H
