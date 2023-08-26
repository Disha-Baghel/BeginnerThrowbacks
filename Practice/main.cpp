#include "Display/Display.h"
#include "Shader/Shader.h"
#include "Mesh/Mesh.h"
#include "Texture.h"
#include "Transform.h"
#include <GL/glew.h>
#include "Camera/Camera.h"

#define WIDTH 800
#define HEIGHT 500

int main(int argc,char* argv[])
{
   Display display(WIDTH,HEIGHT,"OpenGL");

   Shader shader("./res/Shaders/BasicShader");

   Vertex vertices[] = {
                        Vertex(glm::vec3( 1.0, 1.0,1.0) , glm::vec2(1,0)),
                        Vertex(glm::vec3(-1.0, 1.0,1.0) , glm::vec2(0,0)),
                        Vertex(glm::vec3(-1.0,-1.0,1.0) , glm::vec2(0,1)),

                        Vertex(glm::vec3( 1.0,-1.0,1.0) , glm::vec2(1,1)),
                        Vertex(glm::vec3( 1.0, 1.0,1.0) , glm::vec2(1,0)),
                        Vertex(glm::vec3(-1.0,-1.0,1.0) , glm::vec2(0,1)),

                        Vertex(glm::vec3(-1.0, 1.0, 1.0) , glm::vec2(1,0)),
                        Vertex(glm::vec3(-1.0, 1.0,-1.0) , glm::vec2(0,0)),
                        Vertex(glm::vec3(-1.0,-1.0,-1.0) , glm::vec2(0,1)),

                        Vertex(glm::vec3(-1.0,-1.0, 1.0) , glm::vec2(1,1)),
                        Vertex(glm::vec3(-1.0, 1.0, 1.0) , glm::vec2(1,0)),
                        Vertex(glm::vec3(-1.0,-1.0,-1.0) , glm::vec2(0,1)),

                        Vertex(glm::vec3(-1.0, 1.0,-1.0) , glm::vec2(1,0)),
                        Vertex(glm::vec3( 1.0, 1.0,-1.0) , glm::vec2(0,0)),
                        Vertex(glm::vec3( 1.0,-1.0,-1.0) , glm::vec2(0,1)),

                        Vertex(glm::vec3(-1.0, 1.0,-1.0) , glm::vec2(1,0)),
                        Vertex(glm::vec3( 1.0,-1.0,-1.0) , glm::vec2(0,1)),
                        Vertex(glm::vec3(-1.0,-1.0,-1.0) , glm::vec2(1,1)),

                        Vertex(glm::vec3( 1.0, 1.0,-1.0) , glm::vec2(1,0)),
                        Vertex(glm::vec3( 1.0, 1.0, 1.0) , glm::vec2(0,0)),
                        Vertex(glm::vec3( 1.0,-1.0, 1.0) , glm::vec2(0,1)),

                        Vertex(glm::vec3( 1.0, 1.0,-1.0) , glm::vec2(1,0)),
                        Vertex(glm::vec3( 1.0,-1.0, 1.0) , glm::vec2(0,1)),
                        Vertex(glm::vec3( 1.0,-1.0,-1.0) , glm::vec2(1,1)),

                        Vertex(glm::vec3( 1.0, 1.0,-1.0) , glm::vec2(1,0)),
                        Vertex(glm::vec3(-1.0, 1.0,-1.0) , glm::vec2(0,0)),
                        Vertex(glm::vec3(-1.0, 1.0, 1.0) , glm::vec2(0,1)),

                        Vertex(glm::vec3( 1.0, 1.0,-1.0) , glm::vec2(1,0)),
                        Vertex(glm::vec3(-1.0, 1.0, 1.0) , glm::vec2(0,1)),
                        Vertex(glm::vec3( 1.0, 1.0, 1.0) , glm::vec2(1,1)),

                        Vertex(glm::vec3(-1.0,-1.0,-1.0) , glm::vec2(1,0)),
                        Vertex(glm::vec3( 1.0,-1.0,-1.0) , glm::vec2(0,0)),
                        Vertex(glm::vec3( 1.0,-1.0, 1.0) , glm::vec2(0,1)),

                        Vertex(glm::vec3(-1.0,-1.0,-1.0) , glm::vec2(1,0)),
                        Vertex(glm::vec3( 1.0,-1.0, 1.0) , glm::vec2(0,1)),
                        Vertex(glm::vec3(-1.0,-1.0, 1.0) , glm::vec2(1,1)),
                        };

   Mesh mesh(vertices, sizeof(vertices)/sizeof(vertices[0]));

   Texture texture("./res/Images/grass.jpg");

   Camera camera(glm::vec3(0,3,3),45.0f,float(WIDTH)/float(HEIGHT),0.01,1000.0);

    Transform transform;
   float ang = 0;

   while(!display.IsClosed())
   {
       ang += 0.0;
       display.Clear(0.0f,0.15f,0.3f,1.0f);

       transform.GetRot().y = ang;

        shader.Bind();
        texture.Bind();
        shader.Update(transform,camera);
        mesh.Draw();

       camera.Update();
       display.Update();
   }

   return 0;
}
