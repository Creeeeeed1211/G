#include "draw-ex.hpp"

#include <algorithm>

#include <cstring> // for std::memcpy()

#include "image.hpp"
#include "surface-ex.hpp"

void draw_ex_line_solid( SurfaceEx& aSurface, Vec2f aBegin, Vec2f aEnd, ColorU8_sRGB aColor )
{
	//TODO: your implementation goes here
	//TODO: your implementation goes here
	//TODO: your implementation goes here

	//TODO: remove the following when you start your implementation
	(void)aSurface; // Avoid warnings about unused arguments until the function
	(void)aBegin;   // is properly implemented.
	(void)aEnd;
	(void)aColor;
}

void blit_ex_solid( SurfaceEx& aSurface, ImageRGBA const& aImage, Vec2f aPosition )
{
	int imgWidth = aImage.get_width();
	int imgHeight = aImage.get_height();
	



	// Calculate top-left corner of the image relative to the surface
	int startX = static_cast<int>(aPosition.x - imgWidth / 2);
	int startY = static_cast<int>(aPosition.y - imgHeight / 2);

	// Iterate over the image pixels
	for (int y = 0; y < imgHeight; y++)
	{
		for (int x = 0; x < imgWidth; x++)
		{

			int surfaceX = startX + x;
			int surfaceY = startY + y;


			if (surfaceX < 0 || surfaceX >= aSurface.get_width() ||
				surfaceY < 0 || surfaceY >= aSurface.get_height())
			{
				continue;
			}

			// Get the image pixel
			ColorU8_sRGB_Alpha pixel = aImage.get_pixel(x, y);


			
			aSurface.set_pixel_srgb(surfaceX, surfaceY, { pixel.r, pixel.g, pixel.b });
			
		}
	}
}

void blit_ex_memcpy(SurfaceEx& aSurface, ImageRGBA const& aImage, Vec2f aPosition)
{
    int imgWidth = aImage.get_width();
    int imgHeight = aImage.get_height();

    int winWidth = aSurface.get_width();
    int winHeight = aSurface.get_height();

    
    Vec2f imgMax = { aPosition.x + imgWidth / 2, aPosition.y + imgHeight / 2 };
    Vec2f imgMin = { aPosition.x - imgWidth / 2, aPosition.y - imgHeight / 2 };

    // Clip the img boundaries
    int clipXMin = std::max(0, static_cast<int>(imgMin.x));
    int clipYMin = std::max(0, static_cast<int>(imgMin.y));
    int clipXMax = std::min(winWidth, static_cast<int>(imgMax.x));
    int clipYMax = std::min(winHeight, static_cast<int>(imgMax.y));

   
    int clippedWidth = clipXMax - clipXMin;
    int clippedHeight = clipYMax - clipYMin;

    
    if (clippedWidth <= 0 || clippedHeight <= 0) {
        return;
    }

    // Ptr to image and surface data
    auto imgPtr = aImage.get_image_ptr();
    auto DataPtr = aSurface.get_surface_ptr();

    // row
    for (int y = 0; y < clippedHeight; ++y) {
        // row in the image
        int imgY = clipYMin + y - static_cast<int>(imgMin.y);

        //  row in the surface
        int surfaceY = clipYMin + y;

        
        auto imgRowStart = imgY * imgWidth + clipXMin - static_cast<int>(imgMin.x);
        auto surfaceRowStart = surfaceY * winWidth + clipXMin;

        
        std::memcpy(&DataPtr[surfaceRowStart], &imgPtr[imgRowStart], clippedWidth * sizeof(ImageRGBA));
    }
}

