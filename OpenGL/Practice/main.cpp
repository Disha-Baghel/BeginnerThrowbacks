#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"
#include "bmp.h"

void frameBufferSize(GLFWwindow* window,int width,int height);
void processInput(GLFWwindow* window);
void mouse_callback(GLFWwindow* window,double xPos,double yPos);
void scroll_callback(GLFWwindow* window,double xOffset,double yOffset);

glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
glm::vec3 lightPos = glm::vec3(10.2f,10.0f,2.0f);

float yaw = -90.0f;
float pitch = 0.0f;
float Zoom = 45.0f;

float vertices[] = {
// positions // normals // texture coords
-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f,
0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
-0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,
-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
-0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
-0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
-0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
-0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
-0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,
0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
-0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,
-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
-0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f
};

int main(int argc,char* argv[])
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800,600,"OpenGL",NULL,NULL);
    glfwMakeContextCurrent(window);
    gladLoadGL();

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glfwSetInputMode(window,GLFW_CURSOR,GLFW_CURSOR_DISABLED);
    glfwSetFramebufferSizeCallback(window,frameBufferSize);
    glfwSetCursorPosCallback(window,mouse_callback);
    glfwSetScrollCallback(window,scroll_callback);

    GLuint vao;
    glGenVertexArrays(1,&vao);
    glBindVertexArray(vao);

    GLuint vbo;
    glGenBuffers(1,&vbo);
    glBindBuffer(GL_ARRAY_BUFFER,vbo);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);

    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    Shader shader("Shaders/vertex.vs","Shaders/fragment.fs");

    loadBMP("MY PHOTO.bmp");
    glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)(6*sizeof(float)));
    glEnableVertexAttribArray(2);

    GLuint lightVao;
    glGenVertexArrays(1,&lightVao);
    glBindVertexArray(lightVao);

    glBindBuffer(GL_ARRAY_BUFFER,vbo);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);

    Shader lightShader("Shaders/lightVertex.vs","Shaders/lightFragment.fs");

    float radius = sqrt(glm::dot(lightPos,lightPos));

    while(!glfwWindowShouldClose(window)){
        processInput(window);

        lightPos.x = sin(glfwGetTime()*0.5) * radius;
        lightPos.y = cos(glfwGetTime()*0.5) * radius;

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::scale(model,glm::vec3(10));

        glm::mat4 view = glm::mat4(1.0f);
        view = glm::lookAt(cameraPos,cameraPos + cameraFront, cameraUp);

        float fov = Zoom;
        glm::mat4 projection = glm::mat4(1.0f);
        projection = glm::perspective(glm::radians(fov),800.0f/600.0f,0.1f,100.0f);

        glClearColor(0.3,0.2,0.4,1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.use();
        GLuint modelLoc = glGetUniformLocation(shader.getID(),"model");
        glUniformMatrix4fv(modelLoc,1,GL_FALSE,glm::value_ptr(model));
        GLuint viewLoc = glGetUniformLocation(shader.getID(),"view");
        glUniformMatrix4fv(viewLoc,1,GL_FALSE,glm::value_ptr(view));
        GLuint projectionLoc = glGetUniformLocation(shader.getID(),"projection");
        glUniformMatrix4fv(projectionLoc,1,GL_FALSE,glm::value_ptr(projection));

        GLuint lightColorLoc = glGetUniformLocation(shader.getID(),"lightColor");
        glUniform3f(lightColorLoc,0.3f,1.0f,1.0f);

        GLuint lightPosLoc = glGetUniformLocation(shader.getID(),"lightPos");
        glUniform3f(lightPosLoc,lightPos.x,lightPos.y,lightPos.z);

        GLuint cameraPosLoc = glGetUniformLocation(shader.getID(),"cameraPos");
        glUniform3f(cameraPosLoc,cameraPos.x,cameraPos.y,cameraPos.z);

        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES,0,36);

        lightShader.use();

        model = glm::mat4(1.0f);
        model = glm::translate(model,lightPos);
        model = glm::scale(model,glm::vec3(0.2f));

        modelLoc = glGetUniformLocation(lightShader.getID(),"model");
        glUniformMatrix4fv(modelLoc,1,GL_FALSE,glm::value_ptr(model));
        viewLoc = glGetUniformLocation(lightShader.getID(),"view");
        glUniformMatrix4fv(viewLoc,1,GL_FALSE,glm::value_ptr(view));
        projectionLoc = glGetUniformLocation(lightShader.getID(),"projection");
        glUniformMatrix4fv(projectionLoc,1,GL_FALSE,glm::value_ptr(projection));

        lightColorLoc = glGetUniformLocation(lightShader.getID(),"lightColor");
        glUniform3f(lightColorLoc,0.3f,1.0f,1.0f);

        glBindVertexArray(lightVao);
        glDrawArrays(GL_TRIANGLES,0,36);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void frameBufferSize(GLFWwindow* window,int width,int height)
{
    glViewport(0,0,width,height);
}

float deltaTime = 0.0f;
float lastFrame = 0.0f;

void processInput(GLFWwindow* window){
    if(glfwGetKey(window,GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(window,GL_TRUE);
    }

    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    const float cameraSpeed = 2.5f * deltaTime;
    if(glfwGetKey(window,GLFW_KEY_W) == GLFW_PRESS){
        cameraPos += cameraSpeed * cameraFront;
    }
    if(glfwGetKey(window,GLFW_KEY_S) == GLFW_PRESS){
        cameraPos -= cameraSpeed * cameraFront;
    }
    if(glfwGetKey(window,GLFW_KEY_A) == GLFW_PRESS){
        cameraPos -= glm::normalize(glm::cross(cameraFront,cameraUp)) * cameraSpeed;
    }
    if(glfwGetKey(window,GLFW_KEY_D) == GLFW_PRESS){
        cameraPos += glm::normalize(glm::cross(cameraFront,cameraUp)) * cameraSpeed;
    }
    if(glfwGetKey(window,GLFW_KEY_SPACE) == GLFW_PRESS){
        cameraPos += cameraSpeed * cameraUp;
    }
}

float lastX = 400;
float lastY = 300;

void mouse_callback(GLFWwindow* window,double xPos,double yPos)
{
    static bool firstTime = true;

    if(firstTime){
        lastX = xPos;
        lastY = yPos;
        firstTime = false;
    }

    float xOffset = xPos - lastX;
    float yOffset = lastY - yPos;
    lastX = xPos;
    lastY = yPos;

    static const float sensitivity = 0.1f;
    xOffset *= sensitivity;
    yOffset *= sensitivity;

    yaw += xOffset;
    pitch += yOffset;

    if(pitch > 89.0f)
        pitch = 89.9f;
    if(pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw));

    cameraFront = glm::normalize(direction);
}

void scroll_callback(GLFWwindow* window,double xOffset,double yOffset)
{
    Zoom -= (float)yOffset;
    if(Zoom < 1.0f)
        Zoom = 1.0f;
    if(Zoom > 45.0f)
        Zoom = 45.0f;
}
