#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

/*
 * Main controller is the controller which distributes the work
 * between several threads. It's also the last frontier where
 * exceptions can be handled.
 */

#include <QObject>
#include <QThread>
#include "controlwindow.h"
#include "globject.h"
#include "physicscontroller.h"
#include "renderingcontroller.h"
#include "camglwidget.h"
#include <QMutex>

class MainController : public QObject
{
    Q_OBJECT
    friend class RenderingController;
    friend class PhysicsController;
public:
    explicit MainController(QObject* parent = nullptr);
    ~MainController();
    void start(); // starting the simulation program

private:
    void initialization(); // initialization of all objects

signals:
    // signal that the simulation has been crashed...
    void crashed(); // ...and needs to be restarted

public slots:
    void startSimulation();
    void simulationFinished();
    void restartApp(); // reallocate all memory and restart all systems

private: // general members
    ControlWindow* m_controlWindow;
    CamGLWidget* m_simulationWindow;
    QList< QSharedPointer<GLObject> > m_objects;
    QMutex m_objectsMutex;

private: // physics engine
    PhysicsController* m_physController;
    QThread* m_physicsThread;

private: // 3D engine
    RenderingController* m_renderController;
};

#endif // MAINCONTROLLER_H
