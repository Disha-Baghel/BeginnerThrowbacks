#include "Shader.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <glad/glad.h>

Shader::Shader(const char* const vertexPath, const char* const fragmentPath)
{
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vertexFile;
    std::ifstream fragmentFile;

    vertexFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fragmentFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try{
        std::stringstream vertexStream,fragmentStream;

        vertexFile.open(vertexPath);
        fragmentFile.open(fragmentPath);

        vertexStream << vertexFile.rdbuf();
        fragmentStream << fragmentFile.rdbuf();

        vertexCode = vertexStream.str();
        fragmentCode = fragmentStream.str();
    }
    catch(std::ifstream::failure e){
        std::cout << "ERROR::SHADER::FAILED_TO_READ\n" <<
                    e.what() << std::endl;
    }

    const char* const vertexShader = vertexCode.c_str();
    const char* const fragmentShader = fragmentCode.c_str();

    unsigned int vertex,fragment;
    int success;
    char infoLog[512];

    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex,1,&vertexShader,NULL);
    glCompileShader(vertex);

    glGetShaderiv(vertex,GL_COMPILE_STATUS,&success);
    if(!success){
        glGetShaderInfoLog(vertex,512,NULL,infoLog);
        std::cout << "ERROR::SHADER::VERTEX::FAILED_TO_COMPILE\n" <<
                    infoLog << std::endl;
    }

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment,1,&fragmentShader,NULL);
    glCompileShader(fragment);

    glGetShaderiv(fragment,GL_COMPILE_STATUS,&success);
    if(!success){
        glGetShaderInfoLog(fragment,512,NULL,infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::FAILED_TO_COMPILE\n" <<
                    infoLog << std::endl;
    }

    ID = glCreateProgram();
    glAttachShader(ID,vertex);
    glAttachShader(ID,fragment);
    glLinkProgram(ID);

    glGetProgramiv(ID,GL_LINK_STATUS,&success);
    if(!success){
        glGetProgramInfoLog(ID,512,NULL,infoLog);
        std::cout << "ERROR::SHADER::FAILED_TO_LINK_SHADERS\n" <<
                    infoLog << std::endl;
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void Shader::use()
{
    glUseProgram(ID);
}
