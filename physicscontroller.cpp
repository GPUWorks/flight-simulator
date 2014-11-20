#include "physicscontroller.h"
#include "maincontroller.h"
#include "registry.h"
#include "ui_controlwindow.h"
#include <QMetaType>

PhysicsController::PhysicsController(QObject* mainController) :
    QObject(nullptr),
    m_mainController(mainController),
    m_physicsTimer(new QTimer(this))
{
    MainController* controller = dynamic_cast<MainController*>(m_mainController);
    m_objects = &(controller->m_objects);
    m_objectsMutex = &(controller->m_objectsMutex);
    connect(m_physicsTimer.data(), SIGNAL(timeout()), this, SLOT(updatePhysicalProperties()));
    m_time = 0.0;
}

void PhysicsController::start()
{
    qDebug("start physics controller");
    m_physicsTimer->start(SEC / Registry::FPSphys);
}

void PhysicsController::updatePhysicalProperties()
{
    qDebug("physics update");
    m_time += (m_physicsTimer.data()->interval() / 1000.0);
}
