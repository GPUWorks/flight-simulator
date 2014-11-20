#ifndef GLCAMERA_H
#define GLCAMERA_H

#include <QVector3D>
#include <QMatrix4x4>
#include <QObject>
#include <stdexcept>

class GLCamera : public QObject
{
    Q_OBJECT
public:
    explicit GLCamera(): QObject(nullptr){}

    virtual QMatrix4x4 getProjectionMatrix() {
        throw std::logic_error("Method with no definition");
    }

    virtual void setYaw(qreal yaw) {
        m_yaw = yaw;
    }

    virtual qreal yaw() {
        return m_yaw;
    }

    virtual void setPitch(qreal pitch) {
        m_pitch = pitch;
    }

    virtual qreal pitch() {
        return m_pitch;
    }

    virtual void addCameraPos(QVector3D arg) {
        m_cameraPos += arg;
    }

    virtual void subCameraPos(QVector3D arg) {
        m_cameraPos -= arg;
    }

    virtual void resize(int width, int height) {
        m_width = width;
        m_height = height;
    }

protected:
    qreal m_yaw;
    qreal m_pitch;
    QVector3D m_cameraPos;

    int m_width;
    int m_height;
};

#endif // GLCAMERA_H
