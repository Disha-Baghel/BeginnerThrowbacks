#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <math.h>
#include "Shader.h"

void framebuffer_size_callback(GLFWwindow* window,int width,int heght);
void processInput(GLFWwindow* window);

float vertices[] = {
0.5f, 0.5f, 0.0f, // top right
0.5f, -0.5f, 0.0f, // bottom right
-0.5f, -0.5f, 0.0f, // bottom left
-0.5f, 0.5f, 0.0f // top left
};
unsigned int indices[] = { // note that we start from 0!
0, 1, 3, // first triangle
1, 2, 3 // second triangle
};


unsigned int makeBuffer(GLenum Target,GLsizei BufferSize,const void* BufferData,GLenum Usage){
    unsigned int buffer;
    glGenBuffers(1,&buffer);
    glBindBuffer(Target,buffer);
    glBufferData(Target,BufferSize,BufferData,Usage);
    return buffer;
}

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800,600,"OpenGL",NULL,NULL);
    glfwMakeContextCurrent(window);
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        return -1;
    }

    glViewport(0,0,800,600);

    glfwSetFramebufferSizeCallback(window,framebuffer_size_callback);

    unsigned int vao;
    glGenVertexArrays(1,&vao);
    glBindVertexArray(vao);

    unsigned int vbo = makeBuffer(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
    unsigned int ebo = makeBuffer(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);

    Shader shader("Shaders/shader.vs","Shaders/shader.fs");

    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);

    while(!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.2f,0.3f,0.3f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.use();
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ebo);
        glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window,int width,int heght)
{
    glViewport(0,0,800,600);
}

void processInput(GLFWwindow* window)
{
    if(glfwGetKey(window,GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window,GL_TRUE);
}
