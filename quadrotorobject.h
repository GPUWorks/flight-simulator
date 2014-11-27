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

    qreal yaw();
    void changeYaw(char op);

    qreal pitch();
    void changePitch(char op);

    qreal roll();
    void changeRoll(char op);

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
    QMatrix4x4 ROT;
};

#endif // QUADROTOROBJECT_H
