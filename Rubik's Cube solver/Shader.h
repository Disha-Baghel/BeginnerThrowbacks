#ifndef SHADER_H
#define SHADER_H

#include <string>
#include "Transform.h"
#include "Camera.h"

class Shader
{
public:
    Shader(const std::string& ShaderSource);
    ~Shader();

    void Use();

    void Update(const Transform& transform, const Camera& camera);
private:

    std::string LoadShader(const std::string& ShaderSource);

    unsigned int CreateShader(const std::string& ShaderCode, const unsigned int& ShaderType);

    void CheckError(const unsigned int& ShaderProgram, const bool& isProgram,const unsigned int& flag, const std::string& ErrorMsg);

private:

    enum{
        Vertex,
        Fragment,

        NumShader
    };

    enum{
        Model_U,
        View_U,
        Proj_U,

        NumUniform
    };

    unsigned int m_Program;
    unsigned int m_Shader[NumShader];
    unsigned int m_Uniform[NumUniform];
};

#endif // SHADER_H
