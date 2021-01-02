//
// Created by Max on 2021-01-02.
//

#include <iostream>
#include "Canvas.h"

Color** Canvas::initializeGrid() {
    Color** grid = new Color*[this->height];
    for (int i = 0; i < this->height; ++i) {
        grid[i] = new Color[width];
        for (int j = 0; j < this->width; ++j) {
            grid[i][j] = Color(0,0,0);
        }
    }
    return grid;
}

void Canvas::writePixel(int x, int y, Color color) {
    if(x >= this->width || x < 0 || y >= this->height || y < 0) return;

    this->pixelGrid[y][x] = color;
}

Color Canvas::pixelAt(int x, int y) {
    if(x >= this->width || x < 0 || y >= this->height || y < 0) return;

    return this->pixelGrid[y][x];
}
