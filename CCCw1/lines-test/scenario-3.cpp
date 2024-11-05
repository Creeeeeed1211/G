#include <catch2/catch_amalgamated.hpp>
#include "../draw2d/surface.hpp"
#include "../draw2d/draw.hpp"
#include "../lines-test/helpers.hpp"



TEST_CASE("Lines with both points outside the surface", "[OUTSIDE]")
{
    Surface surface(200, 200);
    surface.clear();
    ColorU8_sRGB color = { 255, 255, 255 };

    SECTION("Horizontal left")
    {
        bool pass = true;
        draw_line_solid(surface, { -100.f, 50.f }, { -50.f, 50.f }, color);

        for (Surface::Index y = 0; y < surface.get_height(); ++y)
        {
            for (Surface::Index x = 0; x < surface.get_width(); ++x)
            {
                ColorU8_sRGB check = get_pixel_color(surface, x, y);
                if (check.r != 0 || check.g != 0 || check.b != 0)
                {
                    pass = false;
                    break;
                }
            }
            if (!pass) break;
        }
        REQUIRE(pass);
    }

    SECTION("Vertical top")
    {
        bool pass = true;
        draw_line_solid(surface, { 100.f, 250.f }, { 100.f, 300.f }, color);

        for (Surface::Index y = 0; y < surface.get_height(); ++y)
        {
            for (Surface::Index x = 0; x < surface.get_width(); ++x)
            {
                ColorU8_sRGB check = get_pixel_color(surface, x, y);
                if (check.r != 0 || check.g != 0 || check.b != 0)
                {
                    pass = false;
                    break;
                }
            }
            if (!pass) break;
        }
        REQUIRE(pass);
    }

    SECTION("Diagonal bottom-left")
    {
        bool pass = true;
        draw_line_solid(surface, { -50.f, -50.f }, { -10.f, -10.f }, color);

        for (Surface::Index y = 0; y < surface.get_height(); ++y)
        {
            for (Surface::Index x = 0; x < surface.get_width(); ++x)
            {
                ColorU8_sRGB check = get_pixel_color(surface, x, y);
                if (check.r != 0 || check.g != 0 || check.b != 0)
                {
                    pass = false;
                    break;
                }
            }
            if (!pass) break;
        }
        REQUIRE(pass);
    }

    SECTION("Diagonal top-right")
    {
        bool pass = true;
        draw_line_solid(surface, { 250.f, 250.f }, { 300.f, 300.f }, color);

        for (Surface::Index y = 0; y < surface.get_height(); ++y)
        {
            for (Surface::Index x = 0; x < surface.get_width(); ++x)
            {
                ColorU8_sRGB check = get_pixel_color(surface, x, y);
                if (check.r != 0 || check.g != 0 || check.b != 0)
                {
                    pass = false;
                    break;
                }
            }
            if (!pass) break;
        }
        REQUIRE(pass);
    }

   
}
