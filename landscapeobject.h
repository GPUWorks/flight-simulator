#ifndef LANDSCAPEOBJECT_H
#define LANDSCAPEOBJECT_H

#include <QGLShaderProgram>
#include <QGLFunctions>
#include <QGLBuffer>
#include <QVector3D>
#include "globject.h"

class LandscapeObject : public GLObject
{
public:
    LandscapeObject();

private:
    QGLShaderProgram m_prog;

    QVector<GLfloat> m_data;
    QGLBuffer m_buffer;
};

#endif // LANDSCAPEOBJECT_H
