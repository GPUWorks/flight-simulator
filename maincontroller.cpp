#include "maincontroller.h"

MainController::MainController(QObject* parent) :
    QObject(parent),
    m_controlWindow(new ControlWindow(this)),
    m_simulationWindow(new CamGLWidget)
{
    connect(m_controlWindow,    SIGNAL(closed()), m_simulationWindow, SLOT(deleteLater()));
    connect(m_simulationWindow, SIGNAL(closed()), this, SLOT(simulationFinished()));

    connect(this, SIGNAL(crashed()), this, SLOT(restartApp()));
}

MainController::~MainController()
{
    qDebug("MainController Destructor");
}

void MainController::start()
{
    initialization();

    m_controlWindow->show();
}

void MainController::restartApp()
{
    /*
     * TODO: full restart of the application:
     *  - reallocate memory (call `initialization`)
     *  - restart all windows, threads, systems (call `start`)
     */
}

#include "landscapeobject.h"

void MainController::initialization()
{
    // TODO: initialize objects
    /*m_objects.push_back( QSharedPointer<GLObject>(new LandscapeObject) );
    m_objects.push_back( QSharedPointer<GLObject>(new LandscapeObject) );
    m_objects.push_back( QSharedPointer<GLObject>(new LandscapeObject) );

    qDebug() << "m_objects:" << m_objects.size();
    qDebug() << &m_objects.first();*/
}

void MainController::startSimulation()
{
    qDebug("startSimulation");

    // Creating new thread and physics controller.
    // Connecting physics controller to new thread.
    m_physicsThread = new QThread;
    m_physController = new PhysicsController(this);
    m_physController->moveToThread(m_physicsThread);

    // Creating rendering controller.
    m_renderController = new RenderingController(this);

    // Opening simulation window.
    m_simulationWindow->resize(800, 600);
    m_simulationWindow->show();

    // Set up connections
    connect(m_physicsThread,    SIGNAL(started()),  m_physController,   SLOT(start()));

    connect(m_physController,   SIGNAL(finished()), m_physicsThread,    SLOT(quit())); ///////////////////
    connect(m_physController,   SIGNAL(finished()), m_physController,   SLOT(deleteLater()));           // m_physController
    connect(m_physController,   SIGNAL(finished()), m_physicsThread,    SLOT(deleteLater()));           // signal `finished`
    connect(m_physController,   SIGNAL(finished()), m_renderController, SLOT(deleteLater()));           //
    connect(m_physController,   SIGNAL(finished()), this,               SLOT(simulationFinished())); /////
    connect(m_renderController, SIGNAL(finished()), m_physicsThread,    SLOT(quit())); ///////////////////
    connect(m_renderController, SIGNAL(finished()), m_physController,   SLOT(deleteLater()));           // m_renderController
    connect(m_renderController, SIGNAL(finished()), m_physicsThread,    SLOT(deleteLater()));           // signal `finished`
    connect(m_renderController, SIGNAL(finished()), m_renderController, SLOT(deleteLater()));           //
    connect(m_renderController, SIGNAL(finished()), this,               SLOT(simulationFinished())); /////
    connect(m_physController,   SIGNAL(crashed()),  m_physicsThread,    SLOT(quit())); ///////////////////
    connect(m_physController,   SIGNAL(crashed()),  m_physController,   SLOT(deleteLater()));           // m_physController
    connect(m_physController,   SIGNAL(crashed()),  m_physicsThread,    SLOT(deleteLater()));           // signal `crashed`
    connect(m_physController,   SIGNAL(crashed()),  m_renderController, SLOT(deleteLater()));           //
    connect(m_physController,   SIGNAL(crashed()),  this,               SIGNAL(crashed())); //////////////
    connect(m_renderController, SIGNAL(crashed()),  m_physicsThread,    SLOT(quit())); ///////////////////
    connect(m_renderController, SIGNAL(crashed()),  m_physController,   SLOT(deleteLater()));           // m_renderController
    connect(m_renderController, SIGNAL(crashed()),  m_physicsThread,    SLOT(deleteLater()));           // signal `crashed`
    connect(m_renderController, SIGNAL(crashed()),  m_renderController, SLOT(deleteLater()));           //
    connect(m_renderController, SIGNAL(crashed()),  this,               SIGNAL(crashed())); //////////////
    connect(m_simulationWindow, SIGNAL(closed()),   m_physicsThread,    SLOT(quit())); ///////////////////
    connect(m_simulationWindow, SIGNAL(closed()),   m_physController,   SLOT(deleteLater()));           // m_simulationWindow
    connect(m_simulationWindow, SIGNAL(closed()),   m_physicsThread,    SLOT(deleteLater()));           // signal `closed`
    connect(m_simulationWindow, SIGNAL(closed()),   m_renderController, SLOT(deleteLater()));           //
    connect(m_simulationWindow, SIGNAL(closed()),   this,               SLOT(simulationFinished())); /////

    connect(this,               SIGNAL(crashed()),  m_simulationWindow, SLOT(deleteLater()));
    connect(this,               SIGNAL(crashed()),  m_controlWindow,    SLOT(deleteLater()));

    m_physicsThread->start(); // start physics engine in separate thread
    m_renderController->start(); // start rendering engine
}

void MainController::simulationFinished()
{
    qDebug("simulationFinished");
}
