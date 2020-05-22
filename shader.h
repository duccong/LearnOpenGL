#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <QtGui/QOpenGLFunctions_3_3_Core>
#include <QVector3D>

class Shader : public QOpenGLFunctions_3_3_Core
{
public:
    // the program ID
    unsigned int ID;

    // constructor reads and builds the shader
    Shader(const char* vertexPath,const char* fragmentPath);
    // use/activate the shader
    void use();
    // utility uniform functions
    void setBool(const std::string &name, bool value);
    void setInt(const std::string &name, int value);
    void setFloat(const std::string &name, float value);
    void setUInt(const std::string &name, unsigned int value);
    void setVec2(const std::string &name, const GLfloat *value);
    void setVec2(const std::string &name, float x, float y) ;
    void setVec3(const std::string &name, const GLfloat *value) ;
    void setVec3(const std::string &name, const QVector3D value) ;
    void setVec3(const std::string &name, float x, float y, float z);
    void setVec4(const std::string &name, const GLfloat *value);
    void setVec4(const std::string &name, float x, float y, float z, float w);
    // ------------------------------------------------------------------------
    void setMat2(const std::string &name, const GLfloat *mat);
    // ------------------------------------------------------------------------
    void setMat3(const std::string &name, const GLfloat *mat);
    // ------------------------------------------------------------------------
    void setMat4(const std::string &name, const GLfloat *mat);
private:
    void checkCompileErrors(unsigned int shader, std::string type);
};

#endif
