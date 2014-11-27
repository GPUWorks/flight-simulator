#ifndef QUADROTOROBJECT_H
#define QUADROTOROBJECT_H

#include <QGLShaderProgram>
#include <QGLFunctions>
#include <QGLBuffer>
#include <QVector3D>
#include "globject.h"

class QuadrotorObject : public GLObject, protected QGLFunctions
{
public:
    QuadrotorObject();
    ~QuadrotorObject();

    virtual void init();
    virtual void render(QMatrix4x4 projection, QVector3D eyePos);

    void setYaw(qreal yaw);
    qreal yaw();

    void setPitch(qreal pitch);
    qreal pitch();

    void setRoll(qreal roll);
    qreal roll();

    void setPos(QVector3D pos);
    QVector3D pos();

private:
    void loadShaders();
    void terrainGen();

private:
    QGLShaderProgram m_prog;

    QVector<GLfloat> m_data;
    QGLBuffer m_buffer;

private:
    qreal m_pitch;
    qreal m_roll;
    qreal m_yaw;
    QVector3D m_center;
};

#endif // QUADROTOROBJECT_H
