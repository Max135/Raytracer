//
// Created by Max on 2021-01-02.
//

#ifndef RAYTRACER_CANVAS_H
#define RAYTRACER_CANVAS_H


#include <vector>
#include <cmath>
#include <fstream>
#include "../Tuple/Color.h"

class Canvas {
    constexpr static const int COLOR_VALUE = 255;
public:
    int width, height;

    Canvas(int width, int height);

    ~Canvas();

    void writePixel(int x, int y, const Tuple &color);

    void fillCanvas(const Color &color);

    void save();

    Color pixelAt(int x, int y);

    std::string toPPM();

private:
    Color **pixelGrid;

    Color **initializeGrid();

    std::string createHeader();

    void addColorBody(const Color &pixel, std::string *body);
};


#endif //RAYTRACER_CANVAS_H
