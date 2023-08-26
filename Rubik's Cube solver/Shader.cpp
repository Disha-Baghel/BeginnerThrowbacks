#include "Shader.h"
#include <GL/glew.h>
#include <iostream>
#include <fstream>
#include <sstream>

Shader::Shader(const std::string& ShaderSource)
{
    m_Program = glCreateProgram();

    m_Shader[Vertex] = CreateShader( LoadShader(ShaderSource + ".vs"), GL_VERTEX_SHADER );
    m_Shader[Fragment] = CreateShader( LoadShader(ShaderSource + ".fs"), GL_FRAGMENT_SHADER);

    for(unsigned int i=0; i<NumShader; i++)
        glAttachShader(m_Program, m_Shader[i]);

    glLinkProgram(m_Program);

    CheckError(m_Program, true, GL_LINK_STATUS, "Failed to link program");

    m_Uniform[Model_U] = glGetUniformLocation(m_Program, "Model");
    m_Uniform[View_U] = glGetUniformLocation(m_Program, "View");
    m_Uniform[Proj_U] = glGetUniformLocation(m_Program, "Projection");
}

Shader::~Shader()
{
    for(unsigned int i=0; i<NumShader; i++)
    {
        glDetachShader(m_Program, m_Shader[i]);
        glDeleteShader(m_Shader[i]);
    }

    glDeleteProgram(m_Program);
}

void Shader::Use()
{
    glUseProgram(m_Program);
}

void Shader::Update(const Transform& transform, const Camera& camera)
{
    glm::mat4 Model = transform.GetModel();
    glm::mat4 View = camera.GetView();
    glm::mat4 Proj = camera.GetProjection();

    glUniformMatrix4fv(m_Uniform[Model_U], 1, false, &Model[0][0]);
    glUniformMatrix4fv(m_Uniform[View_U], 1, false, &View[0][0]);
    glUniformMatrix4fv(m_Uniform[Proj_U], 1, false, &Proj[0][0]);
}

std::string Shader::LoadShader(const std::string& ShaderSource)
{
    std::ifstream file(ShaderSource);

    if(!file)
    {
        std::cout << "Failed to open " << ShaderSource << std::endl;
        exit(0);
    }

    std::stringstream ShaderCode;

    ShaderCode << file.rdbuf();

    file.close();

    return ShaderCode.str();
}

unsigned int Shader::CreateShader(const std::string& ShaderCode, const unsigned int& ShaderType)
{
    unsigned int ShaderProgram = glCreateShader(ShaderType);

    if(ShaderProgram == 0)
    {
        std::cerr << "Failed to create Shader" << std::endl;
        exit(0);
    }

    const GLchar* const Code = ShaderCode.c_str();

    glShaderSource(ShaderProgram, 1, &Code, NULL);
    glCompileShader(ShaderProgram);

    std::string ShaderName;

    switch(ShaderType)
    {
        case GL_VERTEX_SHADER: ShaderName = "Vertex"; break;
        case GL_FRAGMENT_SHADER: ShaderName = "Fragment"; break;
    }

    CheckError(ShaderProgram, false, GL_COMPILE_STATUS, "Error in " + ShaderName);

    return ShaderProgram;
}

void Shader::CheckError(const unsigned int& ShaderProgram, const bool& isProgram,const unsigned int& flag, const std::string& ErrorMsg)
{
    int success;
    char buffer[512];

    if(isProgram)
        glGetProgramiv(ShaderProgram, flag, &success);
    else
        glGetShaderiv(ShaderProgram, flag, &success);

    if(!success)
    {
        if(isProgram)
            glGetProgramInfoLog(ShaderProgram, sizeof(buffer), NULL, buffer);
        else
            glGetShaderInfoLog(ShaderProgram, sizeof(buffer), NULL, buffer);

        std::cerr << ErrorMsg << std::endl << buffer << std::endl;
        exit(0);
    }
}
