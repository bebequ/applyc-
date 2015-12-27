#ifndef _THUMBNAIL_H_
#define _THUMBNAIL_H_

#include "image.h" 

class apThumbNail
{
public:
	apThumbNail();
	~apThumbNail();

	// The defauult copy constructor and assignment operator are ok
	
	void createThumbNail(const char* inputFile, const char* outputFile, int factor);

	class invalid {}; // Exception class

private:
	void readImage(const char* inputFile);
	void writeImage(const char* outputFile) const;
	unsigned char averagePixels(int x0, int y0, int factor);

	apImage image_; // input image
	apImage thumbnail_; // thumbnail image
};

#endif // _THUMBNAIL_H_
