#ifndef COORDINATESYSTEMS_H
#define COORDINATESYSTEMS_H
#include <openglwindow.h>
#include <shader.h>

class CoordinateSystems: public OpenGLWindow
{
    Q_OBJECT
public:
    CoordinateSystems();

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
    float tmp;
    bool tmp2;
    bool isOpenGLInited;
    Shader *ourShader;
    unsigned int uiTmp;
    unsigned int texture;
    unsigned int texture2;
    void freePoint();

    //    QOpenGLShaderProgram *m_program;
    //    int m_frame;
};

#endif // COORDINATESYSTEMS_H
