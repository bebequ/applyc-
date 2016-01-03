#include "image.h"

apImage8::apImage8() : width_(0), height_(0)
{}

apImage8::apImage8(int width, int height)
: width_(width), height_(height)
{
	pixels_ = apAlloc<Pel8>(width*height);
}

apImage8::~apImage8()
{}

// Just a prototype so no error checking on coordinates
Pel8 apImage8::getPixel(int x, int y) const
{
	return pixels_[y*width_ + x];
}

void apImage8::setPixel(int x, int y, Pel8 pixel)
{
	pixels_[y*width_ + x] = pixel;
}

// Each pixel in the output image is the average of a block
// of pixels in the current image
apImage8 apImage8::thumbnail(unsigned int reduction) const
{
	apImage8 output(width()/reduction, height()/reduction);

	for(unsigned int ty = 0; ty<output.height(); ty++) {
		for(unsigned int tx = 0; tx < output.width(); tx++) {
			unsigned int sum = 0;
			for( unsigned int y = 0; y < reduction; y++) {
				for( unsigned int x = 0; x < reduction; x++) {
					sum += getPixel(tx*reduction + x, ty*reduction + y);
				}
			}
			output.setPixel(tx, ty, static_cast<Pel8>(sum / (reduction*reduction)));
		}
	}
	return output;
}

/**
 * @brief apImage32
 *
 *
 */
apImage32::apImage32() : width_(0), height_(0)
{}

apImage32::apImage32(int width, int height)
: width_ (width), height_ (height)
{
	pixels_ = apAlloc<Pel32>(width*height);
}

apImage32::~apImage32()
{}

// Just a prototype so no error checking an coordinates
Pel32 apImage32::getPixel(int x, int y) const
{
	return pixels_[y*width_ + x];
}

void apImage32::setPixel(int x, int y, Pel32 pixel)
{
	pixels_[y*width_ + x] = pixel;
}

// Each pixel in the outpout image is the average of a block
// of pixel in the current image
apImage32 apImage32::thumbnail(unsigned int reduction) const
{
	apImage32 output(width()/reduction, height()/reduction);

	for(unsigned int ty = 0; ty < output.height(); ty++) {
		for(unsigned int tx = 0; tx < output.width(); tx++) {
			unsigned int sum = 0;
			for(unsigned int y =0; y < reduction; y++){
				for(unsigned int x = 0; x < reduction; x++) {
					sum += getPixel(tx*reduction + x, ty*reduction + y);
				}
			}
			output.setPixel(tx, ty, sum / (reduction*reduction));
		}
	}

	return output;
}


