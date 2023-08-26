#ifndef SHADER_H
#define SHADER_H


class Shader
{
    public:
        Shader(const char* const vertexPath,const char* const fragmentPath);
        void use();
        unsigned int getID() { return ID;}

    private:
        unsigned int ID;
};

#endif // SHADER_H
