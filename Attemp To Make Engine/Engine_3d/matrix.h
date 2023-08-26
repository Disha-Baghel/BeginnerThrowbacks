
struct vec3d{
    float x,y,z;
};

struct triangle{
    vec3d p[3];
};

struct mat4x4{
    float m[4][4] = {{0}};
};

vec3d operator*(vec3d &v,const mat4x4 &m);
triangle operator*(triangle &tri,const mat4x4 &m);
triangle operator+(triangle &tri,const vec3d &v);
vec3d operator+(vec3d &v1,const vec3d &v2);
vec3d operator*(vec3d &v1,vec3d &v2);
vec3d operator-(vec3d &v1,vec3d &v2);
float mag(vec3d v);
