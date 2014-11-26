#ifndef GLCAMERASIMULATION_H
#define GLCAMERASIMULATION_H

#include "glcamera.h"

class GLCamera3rdPerson : public GLCamera
{
    Q_OBJECT
public:
    explicit GLCamera3rdPerson();

    virtual QMatrix4x4 getProjectionMatrix();
};

#endif // GLCAMERASIMULATION_H
