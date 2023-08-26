#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <Transform.h>
#include <Camera.h>

class Shader
{
public:
    Shader(const std::string &FilePath);
    ~Shader();
    void Bind();
    void Update(const Transform& transform, const Camera& camera);
private:
    enum
    {
        MODEL_U,
        VIEW_U,
        PROJ_U,

        NUM_U
    };

    static const unsigned int NUM_SHADERS = 2;
    unsigned int m_program;
    unsigned int m_shader[NUM_SHADERS];
    unsigned int m_uniform[NUM_U];
};

#endif // SHADER_H
