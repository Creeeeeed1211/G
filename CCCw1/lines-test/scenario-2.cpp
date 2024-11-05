#include <catch2/catch_amalgamated.hpp>
#include "../draw2d/surface.hpp"
#include "../draw2d/draw.hpp"
#include "../lines-test/helpers.hpp"



TEST_CASE("Line clipping with one point inside and the other outside the surface", "[clipping]")
{
    Surface surface(200, 200);
    ColorU8_sRGB color = { 255, 255, 255 };

    SECTION("Horizontal line with one endpoint inside and the other outside to the right")
    {
        surface.clear();
        draw_line_solid(surface, { 150.f, 100.f }, { 250.f, 100.f }, color);

        bool correctDrawing = true;

        // Check expected drawn pixels
        for (Surface::Index x = 150; x < surface.get_width(); ++x)
        {
            ColorU8_sRGB check = get_pixel_color(surface, x, 100);
            if (check.r != color.r || check.g != color.g || check.b != color.b)
            {
                correctDrawing = false;
                break;
            }
        }

        REQUIRE(correctDrawing);
    }

    SECTION("Vertical line with one endpoint inside and the other outside at the bottom")
    {
        surface.clear();
        draw_line_solid(surface, { 100.f, 150.f }, { 100.f, 250.f }, color);

        bool correctDrawing = true;

        // Check expected drawn pixels
        for (Surface::Index y = 150; y < surface.get_height(); ++y)
        {
            ColorU8_sRGB check = get_pixel_color(surface, 100, y);
            if (check.r != color.r || check.g != color.g || check.b != color.b)
            {
                correctDrawing = false;
                break;
            }
        }

        REQUIRE(correctDrawing);
    }

    SECTION("Diagonal line with one endpoint inside and the other outside the bottom-right")
    {
        surface.clear();
        draw_line_solid(surface, { 100.f, 100.f }, { 250.f, 250.f }, color);

        bool correctDrawing = true;

        // Check expected drawn pixels
        for (Surface::Index y = 100; y < surface.get_height(); ++y)
        {
            for (Surface::Index x = 100; x < surface.get_width(); ++x)
            {
                if (x - 100 == y - 100) 
                {
                    ColorU8_sRGB check = get_pixel_color(surface, x, y);
                    if (check.r != color.r || check.g != color.g || check.b != color.b)
                    {
                        correctDrawing = false;
                        break;
                    }
                }
            }
            if (!correctDrawing) break;
        }

        REQUIRE(correctDrawing);
    }

    SECTION("Line with one endpoint inside and the other outside to the left")
    {
        surface.clear();
        draw_line_solid(surface, { 50.f, 100.f }, { -50.f, 100.f }, color);

        bool correctDrawing = true;

        // Check expected drawn pixels
        for (Surface::Index x = 0; x <= 50; ++x)
        {
            ColorU8_sRGB check = get_pixel_color(surface, x, 100);
            if (check.r != color.r || check.g != color.g || check.b != color.b)
            {
                correctDrawing = false;
                break;
            }
        }

        REQUIRE(correctDrawing);
    }

    SECTION("Line with one endpoint inside and the other outside to the top")
    {
        surface.clear();
        draw_line_solid(surface, { 100.f, 50.f }, { 100.f, -50.f }, color);

        bool correctDrawing = true;

        // Check expected drawn pixels
        for (Surface::Index y = 0; y <= 50; ++y)
        {
            ColorU8_sRGB check = get_pixel_color(surface, 100, y);
            if (check.r != color.r || check.g != color.g || check.b != color.b)
            {
                correctDrawing = false;
                break;
            }
        }

        REQUIRE(correctDrawing);
    }
}
