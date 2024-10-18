#include "draw.hpp"

#include <algorithm>

#include <cmath>

#include "surface.hpp"


void draw_line_solid( Surface& aSurface, Vec2f aBegin, Vec2f aEnd, ColorU8_sRGB aColor )
{
	int startX = static_cast<int>(aBegin.x);
	int startY = static_cast<int>(aBegin.y);
	int endX = static_cast<int>(aEnd.x);
	int endY = static_cast<int>(aEnd.y);

	int deltaX = abs(endX - startX);
	int deltaY = abs(endY - startY);
	int stepX = (startX < endX) ? 1 : -1;
	int stepY = (startY < endY) ? 1 : -1;
	int error = deltaX - deltaY;

	 while (startX != endX || startY != endY)
    {
		 
		 if (startX >= 0 && startX < aSurface.get_width() &&
			 startY >= 0 && startY < aSurface.get_height())
		 {
			 aSurface.set_pixel_srgb(startX, startY, aColor);
		 }
        
        int error2 = 2 * error;
        if (error2 > -deltaY)
        {
            error -= deltaY;
            startX += stepX;
        }        if (error2 < deltaX)
        {
            error += deltaX;
            startY += stepY;
        }
    }
	 // Set the last pixel if within bounds
	 if (endX >= 0 && endX < aSurface.get_width() &&
		 endY >= 0 && endY < aSurface.get_height())
	 {
		 aSurface.set_pixel_srgb(endX, endY, aColor);
	 }

}

void draw_triangle_wireframe( Surface& aSurface, Vec2f aP0, Vec2f aP1, Vec2f aP2, ColorU8_sRGB aColor )
{
	
	
	
	//TODO: your implementation goes here
	//TODO: your implementation goes here
	//TODO: your implementation goes here

	//TODO: remove the following when you start your implementation
	//(void)aSurface; // Avoid warnings about unused arguments until the function
	//(void)aP0;   // is properly implemented.
	//(void)aP1;
	//(void)aP2;
	//(void)aColor;
}

void draw_triangle_solid( Surface& aSurface, Vec2f aP0, Vec2f aP1, Vec2f aP2, ColorU8_sRGB aColor )
{
	//TODO: your implementation goes here
	//TODO: your implementation goes here
	//TODO: your implementation goes here

	//TODO: remove the following when you start your implementation
	(void)aSurface; // Avoid warnings about unused arguments until the function
	(void)aP0;   // is properly implemented.
	(void)aP1;
	(void)aP2;
	(void)aColor;
}

void draw_triangle_interp(Surface& aSurface, Vec2f aP0, Vec2f aP1, Vec2f aP2, ColorF aC0, ColorF aC1, ColorF aC2) {
	// Step 1: Calculate the area of the triangle
	float area = std::abs(aP0.x * (aP1.y - aP2.y) + aP1.x * (aP2.y - aP0.y) + aP2.x * (aP0.y - aP1.y)) / 2.0f;

	// Step 2: Define the bounding box
	int minX = static_cast<int>(std::floor(std::min({ aP0.x, aP1.x, aP2.x })));
	int maxX = static_cast<int>(std::ceil(std::max({ aP0.x, aP1.x, aP2.x })));
	int minY = static_cast<int>(std::floor(std::min({ aP0.y, aP1.y, aP2.y })));
	int maxY = static_cast<int>(std::ceil(std::max({ aP0.y, aP1.y, aP2.y })));

	// Ensure the bounding box is within surface dimensions
	minX = std::max(0, minX);
	maxX = std::min(static_cast<int>(aSurface.get_width() - 1), maxX);
	minY = std::max(0, minY);
	maxY = std::min(static_cast<int>(aSurface.get_height() - 1), maxY);

	// Step 3: Iterate over each pixel in the bounding box
	for (int y = minY; y <= maxY; ++y) {
		for (int x = minX; x <= maxX; ++x) {
			// Calculate barycentric coordinates
			float alpha = std::abs(x * (aP1.y - aP2.y) + aP1.x * (aP2.y - y) + aP2.x * (y - aP1.y)) /
				(2.0f * area);
			float beta = std::abs(aP0.x * (aP2.y - y) + x * (y - aP0.y) + aP2.x * (aP0.y - aP2.y)) /
				(2.0f * area);
			float gamma = 1.0f - alpha - beta;

			// Check if the point (x, y) is inside the triangle
			if (alpha >= 0 && beta >= 0 && gamma >= 0) {
				// Interpolate the color
				ColorF color = {
					aC0.r * alpha + aC1.r * beta + aC2.r * gamma,
					aC0.g * alpha + aC1.g * beta + aC2.g * gamma,
					aC0.b * alpha + aC1.b * beta + aC2.b * gamma
				};

				// Convert the color from float to uint8_t format using the conversion function
				ColorU8_sRGB colorU8 = linear_to_srgb(color);

				// Set the pixel color on the surface using set_pixel_srgb
				aSurface.set_pixel_srgb(x, y, colorU8);
			}
		}
	}
}



	


void draw_rectangle_solid( Surface& aSurface, Vec2f aMinCorner, Vec2f aMaxCorner, ColorU8_sRGB aColor )
{
	//TODO: your implementation goes here
	//TODO: your implementation goes here
	//TODO: your implementation goes here

	//TODO: remove the following when you start your implementation
	(void)aSurface; // Avoid warnings about unused arguments until the function
	(void)aMinCorner;   // is properly implemented.
	(void)aMaxCorner;
	(void)aColor;
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
