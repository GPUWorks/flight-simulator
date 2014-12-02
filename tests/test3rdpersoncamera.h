#ifndef TEST3RDPERSONCAMERA_H
#define TEST3RDPERSONCAMERA_H

#include <QObject>

#include <QString>
#include <QtTest>
#include <QObject>
#include <QVector3D>
#include "../glcamera3rdperson.h"

struct Cmd {
    enum Type { R = 0, THETA = 1, PHI = 2 };
    Type type;
    qreal delta;

    Cmd(): delta(0){}
    Cmd(Type t, qreal d):
        type(t), delta(d){}
};

Q_DECLARE_METATYPE(Cmd)

class Test3rdPersonCamera : public QObject
{
    Q_OBJECT

public:
    Test3rdPersonCamera();

private:
    qreal exec1Cmd(Cmd cmd);
    qreal exec2Cmd(Cmd cmd);

    qreal execCmd(Cmd cmd, GLCamera3rdPerson& cam);

private Q_SLOTS:
    void testCase();
    void testCase_data();

private:
    GLCamera3rdPerson m_camera;
};

#endif // TEST3RDPERSONCAMERA_H
