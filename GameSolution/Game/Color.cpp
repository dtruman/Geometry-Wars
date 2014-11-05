#include "Color.h"
#include "Core.h"

using Core::RGB;

RGB Colorness::varyColor(RGB color, int variance)
{
	r=GetRValue(color);
	r=r+variance+(int)(myRand.randomInRange(-(float)variance,variance+1.0f));
	if(r<0)
		r=0;
	if(r>MAX_COLOR)
		r=MAX_COLOR;
	g=GetGValue(color);
	g=g+variance+(int)(myRand.randomInRange(-(float)variance,variance+1.0f));
	if(g<0)
		g=0;
	if(g>MAX_COLOR)
		g=MAX_COLOR;
	b=GetBValue(color);
	b=b+variance+(int)(myRand.randomInRange(-(float)variance,variance+1.0f));
	if(b<0)
		b=0;
	if(b>MAX_COLOR)
		b=MAX_COLOR;

	return RGB(r,g,b);
};

RGB Colorness::Brightness(RGB color, float brightValue)
{
	r=int(GetRValue(color)*brightValue);
	if(r<0)
		r=0;
	if(r>MAX_COLOR)
		r=MAX_COLOR;
	g=int(GetGValue(color)*brightValue);
	if(g<0)
		g=0;
	if(g>MAX_COLOR)
		g=MAX_COLOR;
	b=int(GetBValue(color)*brightValue);
	if(b<0)
		b=0;
	if(b>MAX_COLOR)
		b=MAX_COLOR;

	return RGB(r,g,b);
};