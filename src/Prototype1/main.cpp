#include "image.h"
#include "unitTest.h"

#include <iostream>

UTFUNC(image8)
{
	unsigned int x, y;

	setDescription("apImage8");

	apImage8 p1;
	VERIFY(p1.width() == 0);
	VERIFY(p1.height() == 0);

	apImage8 p2(640, 480);
	VERIFY(p2.width() == 640);
	VERIFY(p2.height() == 480);

	// Test pixels() and getPixel()
	memset(p2.pixels(), 0x5a, 640*480);
	for(y=0; y<p2.height(); y++)
		for(x=0; x<p2.width(); x++)
			VERIFY(p2.getPixel(x,y) == 0x5a);
	
	// Test setPixel() and getPixel()
	Pel8 pel = 0;
	for(y=0; y<p2.height(); y++)
		for(x=0; x<p2.width(); x++)
			p2.setPixel(x,y, pel++);

	pel = 0;
	for(y=0; y<p2.height(); y++)
		for(x=0; x<p2.width(); x++)
			VERIFY(p2.getPixel(x,y) == pel++);
}

UTFUNC(thumbnail)
{
	unsigned int x, y;

	setDescription("apImage8 thumbnail");

	apImage8 p(32, 32);
	VERIFY(p.width() == 32);
	VERIFY(p.height() == 32);

	// Set the data
	Pel8 pel = 0;
	for (y=0; y<p.height(); y++)
		for (x=0; x<p.width(); x++)
			p.setPixel(x,y,pel++);

	apImage8 thumbnail = p.thumbnail(2);

	for(y=0; y<thumbnail.height(); y++) {
		for(x=0; x<thumbnail.width(); x++) {
			pel = (p.getPixel(2*x, 2*y) + 
				   p.getPixel(2*x, 2*y +1) +
				   p.getPixel(2*x+1, 2*y) +
				   p.getPixel(2*x+1, 2*y+1))/4;
			VERIFY(thumbnail.getPixel(x,y) == pel);
		}
	}
}

UTFUNC(image32)
{
	unsigned int x, y;

	setDescription("apImage32");

	apImage32 p1;
	VERIFY(p1.width() == 0);
	VERIFY(p1.height() == 0);

	apImage32 p2(640, 480);
	VERIFY(p2.width() ==  640);
	VERIFY(p2.height() == 480);

	// Test pixels() and getPixel()
	Pel32 pel = 0;
	for(y=0; y<p2.height(); y++)
		for(x=0; x<p2.width(); x++)
			p2.setPixel(x,y,pel++);
	pel = 0;
	for (y= 0; y<p2.height(); y++)
		for (x=0; x<p2.width(); x++)
			VERIFY(p2.getPixel(x,y) == pel++);
}

UTFUNC(thumbnail32)
{
	unsigned int x, y;

	setDescription("apImage32 thumbnail");

	apImage32 p(32, 32);
	VERIFY(p.width() == 32);
	VERIFY(p.height() == 32);

	// Set the data
	Pel32 pel = 0;
	for(y=0; y<p.height(); y++)
		for(x=0; x<p.width(); x++)
			p.setPixel(x, y, pel++);

	apImage32 thumbnail = p.thumbnail(2);

	for(y=0; y<thumbnail.height(); y++) {
		for (x=0; x<thumbnail.width(); x++) {
			pel = (p.getPixel(2*x, 2*y) + 
				   p.getPixel(2*x, 2*y+1) +
				   p.getPixel(2*x, 2*y) + 
				   p.getPixel(2*x+1, 2*y+1))/4;
			VERIFY(thumbnail.getPixel(x,y) == pel);
		}
	}
}

// Our main function is trivial
int main()
{
	bool state = apUnitTest::gOnly().run();
	apUnitTest::gOnly().dumpResults(std::cout);

	return state;
}
