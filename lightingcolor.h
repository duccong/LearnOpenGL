#ifndef LIGHTINGCOLOR_H
#define LIGHTINGCOLOR_H
#include <openglwindow.h>
#include <shader.h>

class LightingColor : public OpenGLWindow
{
    Q_OBJECT
public:
    LightingColor();

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
    unsigned int lightCubeVAO;

    GLuint shaderProgram;
    float tmp;
    bool tmp2;
    float fTmp2;
    bool isMousePress;

    bool isOpenGLInited;
//    Shader *ourShader;

    Shader* lightingShader;
    Shader* lightCubeShader;

    unsigned int uiTmp;
    unsigned int texture;
    unsigned int texture2;
    void freePoint();
    float cameraSpeed ;// = 2.5f * deltaTime;
    float yaw;
    float pitch;
    float tmpYaw;
    float tmpPitch;
    float lastX;
    float lastY;
    float sensitivity;
    float fov;

    QVector3D *cameraPos;
    QVector3D *cameraFront;
    QVector3D *cameraUp;
    QVector3D *cameraDirection;


public slots:
    void slotKeyPress(QKeyEvent *key);
    void slotMousePress(QEvent *event);

};
#endif // LIGHTINGCOLOR_H
