#include "hellotriangle.h"

HelloTriangle::HelloTriangle()
{
    isOpenGLInited = false;
    tmp = 0.0;
    tmp2 = false;
    setAnimating(true);
}

void HelloTriangle::initialize()
{
    qDebug("HelloTriangle::initialize()");


    initOpenGL();
}

void HelloTriangle::render()
{

//    qDebug("HelloTriangle::render()");
//    m_context->makeCurrent(this);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

//    glUseProgram(shaderProgram);
    ourShader->use();
    // update the uniform color
//    float timeValue = glTim();

    if (tmp2){
        tmp = tmp - 0.01;
        if (tmp <= 0){
            tmp2 = false;
        }
    } else {
        tmp = tmp + 0.01;
        if (tmp >= 1.0){
            tmp2 = true;
        }
    }
//    glUniform4f(glGetUniformLocation(shaderProgram, "oColor"), 1-tmp, tmp, 1-tmp/2, 1.0f);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

}

void HelloTriangle::initOpenGL()
{
    if (isOpenGLInited){
        return;
    }
//    m_context->makeCurrent(this);
    qDebug("HelloTriangle::initOpenGL()");

    int nrAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
    qDebug("Maximum nr of vertex attributes supported: %d", nrAttributes);

    float vertices[] = {
//        0.5f,  0.5f, 0.0f,  // top right
//        0.5f, -0.5f, 0.0f,  // bottom right
//        -0.5f, -0.5f, 0.0f,  // bottom left
//        -0.5f,  0.5f, 0.0f   // top left
        0.0f ,0.7f, 0.0f,        1.0f, 0.0f, 0.0f,
        -0.25f, -0.25f, 0.0f,    0.0f, 0.0f, 1.0f,
        0.25f, -0.25f, 0.0f,     0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f,        0.5f, 0.5f, 0.5f,

    };

    unsigned int indices[] = {  // note that we start from 0!
        0, 2, 6,   // first triangle
        0, 4, 6    // second triangle
    };

    float texCoords[] = {
        0.0f, 0.0f,  // lower-left corner
        1.0f, 0.0f,  // lower-right corner
        0.5f, 1.0f   // top-center corner
    };

    const char *vertexShaderSource = "#version 330 core\n"
                                     "layout (location = 0) in vec3 aPos;\n"
//                                     "uniform vec4 ourColor;\n"
//                                     "out vec3 oColor;\n"
                                     "void main()\n"
                                     "{\n"
                                     "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
//                                     "   oColor = iColor;\n"
                                     "}\0";

    const char *fragmentShaderSource = "#version 330 core\n"
                                       "uniform vec4 oColor;\n"
                                       "out vec4 FragColor;\n"
                                       "void main()\n"
                                       "{\n"
                                       "   FragColor = oColor;\n"
                                       "}\n\0";

    int  success;
    char infoLog[512];


    //[0] VAO, VBO, EBO

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

    //[1-2-3] init in ourShader
    ourShader = new Shader("C:/Users/cong.tran/Documents/LearningOpenGL/3.3.shader.vs", "C:/Users/cong.tran/Documents/LearningOpenGL/3.3.shader.fs");

    // [4] Set Data to Array
    // get the attribute location with glGetAttribLocation
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

//    glBindBuffer(GL_ARRAY_BUFFER, 0);
//    glBindVertexArray(0);

//    glUseProgram(shaderProgram);
    glViewport(0,0,width(),height());

//    glDeleteShader(vertexShader);
//    glDeleteShader(fragmentShader);

    //
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
//    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    isOpenGLInited = true;
}
