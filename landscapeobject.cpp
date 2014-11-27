#include "landscapeobject.h"

LandscapeObject::LandscapeObject()
{
}

LandscapeObject::~LandscapeObject()
{
}

void LandscapeObject::init()
{
    this->initializeGLFunctions();
    terrainGen();
    loadShaders();

    m_prog.bind();
    m_buffer.create();
    m_buffer.setUsagePattern(QGLBuffer::StaticDraw);
    m_prog.release();
}

void LandscapeObject::render(QMatrix4x4 projection, QVector3D eyePos)
{
    Q_UNUSED(eyePos)

    m_prog.bind();

    m_buffer.bind();
    m_buffer.allocate(m_data.data(), m_data.size() * sizeof(GLfloat));
    m_prog.enableAttributeArray("vertex");
    m_prog.setAttributeBuffer("vertex", GL_FLOAT, 0, 3);
    m_buffer.release();

    m_prog.setUniformValue("MVP", projection);

    glDrawArrays(GL_TRIANGLES, 0, m_data.size());

    m_prog.release();
}

void LandscapeObject::loadShaders()
{
    m_prog.addShaderFromSourceFile(QGLShader::Vertex, ":/shaders/landscape.vert.glsl");
    m_prog.addShaderFromSourceFile(QGLShader::Fragment, ":/shaders/landscape.frag.glsl");
    m_prog.link();
}

void LandscapeObject::terrainGen()
{
    m_data.push_back(-100);m_data.push_back(-100);m_data.push_back(0);
    m_data.push_back(-100);m_data.push_back(+100);m_data.push_back(0);
    m_data.push_back(+100);m_data.push_back(-100);m_data.push_back(0);

    m_data.push_back(+100);m_data.push_back(-100);m_data.push_back(0);
    m_data.push_back(-100);m_data.push_back(+100);m_data.push_back(0);
    m_data.push_back(+100);m_data.push_back(+100);m_data.push_back(0);
}
