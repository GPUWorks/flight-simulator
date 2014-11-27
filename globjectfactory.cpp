#include "globjectfactory.h"

#include "landscapefactory.h"
#include "quadrotorfactory.h"

GLObjectFactory::GLObjectFactory()
{
}

GLObjectFactory::~GLObjectFactory()
{
}

QSharedPointer<GLObjectFactory> GLObjectFactory::createFactory(Type object)
{
    if(object == LANDSCAPE) {
        return QSharedPointer<GLObjectFactory>(new LandscapeFactory);
    } else if(object == QUADROTOR) {
        return QSharedPointer<GLObjectFactory>(new QuadrotorFactory);
    } else {
        throw std::runtime_error("Unknown type of an object");
    }
}

GLObject* GLObjectFactory::createObject()
{
    throw std::logic_error("Method with no definition");
}
