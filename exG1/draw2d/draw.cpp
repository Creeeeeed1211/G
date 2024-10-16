#include "draw.hpp"
#include <algorithm>
#include <cmath>
#include "color.hpp"
#include "surface.hpp"

void draw_rectangle_solid(Surface& aSurface, Vec2f aMinCorner, Vec2f aMaxCorner, ColorU8_sRGB aColor)
{
    float minX = std::min(aMinCorner.x, aMaxCorner.x);
    float maxX = std::max(aMinCorner.x, aMaxCorner.x);
    float minY = std::min(aMinCorner.y, aMaxCorner.y);
    float maxY = std::max(aMinCorner.y, aMaxCorner.y);

	for (int y = static_cast<int>(minY); y < static_cast<int>(maxY); ++y) 
	{
		for (int x = static_cast<int>(minX); x < static_cast<int>(maxX); ++x) 
		{
			aSurface.set_pixel_srgb(x, y, aColor);
		}
	}
}



void draw_rectangle_outline( Surface& aSurface, Vec2f aMinCorner, Vec2f aMaxCorner, ColorU8_sRGB aColor )
{
	//TODO: your implementation goes here
	//TODO: your implementation goes here
	//TODO: your implementation goes here

	//TODO: remove the following when you start your implementation
	(void)aSurface; // Avoid warnings about unused arguments
	(void)aMinCorner;
	(void)aMaxCorner;
	(void)aColor;
}
