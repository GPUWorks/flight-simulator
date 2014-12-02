#include "controlwindow.h"
#include "ui_controlwindow.h"
#include "maincontroller.h"

ControlWindow::ControlWindow(QObject* mainController) :
    QMainWindow(nullptr),
    m_mainController(mainController),
    ui(new Ui::ControlWindow)
{
    ui->setupUi(this);
    connect(ui->actionStart, SIGNAL(triggered()), m_mainController, SLOT(startSimulation()));
    connect(ui->actionStop,  SIGNAL(triggered()), m_mainController, SLOT(simulationFinished()));
    m_time = 0.0;
    setUpGPSGraph();
    setUpVelocityGraph();
    setUpAngleGraph();
}

ControlWindow::~ControlWindow()
{
    delete ui;
}

void ControlWindow::closeEvent(QCloseEvent* ev)
{
    Q_UNUSED(ev)
    emit closed();
}

void ControlWindow::setUpQuadrotorPointer()
{
    m_quadrotor = dynamic_cast<QuadrotorObject*>( dynamic_cast<MainController*>(m_mainController)->m_objects.front().data() );
}

void ControlWindow::updateData(qreal delta)
{
    qDebug("update gps data");
    m_time += (delta / 1000.0);
    addGPSData();
    addVelocityData();
    addAngleData();
}

void ControlWindow::addGPSData()
{
    QVector3D pos = m_quadrotor->pos();
    ui->GPSGLWidget->graph(OX)->addData(m_time, pos.x());
    ui->GPSGLWidget->graph(OY)->addData(m_time, pos.y());
    ui->GPSGLWidget->graph(OZ)->addData(m_time, pos.z());
    // remove data of lines that's outside visible range:
    ui->GPSGLWidget->graph(OX)->removeDataBefore(m_time-5);
    ui->GPSGLWidget->graph(OY)->removeDataBefore(m_time-5);
    ui->GPSGLWidget->graph(OZ)->removeDataBefore(m_time-5);
    // rescale value (vertical) axis to fit the current data:
    ui->GPSGLWidget->graph(OX)->rescaleValueAxis(true);
    ui->GPSGLWidget->graph(OY)->rescaleValueAxis(true);
    ui->GPSGLWidget->graph(OZ)->rescaleValueAxis(true);
    // make key axis range scroll with the data (at a constant range size of 5):
    ui->GPSGLWidget->xAxis->setRange(m_time+0.25, 5, Qt::AlignRight);
    ui->GPSGLWidget->replot();
}

void ControlWindow::addVelocityData()
{
    ui->VelocitiesGLWidget->graph(VX)->addData(m_time, 0);
    ui->VelocitiesGLWidget->graph(VY)->addData(m_time, 0);
    ui->VelocitiesGLWidget->graph(VZ)->addData(m_time, 0);
    // remove data of lines that's outside visible range:
    ui->VelocitiesGLWidget->graph(VX)->removeDataBefore(m_time-5);
    ui->VelocitiesGLWidget->graph(VY)->removeDataBefore(m_time-5);
    ui->VelocitiesGLWidget->graph(VZ)->removeDataBefore(m_time-5);
    // rescale value (vertical) axis to fit the current data:
    ui->VelocitiesGLWidget->graph(VX)->rescaleValueAxis(true);
    ui->VelocitiesGLWidget->graph(VY)->rescaleValueAxis(true);
    ui->VelocitiesGLWidget->graph(VZ)->rescaleValueAxis(true);
    // make key axis range scroll with the data (at a constant range size of 5):
    ui->VelocitiesGLWidget->xAxis->setRange(m_time+0.25, 5, Qt::AlignRight);
    ui->VelocitiesGLWidget->replot();
}

void ControlWindow::addAngleData()
{
    ui->AnglesGLWidget->graph(ROLL)->addData(m_time, m_quadrotor->roll());
    ui->AnglesGLWidget->graph(PITCH)->addData(m_time, m_quadrotor->pitch());
    ui->AnglesGLWidget->graph(YAW)->addData(m_time, m_quadrotor->yaw());
    // remove data of lines that's outside visible range:
    ui->AnglesGLWidget->graph(ROLL)->removeDataBefore(m_time-5);
    ui->AnglesGLWidget->graph(PITCH)->removeDataBefore(m_time-5);
    ui->AnglesGLWidget->graph(YAW)->removeDataBefore(m_time-5);
    // rescale value (vertical) axis to fit the current data:
    ui->AnglesGLWidget->graph(ROLL)->rescaleValueAxis(true);
    ui->AnglesGLWidget->graph(PITCH)->rescaleValueAxis(true);
    ui->AnglesGLWidget->graph(YAW)->rescaleValueAxis(true);
    // make key axis range scroll with the data (at a constant range size of 5):
    ui->AnglesGLWidget->xAxis->setRange(m_time+0.25, 5, Qt::AlignRight);
    ui->AnglesGLWidget->replot();
}

void ControlWindow::setUpGPSGraph()
{
    ui->GPSGLWidget->setBackground(QBrush(QColor("#e3e3e3")));

    ui->GPSGLWidget->addGraph();
    ui->GPSGLWidget->graph(OX)->setPen(QPen(Qt::blue));

    ui->GPSGLWidget->addGraph();
    ui->GPSGLWidget->graph(OY)->setPen(QPen(Qt::red));

    ui->GPSGLWidget->addGraph();
    ui->GPSGLWidget->graph(OZ)->setPen(QPen(Qt::green));

    ui->GPSGLWidget->xAxis->setTickLabelType(QCPAxis::ltNumber);
    ui->GPSGLWidget->axisRect()->setupFullAxesBox();
}

void ControlWindow::setUpVelocityGraph()
{
    ui->VelocitiesGLWidget->setBackground(QBrush(QColor("#e3e3e3")));

    ui->VelocitiesGLWidget->addGraph();
    ui->VelocitiesGLWidget->graph(VX)->setPen(QPen(Qt::blue));

    ui->VelocitiesGLWidget->addGraph();
    ui->VelocitiesGLWidget->graph(VY)->setPen(QPen(Qt::red));

    ui->VelocitiesGLWidget->addGraph();
    ui->VelocitiesGLWidget->graph(VZ)->setPen(QPen(Qt::green));

    ui->VelocitiesGLWidget->xAxis->setTickLabelType(QCPAxis::ltNumber);
    ui->VelocitiesGLWidget->axisRect()->setupFullAxesBox();
}

void ControlWindow::setUpAngleGraph()
{
    ui->AnglesGLWidget->yAxis->setRange(-2, 2);

    ui->AnglesGLWidget->setBackground(QBrush(QColor("#e3e3e3")));

    ui->AnglesGLWidget->addGraph();
    ui->AnglesGLWidget->graph(ROLL)->setPen(QPen(Qt::blue));

    ui->AnglesGLWidget->addGraph();
    ui->AnglesGLWidget->graph(PITCH)->setPen(QPen(Qt::red));

    ui->AnglesGLWidget->addGraph();
    ui->AnglesGLWidget->graph(YAW)->setPen(QPen(Qt::green));

    ui->AnglesGLWidget->xAxis->setTickLabelType(QCPAxis::ltNumber);
    ui->AnglesGLWidget->axisRect()->setupFullAxesBox();
}
