#include "gllight.h"
#include <QtMath>

GLLight::GLLight(QObject *parent): QObject(parent)
{
    R = 0.1;
    RKa = 0.8, RKd = 0.5, RKs = 0.5,
    GKa = 0.8, GKd = 0.5, GKs = 0.5,
    BKa = 0.8, BKd = 0.6, BKs = 0.5;
    alpha = 40.5;
    m_col.setX(0.9);m_col.setY(0.9);m_col.setZ(0.9);
    m_pos.setX(10);m_pos.setY(10);m_pos.setZ(10);
}

GLLight::~GLLight()
{
}

qreal GLLight::Ka(char rgb)
{
    if(rgb == 'r') {
        return RKa;
    } else if(rgb == 'g') {
        return GKa;
    } else /*if(rgb == 'b')*/ {
        return BKa;
    }
}

qreal GLLight::Kd(char rgb)
{
    if(rgb == 'r') {
        return RKd;
    } else if(rgb == 'g') {
        return GKd;
    } else /*if(rgb == 'b')*/ {
        return BKd;
    }
}

qreal GLLight::Ks(char rgb)
{
    if(rgb == 'r') {
        return RKs;
    } else if(rgb == 'g') {
        return GKs;
    } else /*if(rgb == 'b')*/ {
        return BKs;
    }
}

float GLLight::a()
{
    return alpha;
}

void GLLight::RKaChanged(qreal val)
{
    RKa = val;
}

void GLLight::RKdChanged(qreal val)
{
    RKd = val;
}

void GLLight::RKsChanged(qreal val)
{
    RKs = val;
}

void GLLight::GKaChanged(qreal val)
{
    GKa = val;
}

void GLLight::GKdChanged(qreal val)
{
    GKd = val;
}

void GLLight::GKsChanged(qreal val)
{
    GKs = val;
}

void GLLight::BKaChanged(qreal val)
{
    BKa = val;
}

void GLLight::BKdChanged(qreal val)
{
    BKd = val;
}

void GLLight::BKsChanged(qreal val)
{
    BKs = val;
}

void GLLight::alphaChanged(qreal val)
{
    alpha = val;
}

void GLLight::RColorChanged(qreal val)
{
    m_col.setX(val);
}

void GLLight::GColorChanged(qreal val)
{
    m_col.setY(val);
}

void GLLight::BColorChanged(qreal val)
{
    m_col.setZ(val);
}

void GLLight::XCoordChanged(int val)
{
    m_pos.setX(val);
}

void GLLight::YCoordChanged(int val)
{
    m_pos.setY(val);
}

void GLLight::ZCoordChanged(int val)
{
    m_pos.setZ(val);
}

void GLLight::init()
{
    this->initializeGLFunctions();
    ballGen();
    loadShaders();

    setPos(QVector3D(-99.0, 90.0, 99.0));

    m_prog.bind();

    m_buffer.create();
    m_buffer.setUsagePattern(QGLBuffer::StaticDraw);

    m_prog.release();
}

void GLLight::render(QMatrix4x4 projection)
{
    m_prog.bind();

    m_buffer.bind();
    m_buffer.allocate(m_data.data(), m_data.size() * sizeof(GLfloat));
    m_prog.enableAttributeArray("vertex");
    m_prog.setAttributeBuffer("vertex", GL_FLOAT, 0, 3);
    m_buffer.release();

    projection.translate(m_pos);

    m_prog.setUniformValue("color", m_col);
    m_prog.setUniformValue("projection", projection);

    glDrawArrays(GL_TRIANGLES, 0, m_data.size());

    m_prog.release();
}

QVector3D GLLight::pos()
{
    return m_pos;
}

QVector3D GLLight::color()
{
    return m_col;
}

void GLLight::setPos(QVector3D pos)
{
    m_pos = pos;
}

void GLLight::loadShaders()
{
    m_prog.addShaderFromSourceFile(QGLShader::Vertex, ":/shaders/balloflight.vert");
    m_prog.addShaderFromSourceFile(QGLShader::Fragment, ":/shaders/balloflight.frag");
    m_prog.link();
}

void GLLight::ballGen()
{
    auto F = [&](float phi, float psi) -> QVector3D {
        GLfloat c_phi = qCos(phi);
        GLfloat c_psi = qCos(psi);
        GLfloat s_phi = qSin(phi);
        GLfloat s_psi = qSin(psi);

        return QVector3D(
                    R * c_phi * s_psi,
                    R * s_phi * s_psi,
                    R * c_psi
        );
    };

    GLfloat h = M_PI / 20.0;
    for(GLfloat phi = 0.0; phi < 2 * M_PI; phi += h) {
        for(GLfloat psi = 0.0; psi < 2 * M_PI; psi += h) {
            QVector3D phi_psi = F(phi, psi);
            QVector3D phi_h_psi = F(phi + h, psi);
            QVector3D phi_psi_h = F(phi, psi + h);
            QVector3D phi_h_psi_h = F(phi + h, psi + h);

            m_data.push_back( phi_psi.x() ); m_data.push_back( phi_psi.y() ); m_data.push_back( phi_psi.z() );
            m_data.push_back( phi_h_psi.x() ); m_data.push_back( phi_h_psi.y() ); m_data.push_back( phi_h_psi.z() );
            m_data.push_back( phi_psi_h.x() ); m_data.push_back( phi_psi_h.y() ); m_data.push_back( phi_psi_h.z() );

            m_data.push_back( phi_psi_h.x() ); m_data.push_back( phi_psi_h.y() ); m_data.push_back( phi_psi_h.z() );
            m_data.push_back( phi_h_psi.x() ); m_data.push_back( phi_h_psi.y() ); m_data.push_back( phi_h_psi.z() );
            m_data.push_back( phi_h_psi_h.x() ); m_data.push_back( phi_h_psi_h.y() ); m_data.push_back( phi_h_psi_h.z() );
        }
    }
}
