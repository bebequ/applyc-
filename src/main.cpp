#include "thumbnail.h"

#include <iostream>

int main()
{
	apThumbNail thumbnail;

	try {
		thumbnail.createThumbNail("input.bmp", "outoput.bmp", 2);
	}
	catch (apThumbNail::invalid) {
		std::cerr << "invalid exception caught" << std::endl;
		return 1;
	}

	return 0;
}

