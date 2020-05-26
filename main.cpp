#include "openglwindow.h"
#include <QApplication>
#include <QSurfaceFormat>
#include <hellotriangle.h>
#include <textures.h>
#include <transform.h>
#include <coordinatesystems.h>
#include <camera.h>
#include <lightingcolor.h>
#include <basiclighting.h>
#include <lightingmaterials.h>
#include <lightingmaps.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //[1]
    LightingMaps w;

    //[2]
    // set SurfaceFormat
    QSurfaceFormat *fmt = new QSurfaceFormat();
    fmt->setRenderableType(QSurfaceFormat::OpenGL);
    fmt->setVersion(3,3);
    fmt->setProfile(QSurfaceFormat::CoreProfile);
    fmt->setDepthBufferSize(24);
//    QSurfaceFormat::setDefaultFormat(format);
    w.setSurfaceFormat(fmt);

    //[3]
    w.resize(640,480);
    w.show();

    return a.exec();
}
