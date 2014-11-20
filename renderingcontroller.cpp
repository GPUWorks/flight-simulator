#include "renderingcontroller.h"
#include "maincontroller.h"
#include "registry.h"
#include "ui_controlwindow.h"

RenderingController::RenderingController(QObject* mainController) :
    QObject(nullptr),
    m_mainController(mainController),
    m_renderingTimer(new QTimer(this))
{
    MainController* controller = dynamic_cast<MainController*>(m_mainController);
    m_objects = &(controller->m_objects);
    m_objectsMutex = &(controller->m_objectsMutex);
    connect(m_renderingTimer.data(), SIGNAL(timeout()), this, SLOT(render()));
    m_simulationWindow = controller->m_simulationWindow;
    m_controlWindow = controller->m_controlWindow->ui->CameraGLWidget;

    /*
     * Allow events in simulation window:
     *  - mousePressEvent
     *  - mouseMoveEvent
     *  - keyPressEvent
     */
    m_simulationWindow->setEvents(true);

    /*
     * Connect events from different windows in order they work together.
     */
    connect(m_simulationWindow, SIGNAL(keyPress(QKeyEvent*)),     m_controlWindow, SLOT(keyPressSlot(QKeyEvent*)));
    connect(m_simulationWindow, SIGNAL(mouseMove(QMouseEvent*)),  m_controlWindow, SLOT(mouseMoveSlot(QMouseEvent*)));
    connect(m_simulationWindow, SIGNAL(mousePress(QMouseEvent*)), m_controlWindow, SLOT(mousePressSlot(QMouseEvent*)));

    connect(m_controlWindow, SIGNAL(keyPress(QKeyEvent*)),     m_simulationWindow, SLOT(keyPressSlot(QKeyEvent*)));
    connect(m_controlWindow, SIGNAL(mouseMove(QMouseEvent*)),  m_simulationWindow, SLOT(mouseMoveSlot(QMouseEvent*)));
    connect(m_controlWindow, SIGNAL(mousePress(QMouseEvent*)), m_simulationWindow, SLOT(mousePressSlot(QMouseEvent*)));
}

void RenderingController::start()
{
    qDebug("start rendering controller");
    m_renderingTimer->start(SEC / Registry::FPSrender);
}

void RenderingController::render()
{
    qDebug("render()");
    dynamic_cast<MainController*>(m_mainController)->m_controlWindow->updateData(m_renderingTimer->interval());
}
