#ifndef _LOCK_H_
#define _LOCK_H_

class apLock
{
public:
	apLock() {}
	~apLock() {}

	bool lock() { return true; } // Get the lock
	bool unlock() { return true; } // Release the lock
};

class apLocker
{
public:
	apLocker (apLock& lock) : lock_ (lock) { lock_.lock(); }
	~apLocker() { lock_.unlock(); }

private:
	apLock& lock_;

	// Prohibit copy and assignment
	apLocker (const apLocker& src);
	apLocker& operator=(const apLocker& src);
};

#endif // _LOCK_H_
