#include "test3rdpersoncamera.h"

Test3rdPersonCamera::Test3rdPersonCamera():
    QObject(nullptr)
{
    m_camera.setCenter(QVector3D(5,5,5));
    m_camera.setTheta(45);
    m_camera.setPhi(45);
    m_camera.setR(15);
}

void Test3rdPersonCamera::testCase()
{
    QFETCH(Cmd, cmd);
    QFETCH(qreal, resVal1);
    QFETCH(qreal, resVal2);

    QCOMPARE(exec1Cmd(cmd), resVal1);
    QCOMPARE(exec2Cmd(cmd), resVal2);
}

void Test3rdPersonCamera::testCase_data()
{
    QTest::addColumn<Cmd>("cmd");
    QTest::addColumn<qreal>("resVal1");
    QTest::addColumn<qreal>("resVal2");

    QTest::newRow("R_1") << Cmd(Cmd::R, +4)  << 19.0 << 19.0;
    QTest::newRow("R_2") << Cmd(Cmd::R, +4)  << 19.0 << 23.0;
    QTest::newRow("R_3") << Cmd(Cmd::R, -14) << 15.0 << 9.0;
    QTest::newRow("R_4") << Cmd(Cmd::R, -5)  << 10.0 << 9.0;

    QTest::newRow("Phi_1") << Cmd(Cmd::PHI, +4)    << +49.0  << +49.0;
    QTest::newRow("Phi_2") << Cmd(Cmd::PHI, +180)  << +225.0 << +229.0;
    QTest::newRow("Phi_3") << Cmd(Cmd::PHI, +140)  << +185.0 << +9.0;
    QTest::newRow("Phi_4") << Cmd(Cmd::PHI, -412)  << -7.0   << -43.0;
    QTest::newRow("Phi_5") << Cmd(Cmd::PHI, 0)     << 45.0   << -43.0;

    QTest::newRow("Theta_1") << Cmd(Cmd::THETA, +4)    << +49.0   << +49.0;
    QTest::newRow("Theta_2") << Cmd(Cmd::THETA, +180)  << +225.0  << +49.0;
    QTest::newRow("Theta_3") << Cmd(Cmd::THETA, -90)   << -45.0   << +49.0;
    QTest::newRow("Theta_4") << Cmd(Cmd::THETA, -40)   << +5.0    << +49.0;
    QTest::newRow("Theta_5") << Cmd(Cmd::THETA, 0)     << +45.0    << +49.0;
}

qreal Test3rdPersonCamera::exec1Cmd(Cmd cmd)
{
    GLCamera3rdPerson camera;
    camera.setCenter(QVector3D(5,5,5));
    camera.setTheta(45);
    camera.setPhi(45);
    camera.setR(15);
    return execCmd(cmd, camera);
}

qreal Test3rdPersonCamera::exec2Cmd(Cmd cmd)
{
    return execCmd(cmd, m_camera);
}

qreal Test3rdPersonCamera::execCmd(Cmd cmd, GLCamera3rdPerson& cam)
{
    if(cmd.type == Cmd::R) {
        cam.addR(cmd.delta);
        return cam.R();
    } else if(cmd.type == Cmd::THETA) {
        cam.addTheta(cmd.delta);
        return cam.theta();
    } else {
        cam.addPhi(cmd.delta);
        return cam.phi();
    }
}
