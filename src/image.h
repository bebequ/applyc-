#ifndef _IMAGE_H_
#define _IMAGE_H_

/**
 * @file image.h
 * @brief This is the class header file for apImage
 * @author Jin Park
 * @date 2015-12-27
 */

#include <stdio.h>

class apImage
{
public:
	apImage ();
	apImage (int width, int height);
	~apImage();

	apImage (const apImage& src);
	apImage& operator= (const apImage& src);

	void swap(apImage& src);
	
	/** setPixel function
	 * @param x, y */
	void setPixel(int x, int y, unsigned char pixel);
	
	/** getPixel function
	 * @param x, y
	 * @return the pixel of x, y */
	unsigned char getPixel(int x, int y) const;

	bool isValid() const { return pixels_ != 0; }
	// Tests if the image data exists, and presumably valid.
	
	int width() const { return width_; } // Image width
	int height() const { return height_; } // Image height

	class rangeError{}; // Exception class

private:
	void init();
	void cleanup();
	// Initialize or cleanup the allocated image data
	
	int width_; // Image width
	int height_; // Image height
	unsigned char* pixels_; // Image data
};

#endif // _IMAGE_H_
