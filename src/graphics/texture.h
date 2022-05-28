#ifndef TEXTURE_H
#define TEXTURE_H

struct Texture {
    unsigned int id;
    int width;
    int height;
    int usage_count;        // Number of entities using this model. Delete when 0
};

#endif