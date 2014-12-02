#include "camglwidget.h"
#include "maincontroller.h"
#include "registry.h"
#include <QMutexLocker>

CamGLWidget::CamGLWidget(QObject* parent):
    m_mainController(parent),
    m_camera1stPerson(new GLCamera1stPerson),
    m_camera3rdPerson(new GLCamera3rdPerson),
    m_renderingTimer(new QTimer(this))
{
    MainController* mainController = dynamic_cast<MainController*>(parent);
    m_objects = &(mainController->m_objects);
    m_quadrotor = dynamic_cast<QuadrotorObject*>(m_objects->front().data());
    m_objectsMutex = &(mainController->m_objectsMutex);
    m_type = Camera::ThirdPersonView;
    connect(m_renderingTimer.data(), SIGNAL(timeout()), this, SLOT(render()));

    m_cameraList.push_back( m_camera1stPerson );
    m_cameraList.push_back( m_camera3rdPerson );
}

void CamGLWidget::initializeGL()
{
    m_camera3rdPerson->setCameraPos(QVector3D(5,5,5));
    m_camera3rdPerson->setMinDist(0.3);
    m_camera3rdPerson->setMaxDist(200);
    m_camera3rdPerson->setViewAngle(90);
    m_camera3rdPerson->resize(width(), height());
    m_camera3rdPerson->setCameraPos(QVector3D(2, 2, 4));

    m_camera1stPerson->setCameraPos(QVector3D(5,5,-5));
    m_camera1stPerson->setMinDist(0.3);
    m_camera1stPerson->setMaxDist(Registry::qoCameraViewDistance);
    m_camera1stPerson->setViewAngle(Registry::qoCameraViewAngle);
    m_camera1stPerson->resize(width(), height());
    m_camera1stPerson->setCameraPos(QVector3D(0, 10, 12));

    foreach (auto object, *m_objects) {
        object->init();
        object->setLight(nullptr);
    }

    m_camera3rdPerson->setCenter(m_quadrotor->pos());
}

void CamGLWidget::paintGL()
{
    QMutexLocker locker(m_objectsMutex);
    Q_UNUSED(locker)

    dynamic_cast<MainController*>(m_mainController)->m_controlWindow->updateData(m_renderingTimer->interval());

    glClearColor(0,0,0,1);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    QMatrix4x4 MVP = ( m_type == FirstPersonView ? m_camera1stPerson->getProjectionMatrix() : m_camera3rdPerson->getProjectionMatrix() );
    QVector3D eyePos = ( m_type == FirstPersonView ? m_camera1stPerson->pos() : m_camera3rdPerson->pos() );

    foreach (QSharedPointer<GLObject> object, *m_objects) {
        object->render(MVP, eyePos);
    }
}

float clamp(float x, float a, float b)
{
    if(a > x)
        return a;
    if(b < x)
        return b;
    return x;
}

void CamGLWidget::mousePressEvent(QMouseEvent* ev)
{
    pmouse.setX(ev->x());
    pmouse.setY(ev->y());
}

void CamGLWidget::mouseMoveEvent(QMouseEvent* ev)
{
    if(ev->buttons()) {
        m_camera3rdPerson->addPhi((ev->x() - pmouse.x()) * MOUSE_SENSITIVITY);
        m_camera3rdPerson->addTheta(-(ev->y() - pmouse.y()) * MOUSE_SENSITIVITY);
    }
    pmouse.setX(ev->x());
    pmouse.setY(ev->y());
}

void CamGLWidget::keyPressEvent(QKeyEvent* ev)
{
    //GLCamera* camera = m_camera3rdPerson;

    /*if(ev->key() == Qt::Key_Up || ev->key() == Qt::Key_W) {
        QVector3D to(qSin(camera->yaw()) * qCos(camera->pitch()),
                     qCos(camera->yaw()) * qCos(camera->pitch()),
                     qSin(camera->pitch()));
        camera->addCameraPos( to * KEY_SENSITIVITY );
    } else if(ev->key() == Qt::Key_Down || ev->key() == Qt::Key_S) {
        QVector3D to(qSin(camera->yaw()) * qCos(camera->pitch()),
                     qCos(camera->yaw()) * qCos(camera->pitch()),
                     qSin(camera->pitch()));
        camera->subCameraPos( to * KEY_SENSITIVITY );
    } else if(ev->key() == Qt::Key_Left || ev->key() == Qt::Key_A) {
        QVector3D to(qCos(camera->yaw()), -qSin(camera->yaw()), 0);
        camera->subCameraPos( to * KEY_SENSITIVITY );
    } else if(ev->key() == Qt::Key_Right || ev->key() == Qt::Key_D) {
        QVector3D to(qCos(camera->yaw()), -qSin(camera->yaw()), 0);
        camera->addCameraPos( to * KEY_SENSITIVITY );
    } else if(ev->key() == Qt::Key_U) {
        // decrease pitch angle
        m_quadrotor->changePitch('-');
    } else if(ev->key() == Qt::Key_J) {
        // increase pitch angle
        m_quadrotor->changePitch('+');
    } else if(ev->key() == Qt::Key_H) {
        // decrease roll angle
        m_quadrotor->changeRoll('-');
    } else if(ev->key() == Qt::Key_K) {
        // increase roll angle
        m_quadrotor->changeRoll('+');
    } else if(ev->key() == Qt::Key_Y) {
        // decrease yaw angle
        m_quadrotor->changeYaw('-');
    } else if(ev->key() == Qt::Key_I) {
        // increase yaw angle
        m_quadrotor->changeYaw('+');
    }*/
    if(ev->key() == Qt::Key_W) {
        m_camera3rdPerson->addR(-1.0);
    } else if(ev->key() == Qt::Key_S) {
        m_camera3rdPerson->addR(+1.0);
    }
}

void CamGLWidget::closeEvent(QCloseEvent* ev)
{
    Q_UNUSED(ev)
    emit closed();
}

void CamGLWidget::setCamera1stPerson()
{
    m_type = Camera::FirstPersonView;
}

void CamGLWidget::setCamera3rdPerson()
{
    m_type = Camera::ThirdPersonView;
}

void CamGLWidget::start()
{
    m_renderingTimer->start(SEC / Registry::FPSrender);
}

void CamGLWidget::render()
{
    updateGL();
}
