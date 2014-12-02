#include "glcamera3rdperson.h"
#include <QtMath>

GLCamera3rdPerson::GLCamera3rdPerson()
{
    m_yaw = m_pitch = 0.0;
    m_R = 20;
    m_theta = M_PI / 6;
    m_phi = M_PI / 6;
}

QMatrix4x4 GLCamera3rdPerson::getProjectionMatrix()
{
    QMatrix4x4 mat;
    mat.perspective(m_viewAngle,
                    this->m_width / this->m_height,
                    m_minDist, m_maxDist);

    QVector3D pos(
        m_R * qSin(m_theta) * qCos(m_phi),
        m_R * qSin(m_theta) * qSin(m_phi),
        m_R * qCos(m_theta)
    );

    mat.lookAt(m_center + pos,
               m_center,
               QVector3D(0,0,1));

    return mat;
}

void GLCamera3rdPerson::setCenter(QVector3D center)
{
    m_center = center;
}

void GLCamera3rdPerson::addR(qreal delta)
{
    m_R += delta;
}

void GLCamera3rdPerson::addTheta(qreal delta)
{
    m_theta += delta;
    if(m_theta >= 360)
        m_theta -= 360;
    else if(m_theta <= -360)
        m_theta += 360;
    if(m_R * qCos(m_theta) + m_center.z() < 0.5)
        m_theta -= delta;
}

void GLCamera3rdPerson::addPhi(qreal delta)
{
    m_phi += delta;
    if(m_phi >= 360)
        m_phi -= 360;
    else if(m_phi <= -360)
        m_phi += 360;
}
