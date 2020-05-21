#include "cameraobject.h"

CameraObject::CameraObject()
{

}
// constructor with vectors

CameraObject::CameraObject(QVector3D position = QVector3D(0.0f, 0.0f, 0.0f), QVector3D up = QVector3D(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH) : Front(QVector3D(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
{
    Position = position;
    WorldUp = up;
    Yaw = yaw;
    Pitch = pitch;
    updateCameraVectors();
}
// constructor with scalar values
CameraObject::CameraObject(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : Front(QVector3D(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
{
    Position = QVector3D(posX, posY, posZ);
    WorldUp = QVector3D(upX, upY, upZ);
    Yaw = yaw;
    Pitch = pitch;
    updateCameraVectors();
}

QMatrix4x4 CameraObject::GetViewMatrix()
{
    // matrix
    QMatrix4x4 view;
    view.lookAt(Position, Position + Front, Up);
    return view;
}

void CameraObject::updateCameraVectors()
{
    // calculate the new Front vector
    QVector3D front;
    front.setX( qCos(qRadiansToDegrees(Yaw)) * qCos(qRadiansToDegrees(Pitch)));
    front.setY( qSin(qRadiansToDegrees(Pitch)));
    front.setZ( qSin(qRadiansToDegrees(Yaw)) * qCos(qRadiansToDegrees(Pitch)));
    front.normalize();
    // also re-calculate the Right and Up vector
    Right.crossProduct(Front, WorldUp).normalize();  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    Up.crossProduct(Right, Front).normalize();
}

//    // processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
//    void ProcessKeyboard(Camera_Movement direction, float deltaTime)
//    {
//        float velocity = MovementSpeed * deltaTime;
//        if (direction == FORWARD)
//            Position += Front * velocity;
//        if (direction == BACKWARD)
//            Position -= Front * velocity;
//        if (direction == LEFT)
//            Position -= Right * velocity;
//        if (direction == RIGHT)
//            Position += Right * velocity;
//    }

//    // processes input received from a mouse input system. Expects the offset value in both the x and y direction.
//    void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true)
//    {
//        xoffset *= MouseSensitivity;
//        yoffset *= MouseSensitivity;

//        Yaw   += xoffset;
//        Pitch += yoffset;

//        // make sure that when pitch is out of bounds, screen doesn't get flipped
//        if (constrainPitch)
//        {
//            if (Pitch > 89.0f)
//                Pitch = 89.0f;
//            if (Pitch < -89.0f)
//                Pitch = -89.0f;
//        }

//        // update Front, Right and Up Vectors using the updated Euler angles
//        updateCameraVectors();
//    }

//    // processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
//    void ProcessMouseScroll(float yoffset)
//    {
//        Zoom -= (float)yoffset;
//        if (Zoom < 1.0f)
//            Zoom = 1.0f;
//        if (Zoom > 45.0f)
//            Zoom = 45.0f;
//    }


