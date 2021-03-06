#include "transform.h"

transform::transform()
{
    isOpenGLInited = false;
    tmp = 0.0;
    tmp2 = false;
//    setAnimating(false);
    setAnimating(true);
}

void transform::initialize()
{
    qDebug("HelloTriangle::initialize()");


    initOpenGL();
}

void transform::render()
{

//    qDebug("HelloTriangle::render()");
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT  | GL_DEPTH_BUFFER_BIT  );

//    ourShader->use();

    if (tmp2){
        tmp = tmp - 0.01;
        if (tmp <= -1){
            tmp2 = false;
        }
    } else {
        tmp = tmp + 0.01;
        if (tmp >= 1.0){
            tmp2 = true;
        }
    }
//    tmp++;

    QMatrix4x4 matrix;

//    matrix.perspective(60.0f, 4.0f/3.0f, 0.1f, 100.0f);
    matrix.translate(tmp, 0 , 0);
//    matrix.translate(0, tmp, 0);
//    matrix.rotate(100.0f * tmp / screen()->refreshRate(), 1, 1, 1);
//    matrix.rotate(180, 0, 0,1);
//    ourShader->setMat4("transform",matrix.data());

//    float test[] = {
//        1, 0, 0, 0,
//        0, 1, 0, 1,
//        0, 0, 1, 0,
//        0, 0, 0, 1
//    };

//    QMatrix4x4 mat4(test);
//    qDebug() << matrix << endl;
//    qDebug() << mat4 << endl;

    ourShader->setMat4("transform",matrix.data());

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void transform::initOpenGL()
{
    if (isOpenGLInited){
        return;
    }
//    m_context->makeCurrent(this);
    qDebug("HelloTriangle::initOpenGL()");

    int nrAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
    qDebug("Maximum nr of vertex attributes supported: %d", nrAttributes);

//    };
    float vertices[] = {
            // positions          // colors           // texture coords
             0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
             0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
            -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
            -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f,  // top left
             0.25f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right2
        };

    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    };

    float texCoords[] = {
        0.0f, 0.0f,  // lower-left corner
        1.0f, 0.0f,  // lower-right corner
        0.5f, 1.0f   // top-center corner
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

    QImage* img2 = new QImage(path+ "test2.png");

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
    QString sTmp = path + "5.1.transform.vs";
    QString sTmp2 = path + "5.1.transform.fs";
    ourShader = new Shader(sTmp.toLocal8Bit().data(), sTmp2.toLocal8Bit().data());

    // [4] Set Data to Array
    // get the attribute location with glGetAttribLocation
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // Load texture
    ourShader->use();
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

void transform::freePoint()
{

}


