#include "glcamera.h"

GLCamera::GLCamera(QObject* parent): QObject(parent)
{
}

GLCamera::~GLCamera()
{
}

QMatrix4x4 GLCamera::getProjectionMatrix() {
    throw std::logic_error("Method with no definition");
}

void GLCamera::setViewAngle(qreal viewAngle)
{
    m_viewAngle = viewAngle;
}

void GLCamera::setMinDist(qreal minDist)
{
    m_minDist = minDist;
}

void GLCamera::setMaxDist(qreal maxDist)
{
    m_maxDist = maxDist;
}

QVector3D GLCamera::pos()
{
    return m_cameraPos;
}

void GLCamera::setYaw(qreal yaw) {
    m_yaw = yaw;
}

qreal GLCamera::yaw() {
    return m_yaw;
}

void GLCamera::setPitch(qreal pitch) {
    m_pitch = pitch;
}

qreal GLCamera::pitch() {
    return m_pitch;
}

void GLCamera::addCameraPos(QVector3D arg) {
    m_cameraPos += arg;
}

void GLCamera::subCameraPos(QVector3D arg) {
    m_cameraPos -= arg;
}

void GLCamera::setCameraPos(QVector3D arg)
{
    m_cameraPos = arg;
}

void GLCamera::resize(int width, int height) {
    m_width = width;
    m_height = height;
}
