#include "object.h"

SDL_Renderer* object::renderer;
int object::width;
int object::height;
mat4x4 object::matProj;
vec3d object::vCamera;

int Get(std::string& str,const char ch)
{
    int pos = str.find('/');
    str = str.substr(0,pos);
    return atoi(str.c_str());
}

object::object(const char* const file)
{
    meshCube.LoadFromObjectFile(file);
}

void object::Set_Color(int r,int g,int b,float lum)
{
    SDL_SetRenderDrawColor(renderer,lum*r,lum*g,lum*b,255);
}

void object::XRotationMatrix()
{
    matRotX.m[0][0] = 1;
    matRotX.m[1][1] = SDL_cos(XTheta);
    matRotX.m[1][2] = SDL_sin(XTheta);
    matRotX.m[2][1] = -SDL_sin(XTheta);
    matRotX.m[2][2] = SDL_cos(XTheta);
    matRotX.m[3][3] = 1;
}

void object::YRotationMatrix()
{
    matRotY.m[0][0] = SDL_cos(YTheta);
    matRotY.m[0][2] = SDL_sin(YTheta);
    matRotY.m[1][1] = 1;
    matRotY.m[2][0] = -SDL_sin(YTheta);
    matRotY.m[2][2] = SDL_cos(YTheta);
    matRotY.m[3][3] = 1;
}

void object::ZRotationMatrix()
{
    matRotZ.m[0][0] = SDL_cos(ZTheta);
    matRotZ.m[0][1] = SDL_sin(ZTheta);
    matRotZ.m[1][0] = -SDL_sin(ZTheta);
    matRotZ.m[1][1] = SDL_cos(ZTheta);
    matRotZ.m[2][2] = 1;
    matRotZ.m[3][3] = 1;
}

void object::Rotate(char axis,float angle)
{
    switch(axis)
    {
        case 'X':
        case 'x': XTheta += angle;break;
        case 'Y':
        case 'y': YTheta += angle;break;
        case 'Z':
        case 'z': ZTheta += angle;break;
    }
}

void object::set_position(vec3d position)
{
    this->position = position;
}

void object::draw()
{
    XRotationMatrix();
    YRotationMatrix();
    ZRotationMatrix();

    for(auto tri: meshCube.tris)
    {
        triangle triProjected, triTranslated, triRotatedX, triRotatedXY, triRotatedXYZ;

        triRotatedX = tri * matRotX;             // Rotation in X
        triRotatedXY = triRotatedX * matRotY;    // Rotation in XY
        triRotatedXYZ = triRotatedXY * matRotZ;  // Rotation in XYZ

        triTranslated = triRotatedXYZ;

        triTranslated = triTranslated + position; //Shifting the triangle to the specified position

        vec3d line1 = triTranslated.p[1] - triTranslated.p[0];
        vec3d line2 = triTranslated.p[2] - triTranslated.p[0];
        vec3d normal = line1 * line2;

        float l = mag(normal);
        normal.x /= l; normal.y /= l; normal.z /= l;

        if(normal.x * (triTranslated.p[0].x - vCamera.x) +
           normal.y * (triTranslated.p[0].y - vCamera.y) +
           normal.z * (triTranslated.p[0].z - vCamera.z) < 0.0f)
        {
            vec3d light_direction = {0.0f,0.0f,-1.0f};
            float l = SDL_sqrt(light_direction.x*light_direction.x + light_direction.y*light_direction.y + light_direction.z*light_direction.z);
            light_direction.x /= l; light_direction.y /= l; light_direction.z /= l;
            float dp = normal.x * light_direction.x + normal.y * light_direction.y + normal.z * light_direction.z;

        triProjected = triTranslated * matProj;

        triProjected.p[0].x += 1.0f; triProjected.p[0].y += 1.0f;
        triProjected.p[1].x += 1.0f; triProjected.p[1].y += 1.0f;
        triProjected.p[2].x += 1.0f; triProjected.p[2].y += 1.0f;

        triProjected.p[0].x *= 0.5f * (float)width;
        triProjected.p[0].y *= 0.5f * (float)height;
        triProjected.p[1].x *= 0.5f * (float)width;
        triProjected.p[1].y *= 0.5f * (float)height;
        triProjected.p[2].x *= 0.5f * (float)width;
        triProjected.p[2].y *= 0.5f * (float)height;

        Set_Color(255,255,255,dp);

        FillTriangle(renderer,triProjected.p[0].x,triProjected.p[0].y,
                     triProjected.p[1].x,triProjected.p[1].y,
                     triProjected.p[2].x,triProjected.p[2].y);

        }
    }
}
