#include "draw.hpp"

#include <algorithm>

#include <cmath>

#include "surface.hpp"


void draw_line_solid(Surface& aSurface, Vec2f aBegin, Vec2f aEnd, ColorU8_sRGB aColor)
{

	int width = aSurface.get_width() - 1;
	int height = aSurface.get_height() - 1;

	
	float t_min = 0.0f;
	float t_max = 1.0f;

	// Delta
		Vec2f d = aEnd - aBegin;

	
		if (d.x != 0.0f) {
			float t_x0 = -aBegin.x / d.x;
			float t_xw = (width - aBegin.x) / d.x;

			//left to right
			if (d.x > 0) {
				t_min = std::max(0.f, t_x0);
				t_max = std::min(1.f, t_xw);
			}
			else {
			//right to left
				t_min = std::max(0.f, t_xw);	
				t_max = std::min(1.f, t_x0);
			}
		}	

	
		if (d.y != 0.0f) {
			float t_y0 = -aBegin.y / d.y;
			float t_yh = (height - aBegin.y) / d.y;

			if (d.y > 0) {
				//down to up
				t_min = std::max(t_min, t_y0);
				t_max = std::min(t_max, t_yh);
			}
			else {
				// up to down
				t_min = std::max(t_min, t_yh);
				t_max = std::min(t_max, t_y0);
			}
		}

	//outside the bounds
	if (t_min > t_max) return;



	Vec2f clippedBegin = aBegin + t_min * d;
	Vec2f clippedEnd = aBegin + t_max * d;

	
	int startX = clippedBegin.x;
	int startY = clippedBegin.y;
	int endX = clippedEnd.x;
	int endY = clippedEnd.y;

	// Bresenham's algorithm
	int deltaX = abs(endX - startX);
	int deltaY = abs(endY - startY);
	int stepX = (startX < endX) ? 1 : -1;
	int stepY = (startY < endY) ? 1 : -1;
	int error = deltaX - deltaY;

	while (startX != endX || startY != endY)
	{
		aSurface.set_pixel_srgb(startX, startY, aColor);

		int error2 = 2 * error;
		if (error2 > -deltaY)
		{
			error -= deltaY;
			startX += stepX;
		}
		if (error2 < deltaX)
		{
			error += deltaX;
			startY += stepY;
		}
	}

	aSurface.set_pixel_srgb(endX, endY, aColor);
}





void draw_triangle_wireframe(Surface& aSurface, Vec2f aP0, Vec2f aP1, Vec2f aP2, ColorU8_sRGB aColor)
{
	
	draw_line_solid(aSurface, aP0, aP1, aColor);
	draw_line_solid(aSurface, aP1, aP2, aColor);
	draw_line_solid(aSurface, aP2, aP0, aColor);
}

void draw_triangle_solid(Surface& aSurface, Vec2f aP0, Vec2f aP1, Vec2f aP2, ColorU8_sRGB aColor)
{
	
	
	float area = std::abs(aP0.x * (aP1.y - aP2.y) + aP1.x * (aP2.y - aP0.y) + aP2.x * (aP0.y - aP1.y)) / 2.0f;

	
	if (area == 0.0f)
	{
		return; 
	}

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
			float w0 = (aP1.x - aP0.x) * (y - aP0.y) - (aP1.y - aP0.y) * (x - aP0.x);
			float w1 = (aP2.x - aP1.x) * (y - aP1.y) - (aP2.y - aP1.y) * (x - aP1.x);
			float w2 = (aP0.x - aP2.x) * (y - aP2.y) - (aP0.y - aP2.y) * (x - aP2.x);

			// Check if the pixel is inside the triangle
			if (w0 >= 0 && w1 >= 0 && w2 >= 0)
			{ // If inside the triangle
				//Interpolate the color
				float total = w0 + w1 + w2;


				
				aSurface.set_pixel_srgb(x, y, aColor);
			}
		}
	}
}

void draw_triangle_interp(Surface& aSurface, Vec2f aP0, Vec2f aP1, Vec2f aP2, ColorF aC0, ColorF aC1, ColorF aC2)
{
	// degenerate triangle
	float area = std::abs(aP0.x * (aP1.y - aP2.y) + aP1.x * (aP2.y - aP0.y) + aP2.x * (aP0.y - aP1.y)) / 2.0f;

	
	if (area == 0.0f)
	{
		return; 
	}

	// Draw the edges, with no color
	// no need
	/*ColorU8_sRGB lineColor = { 0,0,0 };
	draw_line_solid(aSurface, aP0, aP1, lineColor);
	draw_line_solid(aSurface, aP1, aP2, lineColor);
	draw_line_solid(aSurface, aP2, aP0, lineColor);*/

	//make bouding box

	int minX = static_cast<int>(std::floor(std::min({ aP0.x, aP1.x, aP2.x })));
	int maxX = static_cast<int>(std::ceil(std::max({ aP0.x, aP1.x, aP2.x })));
	int minY = static_cast<int>(std::floor(std::min({ aP0.y, aP1.y, aP2.y })));
	int maxY = static_cast<int>(std::ceil(std::max({ aP0.y, aP1.y, aP2.y })));

	 
	minX = std::max(0, minX);
	maxX = std::min(static_cast<int>(aSurface.get_width() - 1), maxX);
	minY = std::max(0, minY);
	maxY = std::min(static_cast<int>(aSurface.get_height() - 1), maxY);

	
	for (int y = minY; y <= maxY; y++)
	{
		for (int x = minX; x <= maxX; x++)
		{
			// barycentric weight

			float w0 = (aP1.x - aP0.x) * (y - aP0.y) - (aP1.y - aP0.y) * (x - aP0.x);
			float w1 = (aP2.x - aP1.x) * (y - aP1.y) - (aP2.y - aP1.y) * (x - aP1.x);
			float w2 = (aP0.x - aP2.x) * (y - aP2.y) - (aP0.y - aP2.y) * (x - aP2.x);

			// inside when weight>=0
			if (w0 >= 0 && w1 >= 0 && w2 >= 0)
			{ 
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

	//using previous draw line method
	float maxHeight = static_cast<float>(aSurface.get_height() - 1);
	float maxWidth = static_cast<float>(aSurface.get_width() - 1);

	aMinCorner.x = std::max(0.0f, std::min(aMinCorner.x, maxWidth));
	aMinCorner.y = std::max(0.0f, std::min(aMinCorner.y, maxHeight));
	aMaxCorner.x = std::max(0.0f, std::min(aMaxCorner.x, maxWidth));
	aMaxCorner.y = std::max(0.0f, std::min(aMaxCorner.y, maxHeight));

	
	Vec2f lu = { aMinCorner.x , aMinCorner.y };
	Vec2f lb = { aMinCorner.x , aMaxCorner.y };
	Vec2f ru = { aMaxCorner.x , aMinCorner.y };
	Vec2f rb = { aMaxCorner.x , aMaxCorner.y };

	
	draw_line_solid(aSurface, lu, lb, aColor);
	draw_line_solid(aSurface, lb, rb, aColor);
	draw_line_solid(aSurface, rb, ru, aColor);
	draw_line_solid(aSurface, ru, lu, aColor);

}
