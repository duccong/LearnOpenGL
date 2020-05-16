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
    float fTmp2;
    bool isOpenGLInited;
    Shader *ourShader;
    unsigned int uiTmp;
    unsigned int texture;
    unsigned int texture2;
    void freePoint();
    float cameraSpeed ;// = 2.5f * deltaTime;

    QVector3D *cameraPos;
    QVector3D *cameraFront;
    QVector3D *cameraUp;


public slots:
    void slotKeyPress(QKeyEvent *key);

};

#endif // CAMERA_H
