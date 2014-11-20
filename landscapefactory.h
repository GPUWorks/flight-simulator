#ifndef LANDSCAPEFACTORY_H
#define LANDSCAPEFACTORY_H

#include "globjectfactory.h"
#include "globject.h"

class LandscapeFactory : public GLObjectFactory
{
public:
    LandscapeFactory();
    ~LandscapeFactory();

    virtual GLObject* createObject();
};

#endif // LANDSCAPEFACTORY_H
