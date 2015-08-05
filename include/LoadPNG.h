#ifndef LOAD_PNG_H
#define LOAD_PNG_H

struct image {
    short width = 0;
    short height = 0;
    int size = 0;
    byte *data;
};

image loadPNG(char *name);

#endif

