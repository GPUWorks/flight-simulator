#include "landscapefactory.h"
#include "landscapeobject.h"

LandscapeFactory::LandscapeFactory()
{
}

LandscapeFactory::~LandscapeFactory()
{
}

GLObject* LandscapeFactory::createObject()
{
    return new LandscapeObject;
}
