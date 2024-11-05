#include <catch2/catch_amalgamated.hpp>
#include "../draw2d/surface.hpp"
#include "../draw2d/draw.hpp"
#include "../triangles-test/helpers.hpp"

#include <cmath>

bool colors_are_approximately_equal(const ColorU8_sRGB& color1, const ColorU8_sRGB& color2, float tolerance = 0.1f)
{
    // Compare each channel with a specified tolerance
    return (std::fabs(color1.r - color2.r) <= tolerance * 255) &&
        (std::fabs(color1.g - color2.g) <= tolerance * 255) &&
        (std::fabs(color1.b - color2.b) <= tolerance * 255);
}

TEST_CASE("Basic color interpolation in triangle", "[triangle_basic_interpolation]")
{
    Surface surface(200, 200);
    surface.clear(); // Clear the surface to a default color

   
    Vec2f p0 = { 50.f, 50.f };   
    Vec2f p1 = { 150.f, 50.f };  
    Vec2f p2 = { 100.f, 150.f };

    ColorF c0 = { 1.0f, 0.0f, 0.0f }; 
    ColorF c1 = { 0.0f, 1.0f, 0.0f };
    ColorF c2 = { 0.0f, 0.0f, 1.0f };

   
    draw_triangle_interp(surface, p0, p1, p2, c0, c1, c2);

    // Approximate center
    Vec2f center = { 100.f, 83.f }; 
    ColorU8_sRGB expectedColor = linear_to_srgb({ 1.0f / 3, 1.0f / 3, 1.0f / 3 });

    // Retrieve the color at the center point
    ColorU8_sRGB actualColor = get_pixel_color(surface, static_cast<Surface::Index>(center.x), static_cast<Surface::Index>(center.y));

    REQUIRE(colors_are_approximately_equal(actualColor, expectedColor));
}


