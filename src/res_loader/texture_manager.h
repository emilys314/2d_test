#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <unordered_map>
#include <iostream>

#include <glad/glad.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "../graphics/texture.h"

class Texture_Manager {
    std::unordered_map<std::string, Texture> textures = {};

    Texture load_texture(char const* filename) {
        unsigned int id;
        glGenTextures(1, &id);
        glBindTexture(GL_TEXTURE_2D, id); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
        // set the texture wrapping parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // set texture wrapping to GL_REPEAT (default wrapping method)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        // set texture filtering parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        // load image, create texture and generate mipmaps
        int width, height, nrChannels;
        // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
        unsigned char* data = stbi_load(filename, &width, &height, &nrChannels, 0);
        if (data) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else {
            std::cout << "Failed to load texture | " << filename << std::endl;
        }
        stbi_image_free(data);

        Texture texture = {id, width, height};

        return texture;
    }

public:
    Texture_Manager() {

    }

    Texture get(char const* filename) {
        try {
            Texture texture = textures.at(filename);
            return texture;
        } catch (const std::out_of_range& e) {
            std::cout << "Creating new Texture from " << filename << "\n";
            Texture texture = this->load_texture(filename);
            textures[filename] = texture;
            return texture;
        }
    }
};

#endif