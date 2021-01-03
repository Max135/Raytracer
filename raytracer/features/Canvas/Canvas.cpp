//
// Created by Max on 2021-01-02.
//

#include <cmath>
#include "Canvas.h"

//Took way too long to init a 2D grid...
Color **Canvas::initializeGrid() {
    Color **grid = new Color *[this->height];
    for (int i = 0; i < this->height; ++i) {
        grid[i] = new Color[width];
        for (int j = 0; j < this->width; ++j) {
            grid[i][j] = Color(0, 0, 0);
        }
    }
    return grid;
}

void Canvas::writePixel(int x, int y, Color color) {
    this->pixelGrid[y][x] = color;
}

Color Canvas::pixelAt(int x, int y) {
    return this->pixelGrid[y][x];
}

std::string Canvas::toPPM() {
    std::string header = createHeader();
    std::string body;

    for (int i = 0; i < this->height; ++i) {
        std::string line;
        for (int j = 0; j < this->width; ++j) {
            Color pixel = this->pixelAt(j, i);
            addColorBody(pixel, &body);
            if (line.size() - line.find_last_of('\n') >= 70) {
                line.push_back('\n');
            }
        }
        body.pop_back();           //Removes the last unused space
        line.append("\n");      //Add new line for each row
        body.append(line);
    }

    return header.append(body);
}

void Canvas::addColorBody(Color pixel, std::string *body) {
    int red = (int) round(pixel.x * COLOR_VALUE);
    red = (red < 0) ? 0 : (red > COLOR_VALUE) ? COLOR_VALUE : red;
    int green = (int) round(pixel.y * COLOR_VALUE);
    green = (green < 0) ? 0 : (green > COLOR_VALUE) ? COLOR_VALUE : green;
    int blue = (int) round(pixel.z * COLOR_VALUE);
    blue = (blue < 0) ? 0 : (blue > COLOR_VALUE) ? COLOR_VALUE : blue;

    body->append(std::to_string(red));
    body->append(" ");
    body->append(std::to_string(green));
    body->append(" ");
    body->append(std::to_string(blue));
    body->append(" ");
}

std::string Canvas::createHeader() {
    std::string header = "P3\n";                //File format
    header.append(std::to_string(width));   //Canvas width
    header.append(" ");
    header.append(std::to_string(height));  //Canvas height
    header.append("\n");
    header.append(std::to_string(COLOR_VALUE)); //Max color value
    header.append("\n");

    return header;
}

void Canvas::fillCanvas(Color color) {
    for (int i = 0; i < this->height; ++i) {
        for (int j = 0; j < this->width; ++j) {
            writePixel(j, i, color);
        }
    }
}
