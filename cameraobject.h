#ifndef CAMERAOBJECT_H
#define CAMERAOBJECT_H
#include <QVector3D>
#include <qmath.h>

// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

// Default camera values
const float YAW         = -90.0f;
const float PITCH       =  0.0f;
const float SPEED       =  2.5f;
const float SENSITIVITY =  0.1f;
const float ZOOM        =  45.0f;

class CameraObject
{
public:
    CameraObject();
    CameraObject(QVector3D position,QVector3D up , float yaw , float pitch );
    CameraObject(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);

    // camera Attributes
    QVector3D Position;
    QVector3D Front;
    QVector3D Up;
    QVector3D Right;
    QVector3D WorldUp;
    // euler Angles
    float Yaw;
    float Pitch;
    // camera options
    float MovementSpeed;
    float MouseSensitivity;
    float Zoom;

    QVector4D GetViewMatrix();
private:
     void updateCameraVectors();
};

#endif // CAMERAOBJECT_H
