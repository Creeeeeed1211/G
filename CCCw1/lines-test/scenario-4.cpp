#include <catch2/catch_amalgamated.hpp>
#include "../draw2d/surface.hpp"
#include "../draw2d/draw.hpp"
#include "../lines-test/helpers.hpp"




TEST_CASE("Connected lines without gaps", "[connected_lines]")
{
    Surface surface(200, 200);
    surface.clear();
    ColorU8_sRGB color = { 255, 255, 255 };

    SECTION("Two connected lines forming a 'V' shape")
    {
        // Draw two lines connected at {100, 100}
        draw_line_solid(surface, { 50.f, 50.f }, { 100.f, 100.f }, color);
        draw_line_solid(surface, { 100.f, 100.f }, { 150.f, 50.f }, color);

        // Check for continuity at the connection point {100, 100}
        bool noGap = true;
        ColorU8_sRGB p1_color = get_pixel_color(surface, 100, 100);

        if (p1_color.r != color.r || p1_color.g != color.g || p1_color.b != color.b)
        {
            noGap = false;
        }

        REQUIRE(noGap);
    }

    SECTION("Z")
    {
        // Draw three lines connected at {100, 100} and {150, 150}
        draw_line_solid(surface, { 50.f, 50.f }, { 100.f, 100.f }, color);
        draw_line_solid(surface, { 100.f, 100.f }, { 150.f, 150.f }, color);
        draw_line_solid(surface, { 150.f, 150.f }, { 200.f, 100.f }, color);

        // Check continuity at connection points {100, 100} and {150, 150}
        bool noGap = true;
        ColorU8_sRGB p1_color = get_pixel_color(surface, 100, 100);
        ColorU8_sRGB p2_color = get_pixel_color(surface, 150, 150);

        if ((p1_color.r != color.r || p1_color.g != color.g || p1_color.b != color.b) ||
            (p2_color.r != color.r || p2_color.g != color.g || p2_color.b != color.b))
        {
            noGap = false;
        }

        REQUIRE(noGap);
    }

    SECTION("Short connected lines in sequence")
    {
        // Draw multiple short connected lines
        draw_line_solid(surface, { 90.f, 100.f }, { 95.f, 100.f }, color);
        draw_line_solid(surface, { 95.f, 100.f }, { 100.f, 100.f }, color);
        draw_line_solid(surface, { 100.f, 100.f }, { 105.f, 100.f }, color);
        draw_line_solid(surface, { 105.f, 100.f }, { 110.f, 100.f }, color);

        // Check for gaps between the connected points {95, 100}, {100, 100}, {105, 100}
        bool noGap = true;
        std::vector<Surface::Index> points = { 95, 100, 105 };

        for (auto x : points)
        {
            ColorU8_sRGB check_color = get_pixel_color(surface, x, 100);
            if (check_color.r != color.r || check_color.g != color.g || check_color.b != color.b)
            {
                noGap = false;
                break;
            }
        }

        REQUIRE(noGap);
    }

    SECTION("Diagonal")
    {
        
        draw_line_solid(surface, { 25.f, 25.f }, { 50.f, 50.f }, color);
        draw_line_solid(surface, { 50.f, 50.f }, { 75.f, 75.f }, color);
        draw_line_solid(surface, { 75.f, 75.f }, { 100.f, 100.f }, color);

     
        bool noGap = true;
        std::vector<std::pair<Surface::Index, Surface::Index>> points = { {50, 50}, {75, 75} };

        for (const auto& [x, y] : points)
        {
            ColorU8_sRGB check_color = get_pixel_color(surface, x, y);
            if (check_color.r != color.r || check_color.g != color.g || check_color.b != color.b)
            {
                noGap = false;
                break;
            }
        }

        REQUIRE(noGap);
    }
}
