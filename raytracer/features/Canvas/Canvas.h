//
// Created by Max on 2021-01-02.
//

#ifndef RAYTRACER_CANVAS_H
#define RAYTRACER_CANVAS_H

#include <vector>
#include "../Tuple/Tuples.h"

class Canvas {
    constexpr static const int COLOR_VALUE = 255;
public:
    int width, height;

    Canvas(int width, int height) {
        this->width = width;
        this->height = height;

        pixelGrid = initializeGrid();
    }

    void writePixel(int x, int y, Color color);

    void fillCanvas(Color color);

    Color pixelAt(int x, int y);

    std::string toPPM();

private:
    //TODO: https://stackoverflow.com/questions/936687/how-do-i-declare-a-2d-array-in-c-using-new
    //3rd answer for optimisation
    Color **pixelGrid;

    Color **initializeGrid();

    std::string createHeader();

    void addColorBody(Color pixel, std::string *body);
};


#endif //RAYTRACER_CANVAS_H
