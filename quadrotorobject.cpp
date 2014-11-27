#include "quadrotorobject.h"
#include <QtMath>

QuadrotorObject::QuadrotorObject()
{
    m_pitch = m_roll = m_yaw = 0.0;
    m_center = QVector3D(0, 5, 12);
}

QuadrotorObject::~QuadrotorObject()
{
}

void QuadrotorObject::init()
{
    this->initializeGLFunctions();
    terrainGen();
    loadShaders();

    m_prog.bind();
    m_buffer.create();
    m_buffer.setUsagePattern(QGLBuffer::StaticDraw);
    m_prog.release();
}

void QuadrotorObject::render(QMatrix4x4 projection, QVector3D eyePos)
{
    Q_UNUSED(eyePos)

    m_prog.bind();

    m_buffer.bind();
    m_buffer.allocate(m_data.data(), m_data.size() * sizeof(GLfloat));
    m_prog.enableAttributeArray("vertex");
    m_prog.setAttributeBuffer("vertex", GL_FLOAT, 0, 3);
    m_buffer.release();

    QMatrix4x4 MVP = projection;
    MVP.translate(m_center);
    MVP.rotate(QQuaternion(qCos(m_pitch / 2), qSin(m_pitch / 2) * QVector3D(1,0,0)));
    MVP.rotate(QQuaternion(qCos(m_roll  / 2), qSin(m_roll  / 2) * QVector3D(0,1,0)));
    MVP.rotate(QQuaternion(qCos(m_yaw   / 2), qSin(m_yaw   / 2) * QVector3D(0,0,1)));
    MVP.translate(-m_center);

    m_prog.setUniformValue("MVP", MVP);

    glDrawArrays(GL_TRIANGLES, 0, m_data.size());

    m_prog.release();
}

void QuadrotorObject::loadShaders()
{
    m_prog.addShaderFromSourceFile(QGLShader::Vertex, ":/shaders/quadrotor.vert.glsl");
    m_prog.addShaderFromSourceFile(QGLShader::Fragment, ":/shaders/quadrotor.frag.glsl");
    m_prog.link();
}

void QuadrotorObject::terrainGen()
{
    m_data.push_back(+2);m_data.push_back(0);m_data.push_back(10);
    m_data.push_back(-2);m_data.push_back(0);m_data.push_back(10);
    m_data.push_back(-2);m_data.push_back(0);m_data.push_back(14);
    m_data.push_back(-2);m_data.push_back(0);m_data.push_back(14);
    m_data.push_back(+2);m_data.push_back(0);m_data.push_back(14);
    m_data.push_back(+2);m_data.push_back(0);m_data.push_back(10);

    m_data.push_back(+2);m_data.push_back(10);m_data.push_back(10);
    m_data.push_back(-2);m_data.push_back(10);m_data.push_back(10);
    m_data.push_back(-2);m_data.push_back(10);m_data.push_back(14);
    m_data.push_back(-2);m_data.push_back(10);m_data.push_back(14);
    m_data.push_back(+2);m_data.push_back(10);m_data.push_back(14);
    m_data.push_back(+2);m_data.push_back(10);m_data.push_back(10);

    m_data.push_back(+2);m_data.push_back(0);m_data.push_back(10);
    m_data.push_back(+2);m_data.push_back(10);m_data.push_back(10);
    m_data.push_back(-2);m_data.push_back(10);m_data.push_back(10);
    m_data.push_back(-2);m_data.push_back(10);m_data.push_back(10);
    m_data.push_back(-2);m_data.push_back(0);m_data.push_back(10);
    m_data.push_back(+2);m_data.push_back(0);m_data.push_back(10);

    m_data.push_back(+2);m_data.push_back(0);m_data.push_back(14);
    m_data.push_back(+2);m_data.push_back(10);m_data.push_back(14);
    m_data.push_back(-2);m_data.push_back(10);m_data.push_back(14);
    m_data.push_back(-2);m_data.push_back(10);m_data.push_back(14);
    m_data.push_back(-2);m_data.push_back(0);m_data.push_back(14);
    m_data.push_back(+2);m_data.push_back(0);m_data.push_back(14);

    m_data.push_back(+2);m_data.push_back(0);m_data.push_back(10);
    m_data.push_back(+2);m_data.push_back(10);m_data.push_back(10);
    m_data.push_back(+2);m_data.push_back(10);m_data.push_back(14);
    m_data.push_back(+2);m_data.push_back(10);m_data.push_back(14);
    m_data.push_back(+2);m_data.push_back(0);m_data.push_back(14);
    m_data.push_back(+2);m_data.push_back(0);m_data.push_back(10);

    m_data.push_back(-2);m_data.push_back(0);m_data.push_back(10);
    m_data.push_back(-2);m_data.push_back(10);m_data.push_back(10);
    m_data.push_back(-2);m_data.push_back(10);m_data.push_back(14);
    m_data.push_back(-2);m_data.push_back(10);m_data.push_back(14);
    m_data.push_back(-2);m_data.push_back(0);m_data.push_back(14);
    m_data.push_back(-2);m_data.push_back(0);m_data.push_back(10);
}

void QuadrotorObject::setYaw(qreal yaw)
{
    if(yaw >= 2 * M_PI)
        yaw -= (2 * M_PI);
    else if(yaw <= -2 * M_PI)
        yaw += (2 * M_PI);
    m_yaw = yaw;
}

qreal QuadrotorObject::yaw()
{
    return m_yaw;
}

void QuadrotorObject::setPitch(qreal pitch)
{
    if(pitch >= 2 * M_PI)
        pitch -= (2 * M_PI);
    else if(pitch <= -2 * M_PI)
        pitch += (2 * M_PI);
    m_pitch = pitch;
}

qreal QuadrotorObject::pitch()
{
    return m_pitch;
}

void QuadrotorObject::setRoll(qreal roll)
{
    if(roll >= 2 * M_PI)
        roll -= (2 * M_PI);
    else if(roll <= -2 * M_PI)
        roll += (2 * M_PI);
    m_roll = roll;
}

qreal QuadrotorObject::roll()
{
    return m_roll;
}

void QuadrotorObject::setPos(QVector3D pos)
{
    m_center = pos;
}

QVector3D QuadrotorObject::pos()
{
    return m_center;
}
