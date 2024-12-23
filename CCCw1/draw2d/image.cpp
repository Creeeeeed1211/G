#include "image.hpp"

#include <memory>
#include <algorithm>

#include <cstdio>
#include <cstring>
#include <cassert>

#include <stb_image.h>

#include "surface.hpp"

#include "../support/error.hpp"

namespace
{
	struct STBImageRGBA_ : public ImageRGBA
	{
		STBImageRGBA_( Index, Index, std::uint8_t* );
		virtual ~STBImageRGBA_();
	};
}

ImageRGBA::ImageRGBA()
	: mWidth( 0 )
	, mHeight( 0 )
	, mData( nullptr )
{}

ImageRGBA::~ImageRGBA() = default;


std::unique_ptr<ImageRGBA> load_image( char const* aPath )
{
	assert( aPath );

	stbi_set_flip_vertically_on_load( true );

	int w, h, channels;
	stbi_uc* ptr = stbi_load( aPath, &w, &h, &channels, 4 );
	if( !ptr )
		throw Error( "Unable to load image \"%s\"", aPath );

	return std::make_unique<STBImageRGBA_>(
		ImageRGBA::Index(w),
		ImageRGBA::Index(h),
		ptr
	);
}

void blit_masked(Surface& aSurface, ImageRGBA const& aImage, Vec2f aPosition) {
	int imgWidth = aImage.get_width();
	int imgHeight = aImage.get_height();

	//top-left corner of the image
	int startX = static_cast<int>(aPosition.x - imgWidth / 2);
	int startY = static_cast<int>(aPosition.y - imgHeight / 2);

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

			
			if (pixel.a >= 128) 
			{
				
				aSurface.set_pixel_srgb(surfaceX, surfaceY, { pixel.r, pixel.g, pixel.b });
			}
		}
	}
}



namespace
{
	STBImageRGBA_::STBImageRGBA_( Index aWidth, Index aHeight, std::uint8_t* aPtr )
	{
		mWidth = aWidth;
		mHeight = aHeight;
		mData = aPtr;
	}

	STBImageRGBA_::~STBImageRGBA_()
	{
		if( mData )
			stbi_image_free( mData );
	}
}
