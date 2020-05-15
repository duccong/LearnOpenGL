#ifndef CAMERA_H
#define CAMERA_H
#include <openglwindow.h>
#include <shader.h>

class Camera: public OpenGLWindow
{
    Q_OBJECT
public:
    Camera();

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

//    QVector3D cameraPos;
//    QVector3D cameraTarget;
//    QVector3D cameraDirection;
//    QVector3D up;
//    // cameraRight - x-axis
//    QVector3D cameraRight ;
//    // cameraUp - y-axis
//    QVector3D cameraUp;

    //    QOpenGLShaderProgram *m_program;
    //    int m_frame;
};

#endif // CAMERA_H
