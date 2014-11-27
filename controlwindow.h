#ifndef CONTROLWINDOW_H
#define CONTROLWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>
#include "quadrotorobject.h"

namespace Ui {
class ControlWindow;
}

class ControlWindow : public QMainWindow
{
    Q_OBJECT
    friend class MainController;
    friend class PhysicsController;
    enum GPS { OX = 0, OY = 1, OZ = 2 };
    enum Velocities { VX = 0, VY = 1, VZ = 2 };
    enum Angles { ROLL = 0, PITCH = 1, YAW = 2 };
public:
    explicit ControlWindow(QObject* mainController);
    ~ControlWindow();
    void setUpQuadrotorPointer();

    void updateData(qreal delta);
    virtual void closeEvent(QCloseEvent* ev);

signals:
    void closed();

protected: // setting up GraphWidgets
    void setUpGPSGraph();
    void setUpVelocityGraph();
    void setUpAngleGraph();
    void addGPSData();
    void addVelocityData();
    void addAngleData();

private:
    QObject* m_mainController;
    Ui::ControlWindow *ui;
    qreal m_time;
    QuadrotorObject* m_quadrotor;
};

#endif // CONTROLWINDOW_H
