//
// Created by Max on 2021-01-02.
//

#include "../raytracer/features/Canvas/Canvas.h"
#include "gtest/gtest.h"

TEST(CanvasTests, TestCanvasCreation) {
    Canvas canvas(10, 20);

    ASSERT_EQ(10, canvas.width);
    ASSERT_EQ(20, canvas.height);
}

TEST(CanvasTests, TestWritingPixel) {
    Canvas canvas(10, 20);

    ASSERT_TRUE(Color(0, 0, 0) == canvas.pixelAt(2, 3));
    canvas.writePixel(2, 3, Color(1, 0, 0));
    ASSERT_TRUE(Color(1, 0, 0) == canvas.pixelAt(2, 3));
}

TEST(CanvasTests, TestPPMConversion) {
    Canvas canvas(5, 3);

    canvas.writePixel(0, 0, Color(1.5, 0, 0));
    canvas.writePixel(2, 1, Color(0, 0.5, 0));
    canvas.writePixel(4, 2, Color(-0.5, 0, 1));

    ASSERT_EQ("P3\n5 3\n255\n"
              "255 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n"
              "0 0 0 0 0 0 0 128 0 0 0 0 0 0 0\n"
              "0 0 0 0 0 0 0 0 0 0 0 0 0 0 255\n"
              , canvas.toPPM());
}

TEST(CanvasTests, TestPMMFormating) {
    Canvas canvas(10, 2);
    Color color(1, 0.8, 0.6);

    canvas.fillCanvas(color);

    std::string canvasPPM = canvas.toPPM();

    ASSERT_EQ("P3\n10 2\n255\n"
              "255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204 "
              "153 255 204 153 255 204 153 255 204 153 255 204 153\n"
              "255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204 "
              "153 255 204 153 255 204 153 255 204 153 255 204 153\n",
              canvasPPM);

    ASSERT_EQ('\n', canvasPPM[canvasPPM.size()-1]);
}
