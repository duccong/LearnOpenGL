#include "openglwindow.h"
#include <QApplication>
#include <QSurfaceFormat>
#include <hellotriangle.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //[1]
    HelloTriangle w;

    //[2]
    // set SurfaceFormat
    QSurfaceFormat *fmt = new QSurfaceFormat();
    fmt->setRenderableType(QSurfaceFormat::OpenGL);
    fmt->setVersion(3,3);
    fmt->setProfile(QSurfaceFormat::CoreProfile);
    w.setSurfaceFormat(fmt);

    //[3]
    w.resize(640,480);
    w.show();

    return a.exec();
}
