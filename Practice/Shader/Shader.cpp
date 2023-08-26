#include "Shader.h"
#include <GL/glew.h>
#include <fstream>
#include <sstream>
#include <iostream>

static void CheckShaderError(GLuint shader, GLuint flag, bool isPrgram, const std::string &errorMessage);
static std::string LoadShader(const std::string &FilePath);
static GLuint CreateShader(const std::string& text, GLenum shaderType);

Shader::Shader(const std::string &FilePath)
{
    m_program = glCreateProgram();
    m_shader[0] = CreateShader(LoadShader(FilePath + ".vs"), GL_VERTEX_SHADER);
    m_shader[1] = CreateShader(LoadShader(FilePath + ".fs"), GL_FRAGMENT_SHADER);

    for(unsigned int i=0;i<NUM_SHADERS;i++)
        glAttachShader(m_program,m_shader[i]);

    glLinkProgram(m_program);
    CheckShaderError(m_program, GL_LINK_STATUS, true, "Sorry, I couldn't link the program. You might need to recheck your shaders.");

    glValidateProgram(m_program);
    CheckShaderError(m_program, GL_VALIDATE_STATUS, true, "Umm, I think the program is invalid. Recheck your shaders.");

    m_uniform[MODEL_U] = glGetUniformLocation(m_program, "Model");
    m_uniform[VIEW_U] = glGetUniformLocation(m_program, "View");
    m_uniform[PROJ_U] = glGetUniformLocation(m_program, "Projection");
}

Shader::~Shader()
{
    for(unsigned int i=0; i<NUM_SHADERS; i++)
    {
        glDetachShader(m_program,m_shader[i]);
        glDeleteShader(m_shader[i]);
    }

    glDeleteProgram(m_program);
}

void Shader::Bind()
{
    glUseProgram(m_program);
}

void Shader::Update(const Transform& transform, const Camera& camera)
{
    glm::mat4 model = transform.GetModel();
    glm::mat4 view = camera.GetView();
    glm::mat4 projection = camera.GetProjection();

    glUniformMatrix4fv(m_uniform[MODEL_U], 1, GL_FALSE, &model[0][0]);
    glUniformMatrix4fv(m_uniform[VIEW_U], 1, GL_FALSE, &view[0][0]);
    glUniformMatrix4fv(m_uniform[PROJ_U], 1, GL_FALSE, &projection[0][0]);
}

static GLuint CreateShader(const std::string& text, GLenum shaderType)
{
    GLuint shader = glCreateShader(shaderType);

    if(shader == 0)
    {
        std::cerr << "Error: Shader creation failed." << std::endl;
        exit(0);
    }

    const GLchar* const shaderCode = text.c_str();

    glShaderSource(shader,1,&shaderCode,NULL);
    glCompileShader(shader);

    std::string shaderName;

    switch(shaderType)
    {
        case GL_VERTEX_SHADER: shaderName = "Vertex"; break;
        case GL_FRAGMENT_SHADER: shaderName = "Fragment"; break;
        case GL_GEOMETRY_SHADER: shaderName = "Geometry"; break;
        default:
            break;
    }

    CheckShaderError(shader,GL_COMPILE_STATUS,false,"Oh boy! Seems like your " + shaderName + " Shader is not written well.");

    return shader;
}

static std::string LoadShader(const std::string &FilePath)
{
    std::ifstream file;
    file.open(FilePath);

    if(!file)
    {
        std::cerr << "Error: " << FilePath << " does not exist.\n";
        exit(0);
    }

    std::stringstream shaderCode;

    shaderCode << file.rdbuf();

    file.close();

    return shaderCode.str();
}

static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage)
{
    GLint success = 0;
    GLchar error[1024] = {};

    if(isProgram)
        glGetProgramiv(shader, flag, &success);
    else
        glGetShaderiv(shader, flag, &success);

    if(!success)
    {
        if(isProgram)
            glGetProgramInfoLog(shader, sizeof(error),NULL,error);
        else
            glGetShaderInfoLog(shader, sizeof(error), NULL, error);

        std::cerr << errorMessage << "\n" << error << std::endl;
        exit(0);
    }
}
