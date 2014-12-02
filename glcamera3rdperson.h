#ifndef GLCAMERASIMULATION_H
#define GLCAMERASIMULATION_H

#include "glcamera.h"
#include <QVector3D>

class GLCamera3rdPerson : public GLCamera
{
    Q_OBJECT
public:
    explicit GLCamera3rdPerson();

    void setCenter(QVector3D center);

    void addR(qreal delta);
    void addTheta(qreal delta);
    void addPhi(qreal delta);

    virtual QMatrix4x4 getProjectionMatrix();

private:
    QVector3D m_center;
    qreal m_R;
    qreal m_theta;
    qreal m_phi;
};

#endif // GLCAMERASIMULATION_H
