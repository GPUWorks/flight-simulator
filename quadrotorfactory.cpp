#include "quadrotorfactory.h"
#include "quadrotorobject.h"

QuadrotorFactory::QuadrotorFactory()
{
}

QuadrotorFactory::~QuadrotorFactory()
{
}

GLObject* QuadrotorFactory::createObject()
{
    return new QuadrotorObject;
}
