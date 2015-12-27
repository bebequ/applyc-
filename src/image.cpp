#include "image.h"

#include <memory.h>

apImage::apImage() : width_(0), height_(0), pixels_(0) 
{}

apImage::apImage(int width, int height) : width_(width), height_(height), pixels_ (0)
{
	init();
}

apImage::~apImage() 
{
	cleanup();
}

apImage::apImage(const apImage& src) : width_(0), height_(0), pixels_(0)
{
	if (src.isValid()) {
		width_ = src.width();
		height_ = src.height();
		init();
		memcpy(pixels_, src.pixels_, width_ * height_);
	}
}

template<class T> void swap(T& a, T&b)
{
	T copy(a);
	a = b;
	b = copy;
}

apImage& apImage::operator=(const apImage& src)
{
	/*
	if (&src != this) {
		// Delete any existing data and recreate the source image
		cleanup();
		width_ = sr.width();
		height_ = src.height();
		init();

		memcpy(pixels_, src.pixels_, width, height_);
	}
	return *this;
	*/
	apImage temp(src);
	swap(temp);
	
	return *this;
}

void apImage::swap(apImage& src)
{
	::swap(width_, src.width_);
	::swap(height_, src.height_);
	::swap(pixels_, src.pixels_);
}

void apImage::setPixel(int x, int y, unsigned char pixel)
{
	if (x < 0 || y < 0 || x >= width_ || y >= height_ || isValid() ) 
		throw rangeError();
	unsigned char* p = pixels_ + y*width_ + x;
	*p = pixel;
}

unsigned char apImage::getPixel(int x, int y) const 
{
	if ( x < 0 || y < 0 || x >= width_ || y >= height_ || isValid() ) 
		throw rangeError();
	// Image data is stored a row at a time.
	unsigned char* p = pixels_ + y*width_ + x;
	return *p;
}

// private
void apImage::init()
{
	// All memory allocation passes through this function
	if (width_ > 0 && height_ > 0) {
		pixels_ = new unsigned char [width_ * height_];
	}
}

void apImage::cleanup()
{
	// Put the object back into its original, null state.
	delete [] pixels_;

	width_ = 0;
	height_ = 0;
	pixels_ = 0;
}
