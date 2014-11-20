#ifndef RENDERINGCONTROLLER_H
#define RENDERINGCONTROLLER_H

#include <QObject>
#include <QScopedPointer>
#include <QTimer>
#include "globject.h"
#include "camglwidget.h"

class MainController;

class RenderingController : public QObject
{
    Q_OBJECT
public:
    explicit RenderingController(QObject* mainController);
    void start();

signals:
    void crashed();
    void finished();

protected slots:
    void render();

private:
    QObject* m_mainController;
    QScopedPointer<QTimer> m_renderingTimer;
    QList< QSharedPointer<GLObject> >* m_objects;
    QMutex* m_objectsMutex;

private: // rendering windows
    CamGLWidget* m_simulationWindow;
    CamGLWidget* m_controlWindow;
};

#endif // RENDERINGCONTROLLER_H
