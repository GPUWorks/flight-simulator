#ifndef GLCAMERA1STPERSON_H
#define GLCAMERA1STPERSON_H

#include "glcamera.h"

class GLCamera1stPerson : public GLCamera
{
    Q_OBJECT
public:
    explicit GLCamera1stPerson();

    virtual QMatrix4x4 getProjectionMatrix();

    void setRoll(qreal roll);
    qreal roll();

private:
    qreal m_roll;
};

#endif // GLCAMERA1STPERSON_H
