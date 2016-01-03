#ifndef _IMAGE8_H_
#define _IMAGE8_H_

#include "allocTmpl.h"

typedef unsigned char Pel8;

class apImage8
{
public:
	apImage8();
	apImage8(int width, int height);
	// Create a null image, o the specified size
	
	virtual ~apImage8();

	int width() const { return width_; }
	int height() const { return height_; }

	const Pel8* pixels() const { return pixels_.data(); }
	Pel8* pixels() { return pixels_.data(); }	
	// Return pointer to start of pixel data
	
	Pel8 getPixel (int x, int y) const;
	void setPixel(int x, int y, Pel8 pixel);
	// Get/set a signle pixel
	
	// Image operations (only one for the prototype)
	virtual apImage8 thumbnail (unsigned int reduction) const;

	// Default copy ctor and assignment are ok
protected:
	apAlloc<Pel8> pixels_; // Pixel data
	int width_; // Image dimensions
	int height_;
};

typedef unsigned int Pel32;

class apImage32
{
public:
	apImage32();
	apImage32(int width, int height);
	// Creates a null image, or the specified size
	
	virtual ~apImage32();

	int width() const { return width_; }
	int height() const { return height_; }

	const Pel32* pixels () const { return pixels_.data(); }
	Pel32* pixels() { return pixels_.data(); }
	// Return pointer to start of pixel data
	
	Pel32 getPixel(int x, int y) const;
	void setPixel(int x, int y, Pel32 pixel);
	// Get/set a single pixel
	
	// Image operations (only one for the prototype)
	virtual apImage32 thumbnail(unsigned int reduction) const;

	// Default copy ctor and assignment are ok
protected:
	apAlloc<Pel32> pixels_; // Pixel data
	int width_;	// Image dimensions
	int height_;
};

#endif // _IMAGE8_H_
