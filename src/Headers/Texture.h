//
// Created by Caleb Rutledge on 1/3/24.
//

#ifndef OPENGL_TESTS_TEXTURE_H
#define OPENGL_TESTS_TEXTURE_H
#include "stb_image.h"
#include "glew.h"
#include <iostream>



class Texture {
    public:
    // the program ID
        unsigned int ID;
        int width, height, nrChannels;
    // constructor reads and builds the shader
        Texture();
        Texture(const char* texturePath);
        ~Texture();
    // use/activate the shader
        void use();
};


#endif //OPENGL_TESTS_TEXTURE_H
