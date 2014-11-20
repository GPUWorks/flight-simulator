#ifndef CAMGLWIDGET_H
#define CAMGLWIDGET_H

#include <QGLWidget>
#include <QCloseEvent>

class CamGLWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit CamGLWidget(QWidget *parent = nullptr);

    void setEvents(bool state);

    virtual void initializeGL();
    virtual void resizeGL(int w, int h);
    virtual void paintGL();

    virtual void mousePressEvent(QMouseEvent* ev);
    virtual void mouseMoveEvent(QMouseEvent* ev);
    virtual void keyPressEvent(QKeyEvent* ev);

    virtual void closeEvent(QCloseEvent* ev);

signals:
    void closed();
    void mousePress(QMouseEvent*);
    void mouseMove(QMouseEvent*);
    void keyPress(QKeyEvent*);

public slots:
    void mousePressSlot(QMouseEvent* ev);
    void mouseMoveSlot(QMouseEvent* ev);
    void keyPressSlot(QKeyEvent* ev);

private:
    bool m_events;
};

#endif // CAMGLWIDGET_H
