#ifndef GLOBJECT_H
#define GLOBJECT_H

#include <QObject>
#include <stdexcept>
#include <QMatrix4x4>

class GLObject : public QObject
{
    Q_OBJECT
public:
    GLObject(){}
    ~GLObject(){}

    virtual void init() {
        throw std::logic_error("Method with no definition");
    }
    virtual void render(QMatrix4x4 projection) {
        Q_UNUSED(projection)
        throw std::logic_error("Method with no definition");
    }
};

#endif // GLOBJECT_H
