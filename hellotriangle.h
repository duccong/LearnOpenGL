#ifndef HELLOTRIANGLE_H
#define HELLOTRIANGLE_H
#include <openglwindow.h>

class HelloTriangle : public OpenGLWindow
{
    Q_OBJECT
public:
    HelloTriangle();

    void initialize() override;
    void render() override;
    void initOpenGL();
signals:

public slots:

private:
    GLuint m_posAttr;
    GLuint m_colAttr;
    GLuint m_matrixUniform;

    GLuint VAO;

    GLuint shaderProgram;

    //    QOpenGLShaderProgram *m_program;
    //    int m_frame;
};

#endif // HELLOTRIANGLE_H
