#ifndef CAMGLWIDGET_H
#define CAMGLWIDGET_H

#include <QGLWidget>
#include <QCloseEvent>
#include "globject.h"
#include "glcamera1stperson.h"
#include "glcamera3rdperson.h"
#include <QTimer>
#include <QScopedPointer>
#include <QSharedPointer>
#include <QMutex>
#include <QList>

class CamGLWidget : public QGLWidget
{
    Q_OBJECT
    enum Camera { FirstPersonView, ThirdPersonView };
public:
    explicit CamGLWidget(QObject* parent);
    void start();

    virtual void initializeGL();
    virtual void paintGL();

    virtual void mousePressEvent(QMouseEvent* ev);
    virtual void mouseMoveEvent(QMouseEvent* ev);
    virtual void keyPressEvent(QKeyEvent* ev);

    virtual void closeEvent(QCloseEvent* ev);

signals:
    void closed();

public slots:
    void setCamera1stPerson();
    void setCamera3rdPerson();
    void render();

private:
    QObject* m_mainController;
    QList< QSharedPointer<GLObject> >* m_objects;
    GLCamera1stPerson* m_camera1stPerson;
    GLCamera3rdPerson* m_camera3rdPerson;
    QList< GLCamera* > m_cameraList;
    Camera m_type;
    QScopedPointer<QTimer> m_renderingTimer;
    QMutex* m_objectsMutex;
    QVector3D pmouse;
};

#endif // CAMGLWIDGET_H
