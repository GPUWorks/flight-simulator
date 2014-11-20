#ifndef PHYSICSCONTROLLER_H
#define PHYSICSCONTROLLER_H

#include <QObject>
#include <QTimer>
#include "globject.h"
#include "graphwidget.h"

class MainController;

class PhysicsController : public QObject
{
    Q_OBJECT
public:
    explicit PhysicsController(QObject* mainController);

signals:
    void crashed();
    void finished();

public slots:
    void start();

protected slots:
    void updatePhysicalProperties();

private:
    QObject* m_mainController;
    QScopedPointer<QTimer> m_physicsTimer;
    QList< QSharedPointer<GLObject> >* m_objects;
    QMutex* m_objectsMutex;
    qreal m_time;
};

#endif // PHYSICSCONTROLLER_H
