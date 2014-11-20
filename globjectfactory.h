#ifndef GLOBJECTFACTORY_H
#define GLOBJECTFACTORY_H

#include <QObject>
#include <QSharedPointer>
#include "globject.h"

class GLObjectFactory
{
public:
    enum Type { LANDSCAPE };
public:
    GLObjectFactory();
    virtual ~GLObjectFactory();

    static QSharedPointer<GLObjectFactory> createFactory(Type object);
    virtual GLObject* createObject();
};

#endif // GLOBJECTFACTORY_H
