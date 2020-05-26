/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the documentation of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "openglwindow.h"

#include <QtCore/QCoreApplication>

#include <QtGui/QOpenGLContext>
#include <QtGui/QOpenGLPaintDevice>
#include <QtGui/QPainter>

//! [1]
OpenGLWindow::OpenGLWindow(QWindow *parent)
    : QWindow(parent)
    , m_animating(false)
    , m_context(0)
    , m_device(0)
{
    setSurfaceType(QWindow::OpenGLSurface);
    path = "C:/Users/cong.tran/Documents/LearningOpenGL/";
//    path = "/Users/congductran/Project/LearnOpenGL/";
    lastX = width()/2;
    lastY = height()/2;
    isPress = false;
}
//! [1]

OpenGLWindow::~OpenGLWindow()
{
    delete m_device;
}
//! [2]
void OpenGLWindow::render(QPainter *painter)
{
    Q_UNUSED(painter);
}

void OpenGLWindow::initialize()
{
    qDebug("OpenGLWindow::initialize()");
}

void OpenGLWindow::render()
{

    if (!m_device){
        m_device = new QOpenGLPaintDevice;

    }
    qDebug("OpenGLWindow::render()");
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    m_device->setSize(size());

    QPainter painter(m_device);
    render(&painter);
}
//! [2]

//! [3]
void OpenGLWindow::renderLater()
{
    requestUpdate();
}

bool OpenGLWindow::event(QEvent *event)
{

    switch (event->type()) {
    case QEvent::UpdateRequest:
        renderNow();
        return true;
    case QEvent::KeyPress:{
        QKeyEvent* key = static_cast<QKeyEvent*>(event);
//        qDebug()<< "QEvent::KeyPress: " << key->key();
        emit sigKeyPress(key);
    }
        return true;
    case QEvent::MouseButtonPress: {
        sigMousePress(event);
    }
        return true;
    case QEvent::MouseButtonRelease: {
        sigMousePress(event);
    }
        return true;
    case QEvent::MouseMove: {
        sigMousePress(event);
    }
        return true;
    default:
        return QWindow::event(event);
    }
}

void OpenGLWindow::exposeEvent(QExposeEvent *event)
{
    Q_UNUSED(event);

    if (isExposed())
        renderNow();
}
//! [3]

//! [4]
void OpenGLWindow::renderNow()
{
    if (!isExposed())
        return;

    bool needsInitialize = false;

    if (!m_context) {
        m_context = new QOpenGLContext(this);
        if (!m_fmt){
            m_context->setFormat(requestedFormat());
        } else {
             m_context->setFormat(*m_fmt);
        }

        m_context->create();

        needsInitialize = true;
    }

    m_context->makeCurrent(this);

    if (needsInitialize) {
        initializeOpenGLFunctions();
        initialize();
    }

    render();

    m_context->swapBuffers(this);

    if (m_animating)
        renderLater();
}
//! [4]

//! [5]
void OpenGLWindow::setAnimating(bool animating)
{
    m_animating = animating;

    if (animating)
        renderLater();
}

void OpenGLWindow::setSurfaceFormat(QSurfaceFormat *fmt)
{
    m_fmt = fmt;
}

unsigned int OpenGLWindow::loadTexture(char const * path)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    QImage* img = new QImage(path);
    width = img->width();
    height = img->height();
//    nrComponents = img->al

    *img = img->convertToFormat(QImage::Format_RGBA8888, Qt::AutoColor);
//    if (data)
//    {
//        qDebug("width: %d, height: %d", img->width(),img->height());
//        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img->width(),img->height() , 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
//        glGenerateMipmap(GL_TEXTURE_2D);
//    }
    unsigned char *data = img->bits();
    if (data)
    {
        GLenum format;
//        if (nrComponents == 1)
//            format = GL_RED;
//        else if (nrComponents == 3)
//            format = GL_RGB;
//        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        free(img);
        free(data);
    }
    else
    {
        qDebug()<< "Texture failed to load at path: " << path ;
        free(img);
        free(data);
    }

    return textureID;
}

//! [5]

