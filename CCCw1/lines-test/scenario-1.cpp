#include <catch2/catch_amalgamated.hpp>
#include "../draw2d/surface.hpp"
#include "../draw2d/draw.hpp"

TEST_CASE( "identical", "[identical]" )
{
    
    Surface surface1(200, 200);
    Surface surface2(200, 200);

    const Surface::Index startX = 20, startY = 50;
    const Surface::Index endX = 150, endY = 180;

   
    const ColorU8_sRGB color = {255, 255, 255};

    //opposite directions
    surface1.clear();
    surface2.clear();
    draw_line_solid(surface1, {static_cast<float>(startX), static_cast<float>(startY)},
                    {static_cast<float>(endX), static_cast<float>(endY)}, color);
    draw_line_solid(surface2, {static_cast<float>(endX), static_cast<float>(endY)},
                    {static_cast<float>(startX), static_cast<float>(startY)}, color);


    
    bool identical = true;
    
    for (Surface::Index y = 0; y < surface1.get_height(); y++)
    {
        for (Surface::Index x = 0; x < surface1.get_width(); x++)
        {
            Surface::Index index1 = surface1.get_linear_index(x, y);
            Surface::Index index2 = surface2.get_linear_index(x, y);

            if (surface1.get_surface_ptr()[index1] != surface2.get_surface_ptr()[index2])
            {
                identical = false;
                break;
            }
        }
        if (!identical) break;
    }

    REQUIRE(identical);

   
}
