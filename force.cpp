#include "force.h"
#include <QtMath>

Force::Force() :
    QObject(nullptr)
{
    m_pos = m_direction = QVector3D(0,0,0);
    m_momentum = QVector4D(0,0,0,0);
}

Force::~Force()
{
}

Force::Force(const Force& force)
{
    m_pos = force.m_pos;
    m_direction = force.m_direction;
    m_momentum = force.m_momentum;
}

void Force::operator = (const Force& force)
{
    m_pos = force.m_pos;
    m_direction = force.m_direction;
    m_momentum = force.m_momentum;
}

Force Force::operator + (const Force& force)
{
    Force res;
    if(m_pos == force.m_pos) {
        res.setPos(m_pos);
        res.setDirection(m_direction + force.m_direction);
        res.setMomentum(m_momentum);
    } else if(m_direction == force.m_direction) {
        res.setPos((m_pos + force.m_pos) / 2);
        res.setDirection(m_direction + force.m_direction);
        res.setMomentum(m_momentum + force.m_momentum);
    } else {
        /*Force f1, f2, f3;
        f1 = *this;
        f2.setPos(force.m_pos);
        f2.setDirection(m_direction.normalized() * QVector3D::dotProduct(m_direction.normalized(), force.m_direction));
        f2.setMomentum(QVector4D(0,0,0,0));
        f3.setPos(force.m_pos);
        f2.setDirection();*/
    }
    return res;
}

Force Force::operator - (const Force& force)
{
    Force res;
    if(m_pos == force.m_pos) {
        res.setPos(m_pos);
        res.setDirection(m_direction - force.m_direction);
        res.setMomentum(m_momentum);
    } else if(m_direction == force.m_direction) {
        res.setPos((m_pos - force.m_pos) / 2);
        res.setDirection(m_direction - force.m_direction);
        res.setMomentum(m_momentum + force.m_momentum);
    } else {
        /*Force f1, f2, f3;
        f1 = *this;
        f2.setPos(force.m_pos);
        f2.setDirection(m_direction.normalized() * QVector3D::dotProduct(m_direction.normalized(), force.m_direction));
        f2.setMomentum(QVector4D(0,0,0,0));
        f3.setPos(force.m_pos);
        f2.setDirection();*/
    }
    return res;
}

void Force::setPos(QVector3D pos)
{
    m_pos = pos;
}

QVector3D Force::pos()
{
    return m_pos;
}

void Force::setDirection(QVector3D direction)
{
    m_direction = direction;
}

QVector3D Force::direction()
{
    return m_direction;
}

void Force::setMomentum(QVector4D momentum)
{
    m_momentum = momentum;
}

QVector4D Force::momentum()
{
    return m_momentum;
}
