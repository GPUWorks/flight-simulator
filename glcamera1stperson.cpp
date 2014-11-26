#include "glcamera1stperson.h"
#include <QtMath>

GLCamera1stPerson::GLCamera1stPerson()
{
    m_roll = m_yaw = m_pitch = 0.0;
}

void GLCamera1stPerson::setRoll(qreal roll)
{
    m_roll = roll;
}

qreal GLCamera1stPerson::roll()
{
    return m_roll;
}

QMatrix4x4 GLCamera1stPerson::getProjectionMatrix()
{
    QMatrix4x4 mat;
    mat.perspective(m_viewAngle,
                    this->m_width / this->m_height,
                    m_minDist, m_maxDist);

    QVector3D eyeDirection = QVector3D(qSin(m_yaw) * qCos(m_pitch),
                                       qCos(m_yaw) * qCos(m_pitch),
                                       qSin(m_pitch));
    eyeDirection.normalize();
    mat.lookAt(m_cameraPos,
               m_cameraPos + eyeDirection,
               QVector3D(0,0,1));

    return mat;
}
