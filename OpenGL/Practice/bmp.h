#ifndef BMP_H
#define BMP_H

#include <fstream>
#include <iostream>

GLuint loadBMP(const char* const imagePath)
{
    unsigned char header[54];
    unsigned char dataPos;
    unsigned int width,height;
    unsigned int imageSize;

    unsigned char* data;

    std::ifstream img(imagePath,std::ios::binary);
    if(!img){
        std::cout << "ERROR::IMAGE::FAILED_TO_OPEN\n";
        return 0;
    }

    img.read((char*)header,54);

    if(header[0] != 'B' || header[1]!='M'){
        std::cout << "ERROR::IMAGE::NOT_A_BMP_IMAGE\n";
        return 0;
    }

    dataPos = *(int*)&(header[0x0A]);
    imageSize = *(int*)&(header[0x22]);
    width = *(int*)&(header[0x12]);
    height = *(int*)&(header[0x16]);

    if(imageSize==0) imageSize = width*height*3;
    if(dataPos==0) dataPos = 54;

    data = new unsigned char [imageSize];

    img.read((char*)data,imageSize);

    img.close();

    GLuint textureID;
    glGenTextures(1,&textureID);
    glBindTexture(GL_TEXTURE_2D,textureID);

    glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,width,height,0,GL_BGR,GL_UNSIGNED_BYTE,data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glGenerateMipmap(GL_TEXTURE0);

    return textureID;
}


#endif // BMP_H
