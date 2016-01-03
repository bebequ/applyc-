#include "unix/lock.h"

apMutexAttribute* apMutexAttribute::sOnly_ = 0;

apMutexAttribute& apMutexAttribute::gOnly()
{
	if(!sOnly_)
		sOnly_ = new apMutexAttribute();
	return *sOnly_;
}

apMutexAttribute::apMutexAttribute()
{
	pthread_mutexattr_init(&attr_);
	pthread_mutexattr_settype(value(), PTHREAD_MUTEX_RECURSIVE);
}

apMutexAttribute::~apMutexAttribute()
{
	pthread_mutexattr_destroy(&attr_);
}

