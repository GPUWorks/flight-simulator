#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include <QGLWidget>
#include "lib/qcustomplot.h"

Q_DECLARE_METATYPE(QCPRange)

class GraphWidget : public QCustomPlot
{
    Q_OBJECT
public:
    explicit GraphWidget(QWidget* parent = 0);
};

#endif // GRAPHWIDGET_H
