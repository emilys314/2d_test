#ifndef TEXTURE_H
#define TEXTURE_H

class Texture{
private:
    unsigned int id;
    int width;
    int height;

public:
    Texture(unsigned int id, int width, int height) {
        this->id = id;
        this->width = width;
        this->height = height;
    }

    unsigned int getId() {
        return id;
    }

    int getWidth() {
        return width;
    }

    int getHeight() {
        return height;
    }
};

#endif