#include "draw.hpp"

#include <algorithm>

#include <cmath>

#include "surface.hpp"


void draw_line_solid(Surface& aSurface, Vec2f aBegin, Vec2f aEnd, ColorU8_sRGB aColor)
{
	//test
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

void draw_line_interp(Surface& aSurface, Vec2f aP0, Vec2f aP1, ColorF aC0, ColorF aC1)
{
	// Calculate differences in position and color
	float dx = aP1.x - aP0.x;
	float dy = aP1.y - aP0.y;

	// The number of steps needed (greater difference determines steps)
	int steps = static_cast<int>(std::max(std::abs(dx), std::abs(dy)));

	// Handle degenerate lines (if both points are the same)
	if (steps == 0) {
		aSurface.set_pixel_srgb(static_cast<int>(aP0.x), static_cast<int>(aP0.y), linear_to_srgb(aC0));
		return;
	}

	// Calculate increments per step for position and color
	float xIncrement = dx / steps;
	float yIncrement = dy / steps;

	ColorF colorIncrement = {
		(aC1.r - aC0.r) / steps,
		(aC1.g - aC0.g) / steps,
		(aC1.b - aC0.b) / steps
	};

	// Initialize position and color
	float x = aP0.x;
	float y = aP0.y;
	ColorF color = aC0;

	// Draw the line
	for (int i = 0; i <= steps; ++i)
	{
		// Convert interpolated color to sRGB and set the pixel
		aSurface.set_pixel_srgb(static_cast<int>(std::round(x)), static_cast<int>(std::round(y)), linear_to_srgb(color));

		// Increment position and color
		x += xIncrement;
		y += yIncrement;
		color.r += colorIncrement.r;
		color.g += colorIncrement.g;
		color.b += colorIncrement.b;
	}
}


void draw_triangle_wireframe(Surface& aSurface, Vec2f aP0, Vec2f aP1, Vec2f aP2, ColorU8_sRGB aColor)
{
	// Draw the edges, with no color
	//ColorU8_sRGB lineColor = { 0,0,0 };
	draw_line_solid(aSurface, aP0, aP1, aColor);
	draw_line_solid(aSurface, aP1, aP2, aColor);
	draw_line_solid(aSurface, aP2, aP0, aColor);
}

void draw_triangle_solid(Surface& aSurface, Vec2f aP0, Vec2f aP1, Vec2f aP2, ColorU8_sRGB aColor)
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

void draw_triangle_interp(Surface& aSurface, Vec2f aP0, Vec2f aP1, Vec2f aP2, ColorF aC0, ColorF aC1, ColorF aC2)
{
	//Calculate the area of the triangle
	float area = std::abs(aP0.x * (aP1.y - aP2.y) + aP1.x * (aP2.y - aP0.y) + aP2.x * (aP0.y - aP1.y)) / 2.0f;

	// Check for degenerate triangle (zero area)
	if (area == 0.0f)
	{
		return; // Do not draw anything for degenerate triangles
	}

	// Draw the triangle edges using the draw_line_solid function
	ColorU8_sRGB color0 = linear_to_srgb(aC0);
	ColorU8_sRGB color1 = linear_to_srgb(aC1);
	ColorU8_sRGB color2 = linear_to_srgb(aC2);


	
	// Draw the edges, with no color // no need
	/*ColorU8_sRGB lineColor = { 0,0,0 };
	draw_line_solid(aSurface, aP0, aP1, lineColor);
	draw_line_solid(aSurface, aP1, aP2, lineColor);
	draw_line_solid(aSurface, aP2, aP0, lineColor);*/

	int minX = static_cast<int>(std::floor(std::min({ aP0.x, aP1.x, aP2.x })));
	int maxX = static_cast<int>(std::ceil(std::max({ aP0.x, aP1.x, aP2.x })));
	int minY = static_cast<int>(std::floor(std::min({ aP0.y, aP1.y, aP2.y })));
	int maxY = static_cast<int>(std::ceil(std::max({ aP0.y, aP1.y, aP2.y })));

	// Ensure the bounding box is within surface dimensions
	minX = std::max(0, minX);
	maxX = std::min(static_cast<int>(aSurface.get_width() - 1), maxX);
	minY = std::max(0, minY);
	maxY = std::min(static_cast<int>(aSurface.get_height() - 1), maxY);

	// Iterate over each pixel in the bounding box
	for (int y = minY; y <= maxY; ++y)
	{
		for (int x = minX; x <= maxX; ++x)
		{
			//Calculate barycentric coordinates
			float w0 = (aP1.x - aP0.x) * (y - aP0.y) - (aP1.y - aP0.y) * (x - aP0.x);
			float w1 = (aP2.x - aP1.x) * (y - aP1.y) - (aP2.y - aP1.y) * (x - aP1.x);
			float w2 = (aP0.x - aP2.x) * (y - aP2.y) - (aP0.y - aP2.y) * (x - aP2.x);

			// Check if the pixel is inside the triangle
			if (w0 >= 0 && w1 >= 0 && w2 >= 0)
			{ // If inside the triangle
				//Interpolate the color
				float total = w0 + w1 + w2;
				float alpha = w0 / total;
				float beta = w1 / total;
				float gamma = w2 / total;

				ColorF interpolatedColor =
				{
					aC0.r * alpha + aC1.r * beta + aC2.r * gamma,
					aC0.g * alpha + aC1.g * beta + aC2.g * gamma,
					aC0.b * alpha + aC1.b * beta + aC2.b * gamma
				};

				// Convert the color from float to uint8_t format
				ColorU8_sRGB finalColor = linear_to_srgb(interpolatedColor);

				// Set the pixel color on the surface
				aSurface.set_pixel_srgb(x, y, finalColor);
			}
		}
	}
}





void draw_rectangle_solid(Surface& aSurface, Vec2f aMinCorner, Vec2f aMaxCorner, ColorU8_sRGB aColor)
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

void draw_rectangle_outline(Surface& aSurface, Vec2f aMinCorner, Vec2f aMaxCorner, ColorU8_sRGB aColor)
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