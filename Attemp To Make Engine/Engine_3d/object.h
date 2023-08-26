#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include "matrix.h"
#include "Triangle.h"

int Get(std::string& str,const char ch);

struct mesh{
    std::vector<triangle> tris;

    bool LoadFromObjectFile(const char* Filename)
    {
        std::ifstream f(Filename);
        if(!f.is_open())
            return false;

        std::vector<vec3d> verts;

        while(!f.eof())
        {
            char line[128];
            f.getline(line,128);

            std::stringstream s;
            s<<line;

            char junk;

            if(line[0] == 'v' && line[1] == ' ')
            {
                vec3d v;
                s >> junk >> v.x >> v.y >> v.z;
                verts.push_back(v);
            }

            if(line[0] == 'f')
            {
                std::string str[4];
                int f[4];
                str[3] = "not this";
                s >> junk >> str[0] >> str[1] >> str[2] >> str[3];
                for(int i=0;i<4;i++)
                    f[i] = Get(str[i],'/');
                tris.push_back({verts[f[0] - 1], verts[f[1] - 1], verts[f[2] - 1] });
                if(str[3] != "not this")
                    tris.push_back({verts[f[0] - 1], verts[f[2] - 1], verts[f[3] - 1] });
            }
        }
        return true;
    }
};

class object
{
    mesh meshCube;
    mat4x4 matRotX,matRotY,matRotZ;
    void XRotationMatrix();
    void YRotationMatrix();
    void ZRotationMatrix();
    float XTheta = 0.0f,YTheta = 0.0f,ZTheta = 0.0f;
    vec3d position;
public:
    object(const char* const file);
    void draw();
    void Set_Color(int r,int g,int b,float lum);
    void Rotate(char axis,float angle);
    static SDL_Renderer* renderer;
    static int width,height;
    static mat4x4 matProj;
    static vec3d vCamera;
    void set_position(vec3d position);
};
