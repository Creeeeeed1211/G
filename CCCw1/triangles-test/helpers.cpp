#include "helpers.hpp"

#include "../draw2d/color.hpp"
#include "../draw2d/surface.hpp"
#include <cmath> 


ColorU8_sRGB find_most_red_pixel( Surface const& aSurface )
{
	ColorU8_sRGB ret{ 0, 0, 0 };

	auto const stride = aSurface.get_width() << 2;
	for( std::uint32_t x = 0; x < aSurface.get_width(); ++x )
	{
		for( std::uint32_t y = 0; y < aSurface.get_height(); ++y )
		{
			auto const idx = y*stride + (x<<2);
			auto const ptr = aSurface.get_surface_ptr() + idx;

			// Not really needed.
			//if( 0 == ptr[0] && 0 == ptr[1] && 0 == ptr[2] )
			//	continue;

			if( ptr[0] >= ret.r )
			{
				ret.r = ptr[0];
				ret.g = ptr[1];
				ret.b = ptr[2];
			}
		}
	}

	return ret;
}


ColorU8_sRGB get_pixel_color(Surface const& surface, Surface::Index x, Surface::Index y)
{
	auto width = surface.get_width();
	const std::uint8_t* surfaceData = surface.get_surface_ptr();


	Surface::Index index = y * width + x;


	const std::uint8_t* pixel = &surfaceData[index * 4];


	return { pixel[0], pixel[1], pixel[2] };
}

ColorU8_sRGB find_least_red_nonzero_pixel( Surface const& aSurface )
{
	ColorU8_sRGB ret{ 255, 255, 255 };

	auto const stride = aSurface.get_width() << 2;
	for( std::uint32_t x = 0; x < aSurface.get_width(); ++x )
	{
		for( std::uint32_t y = 0; y < aSurface.get_height(); ++y )
		{
			auto const idx = y*stride + (x<<2);
			auto const ptr = aSurface.get_surface_ptr() + idx;

			if( 0 == ptr[0] && 0 == ptr[1] && 0 == ptr[2] )
				continue;

			if( ptr[0] < ret.r )
			{
				ret.r = ptr[0];
				ret.g = ptr[1];
				ret.b = ptr[2];
			}
		}
	}

	return ret;

}


//bool colors_are_approximately_equal(const coloru8_srgb& color1, const coloru8_srgb& color2, float tolerance = 0.1f)
//{
//	// compare each channel with a specified tolerance
//	return (std::fabs(color1.r - color2.r) <= tolerance * 255) &&
//		(std::fabs(color1.g - color2.g) <= tolerance * 255) &&
//		(std::fabs(color1.b - color2.b) <= tolerance * 255);
//}


ColorU8_sRGB interpolate_colors(const ColorU8_sRGB& c1, const ColorU8_sRGB& c2, float t)
{
	return {
		static_cast<std::uint8_t>(c1.r + t * (c2.r - c1.r)),
		static_cast<std::uint8_t>(c1.g + t * (c2.g - c1.g)),
		static_cast<std::uint8_t>(c1.b + t * (c2.b - c1.b))
	};
}

