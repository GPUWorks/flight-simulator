#include "maincontroller.h"
#include "globjectfactory.h"
#include "globject.h"
#include "ui_controlwindow.h"

MainController::MainController(QObject* parent) :
    QObject(parent),
    m_controlWindow(new ControlWindow(this)),
    m_simulationWindow(nullptr)
{
}

MainController::~MainController()
{
    qDebug("MainController Destructor");
}

void MainController::start()
{
    initialization();

    m_simulationWindow = new CamGLWidget(this);
    connect(m_controlWindow,    SIGNAL(closed()), m_simulationWindow, SLOT(deleteLater()));
    connect(m_simulationWindow, SIGNAL(closed()), this,               SLOT(simulationFinished()));

    connect(this, SIGNAL(crashed()), this, SLOT(restartApp()));

    connect(m_controlWindow->ui->tpvButton, SIGNAL(clicked()), m_simulationWindow, SLOT(setCamera3rdPerson()));
    connect(m_controlWindow->ui->fpvButton, SIGNAL(clicked()), m_simulationWindow, SLOT(setCamera1stPerson()));

    m_controlWindow->setFixedSize(775,545);
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
    QSharedPointer<GLObjectFactory> landscapeFactory = GLObjectFactory::createFactory( GLObjectFactory::LANDSCAPE );
    m_objects.push_back( QSharedPointer<GLObject>(landscapeFactory->createObject()) );
}

void MainController::startSimulation()
{
    qDebug("startSimulation");

    // Creating new thread and physics controller.
    // Connecting physics controller to new thread.
    m_physicsThread = new QThread;
    m_physController = new PhysicsController(this);
    m_physController->moveToThread(m_physicsThread);


    // Set up connections
    connect(m_physicsThread,    SIGNAL(started()),  m_physController,   SLOT(start()));

    connect(m_physController,   SIGNAL(finished()), m_physicsThread,    SLOT(quit())); ///////////////////
    connect(m_physController,   SIGNAL(finished()), m_physController,   SLOT(deleteLater()));           // m_physController
    connect(m_physController,   SIGNAL(finished()), m_physicsThread,    SLOT(deleteLater()));           // signal `finished`
    connect(m_physController,   SIGNAL(finished()), this,               SLOT(simulationFinished())); /////
    connect(m_physController,   SIGNAL(crashed()),  m_physicsThread,    SLOT(quit())); ///////////////////
    connect(m_physController,   SIGNAL(crashed()),  m_physController,   SLOT(deleteLater()));           // m_physController
    connect(m_physController,   SIGNAL(crashed()),  m_physicsThread,    SLOT(deleteLater()));           // signal `crashed`
    connect(m_physController,   SIGNAL(crashed()),  this,               SIGNAL(crashed())); //////////////
    connect(m_simulationWindow, SIGNAL(closed()),   m_physicsThread,    SLOT(quit())); ///////////////////
    connect(m_simulationWindow, SIGNAL(closed()),   m_physController,   SLOT(deleteLater()));           // m_simulationWindow
    connect(m_simulationWindow, SIGNAL(closed()),   m_physicsThread,    SLOT(deleteLater()));           // signal `closed`
    connect(m_simulationWindow, SIGNAL(closed()),   this,               SLOT(simulationFinished())); /////

    connect(this,               SIGNAL(crashed()),  m_simulationWindow, SLOT(deleteLater()));
    connect(this,               SIGNAL(crashed()),  m_controlWindow,    SLOT(deleteLater()));

    // Opening simulation window.
    m_simulationWindow->resize(800, 600);
    m_simulationWindow->show();

    //m_physicsThread->start(); // start physics engine in separate thread
    m_simulationWindow->start();
}

void MainController::simulationFinished()
{
    qDebug("simulationFinished");
}
