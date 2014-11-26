#ifndef LANDSCAPEOBJECT_H
#define LANDSCAPEOBJECT_H

#include <QGLShaderProgram>
#include <QGLFunctions>
#include <QGLBuffer>
#include <QVector3D>
#include "globject.h"

class LandscapeObject : public GLObject, protected QGLFunctions
{
public:
    LandscapeObject();
    ~LandscapeObject();

    virtual void init();

    virtual void render(QMatrix4x4 projection, QVector3D eyePos);

private:
    void loadShaders();
    void terrainGen();

private:
    QGLShaderProgram m_prog;

    QVector<GLfloat> m_data;
    QGLBuffer m_buffer;
};

#endif // LANDSCAPEOBJECT_H
