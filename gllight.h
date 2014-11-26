#ifndef GLLIGHT_H
#define GLLIGHT_H

#include <QObject>
#include <QVector3D>
#include <QGLShaderProgram>
#include <QGLFunctions>
#include <QGLBuffer>

class GLLight : public QObject, protected QGLFunctions
{
    Q_OBJECT
public:
    explicit GLLight(QObject *parent = nullptr);
    virtual ~GLLight();

    void init();
    void render(QMatrix4x4 projection);

    QVector3D pos();
    QVector3D color();
    void setPos(QVector3D pos);

    qreal Ka(char rgb);
    qreal Kd(char rgb);
    qreal Ks(char rgb);
    float a();

signals:
    void posChanged();

public slots:
    void RKaChanged(qreal val);
    void RKdChanged(qreal val);
    void RKsChanged(qreal val);

    void GKaChanged(qreal val);
    void GKdChanged(qreal val);
    void GKsChanged(qreal val);

    void BKaChanged(qreal val);
    void BKdChanged(qreal val);
    void BKsChanged(qreal val);

    void alphaChanged(qreal val);

    void RColorChanged(qreal val);
    void GColorChanged(qreal val);
    void BColorChanged(qreal val);

    void XCoordChanged(int val);
    void YCoordChanged(int val);
    void ZCoordChanged(int val);

private:
    void loadShaders();
    void ballGen();

private:
    QGLShaderProgram m_prog;

    QVector<GLfloat> m_data;
    QGLBuffer m_buffer;

    qreal R;
    QVector3D m_pos;
    QVector3D m_col;

    qreal RKa;
    qreal RKd;
    qreal RKs;

    qreal GKa;
    qreal GKd;
    qreal GKs;

    qreal BKa;
    qreal BKd;
    qreal BKs;

    qreal alpha;

};

#endif // GLLIGHT_H
