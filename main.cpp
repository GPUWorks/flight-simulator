#include <QApplication>

#define __TESTS__

#ifndef __TESTS__
    #include "maincontroller.h"
#else
    #include <QTest>
    #include "tests/test3rdpersoncamera.h"
#endif

int main(int argc, char *argv[])
{

    QApplication application(argc, argv);
#ifndef __TESTS__
    MainController controller;
    controller.start();
    return application.exec();
#else
    QTest::qExec(new Test3rdPersonCamera, argc, argv);
    return 0;
#endif
}
