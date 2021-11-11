#include "../utils/DrawableObjectInrerface.h"

#ifndef OPENGLSETUPFROMGLFW_CUBE_H
#define OPENGLSETUPFROMGLFW_CUBE_H


class Cube:IDrawableObject {
    vertices = {
            -0.5, -0.5, 0.5, // 0
            0.5, -0.5, 0.5, // 1
            0.5, 0.5, 0.5, // 2
            -0.5, 0.5, 0.5, // 3
            -0.5, -0.5, -0.5, // 4
            0.5, -0.5, -0.5, // 5
            0.5, 0.5, -0.5, // 6
            -0.5, 0.5, -0.5 // 7
    };

    indices = {
            // front
            0, 1, 2,
            0, 2, 3,
            // right
            1, 5, 6,
            1, 2, 6,
            // left
            0, 4, 7,
            0, 3, 7,
            // back
            4, 5, 7,
            5, 6, 7,
            // top
            2, 3, 6,
            3, 6, 7,
            // bottom
            0, 1, 5,
            0, 4, 5
    };
public:
    Cube() {

    }
    void draw() {
        vertices
    }

};


#endif //OPENGLSETUPFROMGLFW_CUBE_H
