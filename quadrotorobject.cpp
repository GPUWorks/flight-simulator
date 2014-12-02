#include "quadrotorobject.h"
#include <QtMath>
#include "registry.h"

#define UNIT_ANGLE 6

QuadrotorObject::QuadrotorObject()
{
    m_pitch = m_roll = m_yaw = 0.0;
    m_center = QVector3D(0, 5, 12);
    m_powers[LEFT_FRONT] = m_powers[RIGHT_FRONT] = m_powers[LEFT_REAR] = m_powers[RIGHT_REAR] = 2.4525;
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

    m_forces[LEFT_FRONT].setPos(QVector3D(-2,10,12));
    m_forces[LEFT_FRONT].setDirection(m_powers[LEFT_FRONT] * QVector3D(0,0,1));
    m_forces[LEFT_FRONT].setMomentum(QVector4D(0,0,0,0));

    m_forces[RIGHT_FRONT].setPos(QVector3D(2,10,12));
    m_forces[RIGHT_FRONT].setDirection(m_powers[RIGHT_FRONT] * QVector3D(0,0,1));
    m_forces[RIGHT_FRONT].setMomentum(QVector4D(0,0,0,0));

    m_forces[LEFT_REAR].setPos(QVector3D(-2,0,12));
    m_forces[LEFT_REAR].setDirection(m_powers[LEFT_REAR] * QVector3D(0,0,1));
    m_forces[LEFT_REAR].setMomentum(QVector4D(0,0,0,0));

    m_forces[RIGHT_REAR].setPos(QVector3D(2,0,12));
    m_forces[RIGHT_REAR].setDirection(m_powers[RIGHT_REAR] * QVector3D(0,0,1));
    m_forces[RIGHT_REAR].setMomentum(QVector4D(0,0,0,0));

    m_forces[GRAVITY].setPos(m_center);
    m_forces[GRAVITY].setDirection(Registry::qoMass * Registry::pcGravity * QVector3D(0,0,-1));
    m_forces[GRAVITY].setMomentum(QVector4D(0,0,0,0));
}

void QuadrotorObject::render(QMatrix4x4 MVP, QVector3D eyePos)
{
    Q_UNUSED(eyePos)

    m_prog.bind();

    m_buffer.bind();
    m_buffer.allocate(m_data.data(), m_data.size() * sizeof(GLfloat));
    m_prog.enableAttributeArray("vertex");
    m_prog.setAttributeBuffer("vertex", GL_FLOAT, 0, 3);
    m_buffer.release();

    m_prog.setUniformValue("MVP", MVP * ROT);

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

qreal QuadrotorObject::yaw()
{
    const float* ROTmat = ROT.data();
    return atan(ROTmat[4] / ROTmat[0]);
}

void QuadrotorObject::changeYaw(char op)
{
    qreal angle = ( op == '+' ? UNIT_ANGLE : -UNIT_ANGLE );
    ROT.translate(m_center);
    ROT.rotate(angle, 0, 0, 1);
    ROT.translate(-m_center);
    m_yaw -= angle;
    if(m_yaw <= -180)
        m_yaw += 360;
    else if(m_yaw >= 180)
        m_yaw -= 360;
}

qreal QuadrotorObject::pitch()
{
    const float* ROTmat = ROT.data();
    return atan( ROTmat[8] / sqrt( pow(ROTmat[9], 2) + pow(ROTmat[10], 2) ) );
}

void QuadrotorObject::changePitch(char op)
{
    qreal angle = ( op == '+' ? UNIT_ANGLE : -UNIT_ANGLE );
    ROT.translate(m_center);
    ROT.rotate(angle, 1, 0, 0);
    ROT.translate(-m_center);
    m_pitch -= angle;
    if(m_pitch <= -180)
        m_pitch += 360;
    else if(m_pitch >= 180)
        m_pitch -= 360;
}

qreal QuadrotorObject::roll()
{
    const float* ROTmat = ROT.data();
    return atan( ROTmat[9] / ROTmat[10] );
}

void QuadrotorObject::changeRoll(char op)
{
    qreal angle = ( op == '+' ? UNIT_ANGLE : -UNIT_ANGLE );
    ROT.translate(m_center);
    ROT.rotate(angle, 0, 1, 0);
    ROT.translate(-m_center);
    m_roll -= angle;
    if(m_roll <= -180)
        m_roll += 360;
    else if(m_roll >= 180)
        m_roll -= 360;
}

void QuadrotorObject::setPos(QVector3D pos)
{
    m_center = pos;
}

QVector3D QuadrotorObject::pos()
{
    return m_center;
}
