#include "thumbNail.h"

#include <iostream>

apThumbNail::apThumbNail()
{}

apThumbNail::~apThumbNail() 
{}

void apThumbNail::createThumbNail(const char* inputFile, const char* outputFile, int factor)
{
	// Validate the arguments
	if (inputFile == 0 || outputFile == 0 || factor <= 1)
		throw invalid();

	// Read the source image
	readImage(inputFile);
	if (!image_.isValid())
		throw invalid();

	// Create our internal thumbnail image
	thumbnail_ = apImage(image_.width() / factor, image_.height() / factor);

	// Turn any rangeErrors from apImage into our invalid error
	unsigned char pixel;
	try {
		for (int y = 0; y < thumbnail_.height(); y++) {
			for (int x = 0; x < thumbnail_.width(); x++) {
				// Convert to image_ coordinates to find the average
				pixel = averagePixels(x*factor, y*factor, factor);
				thumbnail_.setPixel(x, y, pixel);
			}
		}
	} 
	catch(apImage::rangeError) {
		throw invalid();
	}

	writeImage(outputFile);
}

// private:

void apThumbNail::readImage(const char* /* inputFile */ )
{
	image_ = apImage(64, 64);
	try {
		for (int y = 0; y < image_.height(); y++) {
			for (int x = 0; x < image_.width(); x++) {
				image_.setPixel(x, y, (unsigned char)(y % 255));
			}
		}
	} 
	catch(apImage::rangeError) {
		throw invalid();
	}
}

void apThumbNail::writeImage(const char* /* outputFile */ ) const
{
	// Save formatting state for stream
	std::ios_base::fmtflags  flags = std::cout.flags(std::cout.hex);
	int width = std::cout.width(2);

	for (int y = 0; y < thumbnail_.height(); y++) {
		for (int x = 0; x < thumbnail_.width(); x++) {
			std::cout << (int)thumbnail_.getPixel(x,y) << " ";
		}
		std::cout<<std::endl;
	}
	std::cout.flags(flags);
	std::cout.width(width);
}

unsigned char apThumbNail::averagePixels(int x0, int y0, int factor)
{
	int sum = 0;
	
	// Average factor x factor pixels in the input image
	try {
		for (int y = 0; y < factor; y++) {
			for (int x = 0; x < factor; x++) {
				sum += image_.getPixel(x+x0, y+y0);
			}
		}
	}
	catch (apImage::rangeError) {
		throw invalid();
	}

	// This cast (an int to an unsigned char) is very safe
	return static_cast<unsigned char>(sum / (factor*factor));
}


