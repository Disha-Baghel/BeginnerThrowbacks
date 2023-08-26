#ifndef TEXTURE_H
#define TEXTURE_H


class Texture
{
    public:
        Texture(const char* const &ImagePath);

        void Bind(unsigned int unit = 0);

        virtual ~Texture();
    protected:

    private:

        unsigned int m_Texture;
};

#endif // TEXTURE_H
