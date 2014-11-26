#ifndef GLOBJECT_H
#define GLOBJECT_H

#include <QObject>
#include <stdexcept>
#include <QMatrix4x4>
#include "gllight.h"

class GLObject : public QObject
{
    Q_OBJECT
public:
    GLObject(QObject* parent = nullptr) : QObject(parent){}
    virtual ~GLObject(){}

    virtual void init() {
        throw std::logic_error("Method with no definition");
    }

    virtual void render(QMatrix4x4 projection, QVector3D eyePos) {
        Q_UNUSED(projection)
        Q_UNUSED(eyePos)
        throw std::logic_error("Method with no definition");
    }

    void setLight(GLLight* light) {
        m_light = light;
    }

protected:
    GLLight* m_light;
};

#endif // GLOBJECT_H
