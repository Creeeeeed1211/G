#ifndef HELPERS_HPP_DD37133A_D9CE_4998_AA48_41DA09E1517C
#define HELPERS_HPP_DD37133A_D9CE_4998_AA48_41DA09E1517C

#include "../draw2d/forward.hpp"
#include "../draw2d/surface.hpp"
#include "../draw2d/draw.hpp"
#include <cmath>


ColorU8_sRGB find_most_red_pixel( Surface const& );
ColorU8_sRGB find_least_red_nonzero_pixel( Surface const& );
ColorU8_sRGB get_pixel_color(Surface const& surface, Surface::Index x, Surface::Index y);
// Declaration with a default argument
//bool colors_are_approximately_equal(ColorU8_sRGB color1, ColorU8_sRGB color2, int tolerance = 5);
//bool colors_are_approximately_equal(const ColorU8_sRGB& color1, const ColorU8_sRGB& color2, float tolerance = 0.1f);

ColorU8_sRGB interpolate_colors(const ColorU8_sRGB& c1, const ColorU8_sRGB& c2, float t);

#endif // HELPERS_HPP_DD37133A_D9CE_4998_AA48_41DA09E1517C
