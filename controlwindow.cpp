#include "controlwindow.h"
#include "ui_controlwindow.h"

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
    // TODO: add other properties
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

void ControlWindow::updateData(qreal delta)
{
    qDebug("update gps data");
    m_time += (delta / 1000.0);
    addGPSData();
    addVelocityData();
}

void ControlWindow::addGPSData()
{
    ui->GPSGLWidget->graph(OX)->addData(m_time, qSin(m_time));
    ui->GPSGLWidget->graph(OY)->addData(m_time, 2*qSin(m_time + M_PI / 3));
    ui->GPSGLWidget->graph(OZ)->addData(m_time, qSin(m_time + 2 * M_PI / 3));
    // remove data of lines that's outside visible range:
    ui->GPSGLWidget->graph(OX)->removeDataBefore(m_time-5);
    ui->GPSGLWidget->graph(OY)->removeDataBefore(m_time-5);
    ui->GPSGLWidget->graph(OZ)->removeDataBefore(m_time-5);
    // rescale value (vertical) axis to fit the current data:
    ui->GPSGLWidget->graph(OX)->rescaleValueAxis(false);
    ui->GPSGLWidget->graph(OY)->rescaleValueAxis(false);
    ui->GPSGLWidget->graph(OZ)->rescaleValueAxis(true);
    // make key axis range scroll with the data (at a constant range size of 5):
    ui->GPSGLWidget->xAxis->setRange(m_time+0.25, 5, Qt::AlignRight);
    ui->GPSGLWidget->replot();
}

void ControlWindow::addVelocityData()
{
    ui->VelocitiesGLWidget->graph(VX)->addData(m_time, qSin(m_time) + (qrand()%10) / 10.0);
    ui->VelocitiesGLWidget->graph(VY)->addData(m_time, 2*qSin(m_time + M_PI / 3) + (qrand()%10) / 10.0);
    ui->VelocitiesGLWidget->graph(VZ)->addData(m_time, qSin(m_time + 2 * M_PI / 3) + (qrand()%10) / 10.0);
    // remove data of lines that's outside visible range:
    ui->VelocitiesGLWidget->graph(VX)->removeDataBefore(m_time-5);
    ui->VelocitiesGLWidget->graph(VY)->removeDataBefore(m_time-5);
    ui->VelocitiesGLWidget->graph(VZ)->removeDataBefore(m_time-5);
    // rescale value (vertical) axis to fit the current data:
    ui->VelocitiesGLWidget->graph(VX)->rescaleValueAxis(false);
    ui->VelocitiesGLWidget->graph(VY)->rescaleValueAxis(false);
    ui->VelocitiesGLWidget->graph(VZ)->rescaleValueAxis(true);
    // make key axis range scroll with the data (at a constant range size of 5):
    ui->VelocitiesGLWidget->xAxis->setRange(m_time+0.25, 5, Qt::AlignRight);
    ui->VelocitiesGLWidget->replot();
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

}
