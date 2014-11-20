#include "glcamerasimulation.h"
#include <cmath>

using std::sin;
using std::cos;

GLCameraSimulation::GLCameraSimulation()
{
}

QMatrix4x4 GLCameraSimulation::getProjectionMatrix()
{
    QMatrix4x4 mat;
    mat.perspective(m_viewAngle,
                    this->m_width / this->m_height,
                    m_minDist, m_maxDist);

    QVector3D eyeDirection = QVector3D(sin(m_yaw) * cos(m_pitch),
                                       cos(m_yaw) * cos(m_pitch),
                                       sin(m_pitch));
    eyeDirection.normalize();
    mat.lookAt(m_cameraPos,
               m_cameraPos + eyeDirection,
               QVector3D(0,0,1));

    return mat;
}
