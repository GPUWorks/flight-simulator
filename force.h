#ifndef FORCE_H
#define FORCE_H

#include <QObject>
#include <QVector3D>
#include <QVector4D>

class Force : public QObject
{
    Q_OBJECT
public:
    explicit Force();
    ~Force();
    Force(const Force& force);
    void operator = (const Force& force);
    Force operator + (const Force& force);
    Force operator - (const Force& force);

    void setPos(QVector3D pos);
    QVector3D pos();

    void setDirection(QVector3D direction);
    QVector3D direction();

    void setMomentum(QVector4D momentum);
    QVector4D momentum();

private:
    QVector3D m_pos;
    QVector3D m_direction;
    QVector4D m_momentum;
};

#endif // FORCE_H
