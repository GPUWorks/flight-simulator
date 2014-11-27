#ifndef QUADROTORFACTORY_H
#define QUADROTORFACTORY_H

#include "globjectfactory.h"

class QuadrotorFactory : public GLObjectFactory
{
public:
    QuadrotorFactory();
    ~QuadrotorFactory();

    virtual GLObject* createObject();
};

#endif // QUADROTORFACTORY_H
