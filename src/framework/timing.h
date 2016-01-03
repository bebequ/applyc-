#ifndef _TIMING_H_
#define _TIMING_H_

#include <time.h>

/**
 * @brief : apElapsedTime
 *
 */
class apElapsedTime
{
public:
	apElapsedTime();
	// Record the current time
	
	double msec() const { return sec() * 1000; }
	double sec() const;
	// Return elapsed time, in milliseconds or sec
	
	void reset();
	// Reset the current time
	
private:
	clock_t starting_; // Starting time
};

#endif // _TIMING_H_
