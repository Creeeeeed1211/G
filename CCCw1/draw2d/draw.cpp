#include "draw.hpp"

#include <algorithm>

#include <cmath>

#include "surface.hpp"

void draw_line_solid( Surface& aSurface, Vec2f aBegin, Vec2f aEnd, ColorU8_sRGB aColor )
{
	//TODO: your implementation goes here
	//TODO: your implementation goes here
	//TODO: your implementation goes here
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
        aSurface.set_pixel_srgb(startX, startY, aColor);
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
    aSurface.set_pixel_srgb(startX, startY, aColor); // Set the last pixel


	//TODO: remove the following when you start your implementation
	//(void)aSurface; // Avoid warnings about unused arguments until the function
	//(void)aBegin;   // is properly implemented.
	//(void)aEnd;
	//(void)aColor;
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

void draw_triangle_interp( Surface& aSurface, Vec2f aP0, Vec2f aP1, Vec2f aP2, ColorF aC0, ColorF aC1, ColorF aC2 )
{
	//TODO: your implementation goes here
	//TODO: your implementation goes here
	//TODO: your implementation goes here

	//TODO: remove the following when you start your implementation
	//(void)aSurface; // Avoid warnings about unused arguments until the function
	//(void)aP0;      // is properly implemented.
	//(void)aP1;
	//(void)aP2;
	//(void)aC0;
	//(void)aC1;
	//(void)aC2;

	
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
