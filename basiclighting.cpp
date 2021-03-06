#include "basiclighting.h"

BasicLighting::BasicLighting()
{
    isOpenGLInited = false;
    tmp = 0.0;
    tmp2 = false;
    isMousePress = false;
    setAnimating(false);
    connect(this,SIGNAL(sigKeyPress(QKeyEvent*)),this,SLOT(slotKeyPress(QKeyEvent*)));
    connect(this,SIGNAL(sigMousePress(QEvent*)),this,SLOT(slotMousePress(QEvent*)));

    yaw = -90.0f;
    pitch = 0;
    fov = 30;
    sensitivity = 0.00001f;
    lastX = width()/2;
    lastY = height()/2;

    specularStrength = 0.5;
//glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

    setAnimating(true);

}

void BasicLighting::initialize()
{
    qDebug("HelloTriangle::initialize()");


    initOpenGL();
}

void BasicLighting::render()
{


//    qDebug("HelloTriangle::render()");
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT  | GL_DEPTH_BUFFER_BIT  );

    tmp+=1;
//    fTmp2 += 0.01f;

    QMatrix4x4 projection;
    projection.perspective(45, width()/height(), 0.1f, 100.0f);

    QMatrix4x4 view,viewCamera;

    const float radius = 10.0f;
    float camX = qSin(fTmp2) * radius;
    float camZ = qCos(fTmp2) * radius;

//    view.lookAt(QVector3D(camX, 0.0,camZ), QVector3D(0.0, 0.0, 0.0),QVector3D(0.0, 1.0, 0.0));
//    view.lookAt(*cameraPos+QVector3D(camX, 0.0, camZ), (*cameraPos + *cameraFront), *cameraUp);

    // [] YAW, PITCH

    QVector3D cameraDirection ;
    cameraDirection.setX( qCos(qRadiansToDegrees(yaw)) * qCos(qRadiansToDegrees(pitch)));
    cameraDirection.setY( qSin(qRadiansToDegrees(pitch)));
    cameraDirection.setZ( qSin(qRadiansToDegrees(yaw)) * qCos(qRadiansToDegrees(pitch)));
    cameraDirection.normalize();
    // ![]

//    view.lookAt(*cameraPos, (*cameraPos + *cameraFront), *cameraUp);
    viewCamera.lookAt(*cameraPos, *cameraPos + cameraDirection, *cameraUp);
//     viewCamera.lookAt(QVector3D(camX, 0.0,camZ), QVector3D(0.0, 0.0, 0.0),QVector3D(0.0, 1.0, 0.0));

//    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, view.data());

    QVector3D cubePositions[] = {
        QVector3D( -0.5f,  0.0f,  0.0f),
//        QVector3D( 2.0f,  5.0f, -15.0f),
//        QVector3D(-1.5f, -2.2f, -2.5f),
//        QVector3D(-3.8f, -2.0f, -12.3f),
//        QVector3D( 2.4f, -0.4f, -3.5f),
//        QVector3D(-1.7f,  3.0f, -7.5f),
//        QVector3D( 1.3f, -2.0f, -2.5f),
//        QVector3D( 1.5f,  2.0f, -2.5f),
//        QVector3D( 1.5f,  0.2f, -1.5f),
//        QVector3D(-1.3f,  1.0f, -1.5f)
    };

    for(unsigned int i = 0; i < sizeof(cubePositions)/sizeof(*cubePositions); i++)
    {
        QMatrix4x4 model;
        model.translate(cubePositions[i]);
        float angle = 20.0f * i;
//        model.rotate(45 , 1.0f, 0.3f, 0.5f);
        if (i%2){
            model.rotate(tmp , 1.0f, 0.3f, 0.5f);
        } else {
            model.rotate(-tmp , 1.0f, 0.3f, 0.5f);
        }

        // color
         lightingShader->use();
        lightingShader->setVec3("objectColor", 1.0f, 0.5f, 0.31f);
        lightingShader->setVec3("lightColor",  1.0f, 1.0f, 1.0f);

        lightingShader->setMat4("projection", projection.data());
        lightingShader->setMat4("view", viewCamera.data());
//        model.translate(-0.5f,0.0f,0.0f);

        lightingShader->setVec3("lightPos", 1.2f, 1.0f, 2.0f);
        lightingShader->setVec3("viewPos",viewCamera.data());

        lightingShader->setMat4("model", model.data());
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);


    }
    // cube
     QMatrix4x4 model;
    lightCubeShader->use();
    model.setToIdentity();
    model.rotate(45 , 1.0f, 0.3f, 0.5f);
    lightCubeShader->setMat4("model", model.data());
    lightCubeShader->setMat4("projection", projection.data());
    lightCubeShader->setMat4("view", viewCamera.data());
    model.translate(1.2f,1.0f,1.0f); // lightpos
    model.scale(0.2f);
    //        model.rotate(-tmp , 1.0f, 0.3f, 0.5f);
    lightCubeShader->setMat4("model", model.data());

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);

//    ourShader->setMat4("transform",matrix.data());

//    glDrawArrays(GL_TRIANGLES, 0, 36);
//    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void BasicLighting::initOpenGL()
{
    if (isOpenGLInited){
        return;
    }

    glEnable(GL_DEPTH_TEST);

//    m_context->makeCurrent(this);
    qDebug("HelloTriangle::initOpenGL()");

    int nrAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
    qDebug("Maximum nr of vertex attributes supported: %d", nrAttributes);

    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
    };

//    unsigned int indices[] = {  // note that we start from 0!
//        0, 1, 3,   // first triangle
//        1, 2, 3    // second triangle
//    };

    //[0] VAO, VBO, EBO, texture

    // VAO // Vertex Array Object
    /* A vertex array object (also known as VAO) can be bound just like a vertex buffer object and any subsequent vertex attribute calls from that point on will be stored inside the VAO
     * A vertex array object stores the following:
     * Calls to glEnableVertexAttribArray or glDisableVertexAttribArray.
     * Vertex attribute configurations via glVertexAttribPointer.
     * Vertex buffer objects associated with vertex attributes by calls to glVertexAttribPointer.
    */
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

    // VBO
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // EBO
//    unsigned int EBO; // element buffer
//    glGenBuffers(1, &EBO);
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    //[1-2-3] init in ourShader
    QString sTmp = path + "2.2.light_cube.vs";
    QString sTmp2 = path + "2.2.light_cube.fs";
//    ourShader = new Shader(sTmp.toLocal8Bit().data(), sTmp2.toLocal8Bit().data());

    lightCubeShader = new Shader(sTmp.toLocal8Bit().data(), sTmp2.toLocal8Bit().data());

    sTmp = path + "2.2.basic_lighting.vs";
    sTmp2 = path + "2.2.basic_lighting.fs";

    lightingShader  = new Shader(sTmp.toLocal8Bit().data(), sTmp2.toLocal8Bit().data());

    // [4] Set Data to Array
    // get the attribute location with glGetAttribLocation
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);
//    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
//    glEnableVertexAttribArray(2);

    // ===================== LIGHT CUBE
    glGenVertexArrays(1, &lightCubeVAO);
    glBindVertexArray(lightCubeVAO);

    // we only need to bind to the VBO (to link it with glVertexAttribPointer), no need to fill it; the VBO's data already contains all we need (it's already bound, but we do it again for educational purposes)
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
//    cameraUp.crossProduct(cameraDirection, cameraRight).normalize();

    cameraPos   = new QVector3D(5.0f, 0.0f,  -30.0f);
    cameraFront = new QVector3D(0.0f, 0.0f, -1.0f);
    cameraUp    = new QVector3D(0.0f, 1.0f,  0.0f);
    cameraSpeed = 24/screen()->refreshRate();

//    cameraDirection = cameraDirection.normalized();

    // setup view
//    ourShader->use();
//    QMatrix4x4 view;
//    QMatrix4x4 projection;
//    view.translate(0.0f, 0.0f, -3.0f);
//    projection.ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 100.0f);
//    projection.perspective(45.0f, width()/height(), 0.1f, 100.0f);
//    unsigned int viewLoc  = glGetUniformLocation(ourShader->ID, "viewTmp");
//    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, view.data());
//    ourShader->setMat4("projection", projection.data());

//    QMatrix4x4 viewCamera;
//    viewCamera.lookAt(QVector3D(0.0f, 0.0f, 3.0f),
//                      QVector3D(0.0f, 0.0f, 0.0f),
//                      QVector3D(0.0f, 1.0f, 0.0f));

    // ===================== Load our shader
//    ourShader->use();
//    ourShader->setInt("texture1", 0);
//    ourShader->setInt("texture2", 1);

//    glActiveTexture(GL_TEXTURE0);
//    glBindTexture(GL_TEXTURE_2D, texture2);

//    glActiveTexture(GL_TEXTURE1);
//    glBindTexture(GL_TEXTURE_2D, texture);



    glViewport(0,0,width(),height());
    //
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
//    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    isOpenGLInited = true;

//    delete img;
//    delete img2;
}

void BasicLighting::freePoint()
{

}

void BasicLighting::slotKeyPress(QKeyEvent *key)
{
    qDebug()<< "Camera::KeyPress: " << key->key();
    switch (key->key()) {
    case Qt::Key_Up:
        qDebug()<< "Camera::KeyPress: Key_Up";
        qDebug()<< "cameraFront" << *cameraFront;
        qDebug()<< "cameraUp" << *cameraUp;
        qDebug()<< "cameraPos" << *cameraPos;

        *cameraPos -= (cameraSpeed) * (*cameraFront);
        break;
    case Qt::Key_Down:
        qDebug()<< "Camera::KeyPress: Key_Down";
        qDebug()<< "cameraFront" << *cameraFront;
        qDebug()<< "cameraUp" << *cameraUp;
        qDebug()<< "cameraPos" << *cameraPos;

        *cameraPos += cameraSpeed * (*cameraFront);
        qDebug()<< *cameraPos;
        break;
    case Qt::Key_Left:{
        qDebug()<< "Camera::KeyPress: Key_Left";
        QVector3D tmp;
        qDebug()<< "cameraFront" << *cameraFront;
        qDebug()<< "cameraUp" << *cameraUp;
        qDebug()<< "cameraPos" << *cameraPos;
        tmp = tmp.crossProduct(*cameraFront,*cameraUp);
        tmp.normalize();
        fTmp2 -=0.1;

        *cameraPos += tmp * cameraSpeed;
        qDebug()<< *cameraPos;
        break;
    }

    case Qt::Key_Right:{
        qDebug()<< "Camera::KeyPress: Key_Right";
        qDebug()<< "cameraFront" << *cameraFront;
        qDebug()<< "cameraUp" << *cameraUp;
        qDebug()<< "cameraPos" << *cameraPos;
        QVector3D tmp2;
        fTmp2 +=0.1;
        tmp2 = tmp2.crossProduct(*cameraFront,*cameraUp);

        *cameraPos -= tmp2.normalized() * cameraSpeed;
        break;
    }
    default: {
        qDebug()<< "Camera::KeyPress: default" << key->text();
        if (key->text().compare("a") == 0 ){
            yaw   -= 0.0001f;
        }
        if (key->text().compare("d") == 0 ){
            yaw   += 0.0001f;
        }
        if (key->text().compare("s") == 0 ){
            pitch   -= 0.0001f;
        }
        if (key->text().compare("w") == 0 ){
            pitch   += 0.0001f;
        }
        if (key->text().compare("z") == 0 ){
            fov   += 1.5f;
        }
        if (key->text().compare("x") == 0 ){
            fov   -= 1.5f;
        }
    }
    }
    requestUpdate();
}

void BasicLighting::slotMousePress(QEvent *event)
{
    QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
    switch (event->type()) {
    case QEvent::MouseButtonPress: {

        isMousePress = true;
        lastX = mouseEvent->x();
        lastY = mouseEvent->y();
        tmpYaw = yaw;
        tmpPitch = pitch;
        qDebug()<< "Camera::MouseButtonPress: " << mouseEvent->x() << ","<< mouseEvent->y();
    }
        break;
    case QEvent::MouseButtonRelease: {
        isMousePress = false;
//        qDebug()<< "Camera::MouseButtonRelease: " << event;
    }
        break;
    case QEvent::MouseMove: {
        if (isMousePress){
//            qDebug()<< "Camera::MouseMove: " << event;
            float xoffset = mouseEvent->x() - lastX;
            float yoffset = mouseEvent->y() - lastY;
            qDebug()<< "Camera::MouseMove: " << xoffset;
             qDebug()<< "Camera::MouseMove: " << yoffset;

            xoffset *= sensitivity;
            yoffset *= sensitivity;

            fov -= (float)yoffset;
            if (fov < 1.0f)
                fov = 1.0f;
            if (fov > 45.0f)
                fov = 45.0f;

            yaw = tmpYaw;
            pitch = tmpPitch;
            yaw   -= xoffset;
            pitch -= yoffset;

            if(pitch > 89.0f)
                pitch = 89.0f;
            if(pitch < -89.0f)
                pitch = -89.0f;

            qDebug()<< "pitch: " << pitch << " -yaw: " << yaw <<"-fov: " <<fov;
        }
        break;
    }
    default:
        return;
    }
}
