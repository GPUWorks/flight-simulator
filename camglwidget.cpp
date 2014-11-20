#include "camglwidget.h"

CamGLWidget::CamGLWidget(QWidget* parent) :
    QGLWidget(parent), m_events(false)
{
}

void CamGLWidget::setEvents(bool state)
{
    m_events = state;
}

void CamGLWidget::initializeGL()
{

}

void CamGLWidget::resizeGL(int w, int h)
{
    Q_UNUSED(w)
    Q_UNUSED(h)
}

void CamGLWidget::paintGL()
{
    glClearColor(1,0,0,1);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    // ...
}

void CamGLWidget::mousePressSlot(QMouseEvent* ev)
{
    mousePressEvent(ev);
}

void CamGLWidget::mouseMoveSlot(QMouseEvent* ev)
{
    mouseMoveEvent(ev);
}

void CamGLWidget::keyPressSlot(QKeyEvent* ev)
{
    keyPressEvent(ev);
}

void CamGLWidget::mousePressEvent(QMouseEvent* ev)
{
    if(m_events == true) {
        emit mousePress(ev);
    } else {
        Q_UNUSED(ev)
    }
}

void CamGLWidget::mouseMoveEvent(QMouseEvent* ev)
{
    if(m_events == true) {
        emit mouseMove(ev);
    } else {
        Q_UNUSED(ev)
    }
}

void CamGLWidget::keyPressEvent(QKeyEvent* ev)
{
    if(m_events == true) {
        emit keyPress(ev);
    } else {
        Q_UNUSED(ev)
    }
}

void CamGLWidget::closeEvent(QCloseEvent* ev)
{
    Q_UNUSED(ev)
    emit closed();
}
