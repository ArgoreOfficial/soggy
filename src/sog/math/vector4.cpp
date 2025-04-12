#include "vector4.h"

#include <sog/math.h>

sog::vec4::rgba8_t::operator uint32_t()
{
	union { struct { uint8_t r, g, b, a; }; uint32_t i; } c;

	c.r = x * 255;
	c.g = y * 255;
	c.b = z * 255;
	c.a = w * 255;

	return c.i;
}

sog::vec4::bgra8_t::operator uint32_t()
{
	union { struct { uint8_t r, g, b, a; }; uint32_t i; } c;

	c.r = sog::clamp( z, 0.0f, 1.0f ) * 255;
	c.g = sog::clamp( y, 0.0f, 1.0f ) * 255;
	c.b = sog::clamp( x, 0.0f, 1.0f ) * 255;
	c.a = sog::clamp( w, 0.0f, 1.0f ) * 255;

	return c.i;
}


