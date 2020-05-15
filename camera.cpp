#include "camera.h"

Camera::Camera()
{
    isOpenGLInited = false;
    tmp = 0.0;
    tmp2 = false;
    setAnimating(false);
//    setAnimating(true);
}

void Camera::initialize()
{
    qDebug("HelloTriangle::initialize()");


    initOpenGL();
}

void Camera::render()
{

//    qDebug("HelloTriangle::render()");
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT  | GL_DEPTH_BUFFER_BIT  );

//    ourShader->use();

//    if (tmp2){
//        tmp = tmp - 0.01;
//        if (tmp <= -1){
//            tmp2 = false;
//        }
//    } else {
//        tmp = tmp + 0.01;
//        if (tmp >= 1.0){
//            tmp2 = true;
//        }
//    }
    tmp+=0.01;

//    QMatrix4x4 matrix;

    QMatrix4x4 view;
    unsigned int viewLoc  = glGetUniformLocation(ourShader->ID, "view");

    const float radius = 10.0f;
    float camX = qSin(tmp) * radius;
    float camZ = qCos(tmp) * radius;

    QVector3D cameraPos(0.0f, 0.0f,  3.0f);
    QVector3D cameraFront(0.0f, 0.0f, -1.0f);
    QVector3D cameraUp(0.0f, 1.0f,  0.0f);

    view.lookAt(QVector3D(camX, 0.0, camZ), QVector3D(0.0, 0.0, 0.0),QVector3D(0.0, 1.0, 0.0));
//    view.lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, view.data());

    QVector3D cubePositions[] = {
        QVector3D( 0.0f,  0.0f,  0.0f),
        QVector3D( 2.0f,  5.0f, -15.0f),
        QVector3D(-1.5f, -2.2f, -2.5f),
        QVector3D(-3.8f, -2.0f, -12.3f),
        QVector3D( 2.4f, -0.4f, -3.5f),
        QVector3D(-1.7f,  3.0f, -7.5f),
        QVector3D( 1.3f, -2.0f, -2.5f),
        QVector3D( 1.5f,  2.0f, -2.5f),
        QVector3D( 1.5f,  0.2f, -1.5f),
        QVector3D(-1.3f,  1.0f, -1.5f)
    };

    for(unsigned int i = 0; i < 5; i++)
    {
        QMatrix4x4 model;
        model.translate(cubePositions[i]);
        float angle = 20.0f * i;
        if (! (i % 2) ){
            model.rotate(100.0f * tmp / screen()->refreshRate(), 1.0f, 0.5f, 0.25f);
        } else {
            model.rotate(45 , 1.0f, 0.3f, 0.5f);
        }

        ourShader->setMat4("model", model.data());

        glDrawArrays(GL_TRIANGLES, 0, 36);
    }

//    ourShader->setMat4("transform",matrix.data());

//    glDrawArrays(GL_TRIANGLES, 0, 36);
//    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Camera::initOpenGL()
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
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    };

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
    unsigned int EBO; // element buffer
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // texture 1
//    unsigned int texture;
    glGenTextures(1, &texture);
//    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object

    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

//    glBindTexture(GL_TEXTURE_2D, texture); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object

    QImage* img = new QImage(path+ "wall.jpg");

//    QImage* img = new QImage("C:/Users/cong.tran/Documents/LearningOpenGL/test.png");
    // QImage use 32 bit. but glTexImage2D need 24 bit
    *img = img->convertToFormat(QImage::Format_RGBA8888, Qt::AutoColor);
    uchar* data = img->bits();
    if (data)
    {
        qDebug("width: %d, height: %d", img->width(),img->height());
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img->width(),img->height() , 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        qDebug("Failed to load texture");
    }

    // texture 2
//    unsigned int texture2;
    glGenTextures(1, &texture2);

    glBindTexture(GL_TEXTURE_2D, texture2); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object

    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

//    glBindTexture(GL_TEXTURE_2D, texture); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object

    QImage* img2 = new QImage(path+ "container.png");

//    QImage* img2 = new QImage("C:/Users/cong.tran/Documents/LearningOpenGL/test.png");
    // QImage use 32 bit. but glTexImage2D need 24 bit
    *img2 = img2->convertToFormat(QImage::Format_RGBA8888);
    uchar* data2 = img2->bits();
    if (data2)
    {
        qDebug("width: %d, height: %d", img2->width(),img2->height());
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img2->width(),img2->height() , 0, GL_RGBA, GL_UNSIGNED_BYTE, data2);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        qDebug("Failed to load texture");
    }

    //[1-2-3] init in ourShader
    QString sTmp = path + "7.3.camera.vs";
    QString sTmp2 = path + "7.3.camera.fs";
    ourShader = new Shader(sTmp.toLocal8Bit().data(), sTmp2.toLocal8Bit().data());

    // [4] Set Data to Array
    // get the attribute location with glGetAttribLocation
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // ===================== CameraDirection
    QVector3D cameraPos(0.0f, 0.0f, 3.0f);
    QVector3D cameraTarget(0.0f, 0.0f, 0.0f);

    QVector3D cameraDirection = cameraPos - cameraTarget;
    cameraDirection.normalize();

    // Right axis - x-axis
    QVector3D up(0.0f, 1.0f, 0.0f);
    QVector3D cameraRight ;//= glm::normalize(glm::cross(up, cameraDirection));
    cameraRight.crossProduct(up,cameraDirection).normalize();

    // Up axis - y-axis
    QVector3D cameraUp;
    cameraUp.crossProduct(cameraDirection, cameraRight).normalize();

//    cameraDirection = cameraDirection.normalized();

    // setup view
    ourShader->use();
//    QMatrix4x4 view;
    QMatrix4x4 projection;
//    view.translate(0.0f, 0.0f, -3.0f);
//    projection.ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 100.0f);
    projection.perspective(45.0f, width()/height(), 0.1f, 100.0f);
//    unsigned int viewLoc  = glGetUniformLocation(ourShader->ID, "viewTmp");
//    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, view.data());
    ourShader->setMat4("projection", projection.data());

//    QMatrix4x4 viewCamera;
//    viewCamera.lookAt(QVector3D(0.0f, 0.0f, 3.0f),
//                      QVector3D(0.0f, 0.0f, 0.0f),
//                      QVector3D(0.0f, 1.0f, 0.0f));

    // ===================== Load our shader
//    ourShader->use();
    ourShader->setInt("texture1", 0);
    ourShader->setInt("texture2", 1);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture2);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture);



    glViewport(0,0,width(),height());
    //
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
//    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    isOpenGLInited = true;

    delete img;
    delete img2;
}

void Camera::freePoint()
{

}

