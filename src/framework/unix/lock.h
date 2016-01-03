#ifndef _UNIX_LOCK_H_
#define _UNIX_LOCK_H_

#include <pthread.h>

class apMutexAttribute
{
public:
	static apMutexAttribute& gOnly();

	pthread_mutexattr_t* value() { return &attr_; }

private:
	static apMutexAttribute* sOnly_;

	pthread_mutexattr_t attr_;

	apMutexAttribute();
	~apMutexAttribute();
};

/**
 *
 *
 */
class apLock
{
public:
	apLock()
	{
		pthread_mutex_init(&lock_, apMutexAttribute::gOnly().value());
	}
	~apLock() { pthread_mutex_destroy(&lock_); }

	apLock (const apLock&)
	{
		pthread_mutex_init( &lock_, apMutexAttribute::gOnly().value());
	}

	apLock& operator= (const apLock&) { return *this; }

	// Get the lock
	bool lock() const
	{ return pthread_mutex_lock(&lock_) == 0; }

private:
	mutable pthread_mutex_t lock_;
};

#endif // _UNIX_LOCK_H_
