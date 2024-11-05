#include <catch2/catch_amalgamated.hpp>
#include "../draw2d/surface.hpp"
#include "../draw2d/draw.hpp"
#include "../triangles-test/helpers.hpp"



TEST_CASE("Triangles with same vertices but different order", "[triangle_same_vertices]")
{
    Surface surface1(200, 200);
    Surface surface2(200, 200);
    surface1.clear();
    surface2.clear();

    
    Vec2f p0 = { 50.f, 50.f };
    Vec2f p1 = { 150.f, 50.f };
    Vec2f p2 = { 100.f, 150.f };

    ColorF c0 = { 1.0f, 0.0f, 0.0f }; // Red
    ColorF c1 = { 0.0f, 1.0f, 0.0f }; // Green
    ColorF c2 = { 0.0f, 0.0f, 1.0f }; // Blue

    
    draw_triangle_interp(surface1, p0, p1, p2, c0, c1, c2);

    draw_triangle_interp(surface2, p1, p2, p0, c1, c2, c0);

    
    bool surfacesAreIdentical = true;
    for (Surface::Index y = 0; y < surface1.get_height(); y++)
    {
        for (Surface::Index x = 0; x < surface1.get_width(); x++)
        {
            ColorU8_sRGB color1 = get_pixel_color(surface1, x, y);
            ColorU8_sRGB color2 = get_pixel_color(surface2, x, y);
            if (color1.r != color2.r || color1.g != color2.g || color1.b != color2.b)
            {
                surfacesAreIdentical = false;
                break;
            }
        }
        if (!surfacesAreIdentical) break;
    }

    REQUIRE(surfacesAreIdentical);
}
