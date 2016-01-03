#include "timing.h"

/**
 * @brief : apElapsedTime
 *
 *
 */
apElapsedTime::apElapsedTime() : starting_(0)
{
	reset();
}

double apElapsedTime::sec() const
{
	clock_t current = clock();
	return ((double)(current - starting_) / CLOCKS_PER_SEC);
}

void apElapsedTime::reset()
{
	starting_ = clock();
}
