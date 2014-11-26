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
    explicit GLCamera(QObject* parent = nullptr);
    virtual ~GLCamera();

    virtual QMatrix4x4 getProjectionMatrix();

    void setViewAngle(qreal viewAngle);
    void setMinDist(qreal minDist);
    void setMaxDist(qreal maxDist);

    QVector3D pos();

    virtual void setYaw(qreal yaw);
    virtual qreal yaw();

    virtual void setPitch(qreal pitch);
    virtual qreal pitch();

    virtual void addCameraPos(QVector3D arg);
    virtual void subCameraPos(QVector3D arg);
    void setCameraPos(QVector3D arg);

    virtual void resize(int width, int height);

protected:
    qreal m_yaw;
    qreal m_pitch;
    QVector3D m_cameraPos;

    int m_width;
    int m_height;

    qreal m_viewAngle;
    qreal m_minDist;
    qreal m_maxDist;
};

#endif // GLCAMERA_H
