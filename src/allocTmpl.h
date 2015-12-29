#ifndef _ALLOCTMPL_H_
#define _ALLOCTMPL_H_

#include "lock.h"

#include <stdexcept>
#include <algorithm>

// Disable warings about unreferenced local functions (clone())
#ifdef WIN32
#pragma warning(disable:4505)
#endif

#ifdef NEEDS_UINTPTR_T
typedef int uintptr_t
#endif

template<class T> class apAllocatorBase_
{
public:
	apAllocatorBase_ (unsigned int n, unsigned int align)
		: pRaw_(0), pData_(0), ref_(0), size_(n), align_(align)
	{}
	// Derived classes will allocate memory but we store the relevant
	// details in the base class.
	
	virtual ~apAllocatorBase_ () {}
	// Derived classes will deallocate 
	
	bool lock () const { return lock_.lock(); }
	bool unlock() const { return lock_.unlock(); }
	// Allow clients access to our lock
	
	operator T* () { return pData_; }
	operator const T* () const { return pData_; }
	// Conversion to pointer of allocated memory type
	
	unsigned int size () const { return size_; } // Number of elements
	unsigned int ref () const { return ref_; } // Number of references
	unsigned int align () const { return align_; } // Alignment

	void addRef () { lock(); ref_++; unlock(); }
	void subRef() 
	{
		lock(); --ref_; unlock();
		if (ref_ == 0) delete this;
	}
	// Increments or decrement the reference count.
	
protected:
	virtual void allocate () = 0;
	virtual void deallocate() = 0;
	// Pure virtual functions that derived classes provide to
	// allocate/deallocate memory.
	
	T* alignPointer(void* raw)
	{
		T* p = reinterpret_cast<T*>(
			(reinterpret_cast<uintptr_t>(raw) + align_ - 1)
			& ~(align_ - 1));
		return p;
	}
	// Align the specified pointer to match our alignment and make it 
	// a T* pointer. We cast to a uintptr_t to perform the
	// alignment and then we cast it to T*.
	
	apAllocatorBase_ (const apAllocatorBase_& src);
	apAllocatorBase_& operator= (const apAllocatorBase_& src);
	// No copy or assignment is allowed.
	
	char* pRaw_; // Raw allocated pointer
	T* pData_; // Aligned pointer to our memory
	unsigned int size_; // Number of elements allocated
	unsigned int ref_; // Reference count
	unsigned int align_; // Memory alignment (modulus)

	mutable apLock lock_; // Syncronization lock for accessing memory
};

template<class T> class apAllocator_ : public apAllocatorBase_<T>
{
public:
	explicit apAllocator_ (unsigned int n, unsigned int align = 0)
		: apAllocatorBase_<T>(n, align)
	{
		// A call to allocate() must be wriiten as this->allocate() because of
		// recent changes to gcc (since 3.4 a two-stage name lookup is used)
		this->allocate();
		this->addRef();
	}

	virtual ~apAllocator_() { deallocate(); }

private:
	virtual void allocate()
	{
		if(this->size_ == 0) {
			// Eliminate possibility of null pointers by allocating
			// 1 item.
			this->pData_ = new T[1];
			this->pRaw_ = 0;
			return;
		}

		if (this->align_ < 2) {
			// Let the compiler worry about any alignment
			this->pData_ = new T[this->size_];
			this->pRaw_ = 0;
		} else {
			// Allocate additional bytes to guarantee alignment
			// Then align and cast to our desired data type.
			this->pRaw_ = new char[sizeof(T) * this->size_ + (this->align_ - 1)];
			this->pData_ = alignPointer(this->pRaw_);
		}
	}
	// Allocate our memory for size_ elements of type T with the
	// alignment specified by align_. 0 and 1 specify no alignment,
	// 2 = word alignment, 4 = double-word alignment, ... This must
	// be a power of 2.
	
	virtual void deallocate ()
	{
		// Decide which pointer we delete
		if(this->pRaw_)
			delete[] this->pRaw_;
		else
			delete[] this->pData_;
		this->pRaw_ = 0;
		this->pData_ = 0;
	}

	apAllocator_ (const apAllocator_& src);
	apAllocator_& operator= (const apAllocator_& src);
	// No copy or assignment is allowed.
};

/**
 * @breif apAlloc class definition
 *
 */
template<class T, class A = apAllocator_<T> >
class apAlloc
{
public:
	static apAlloc& gNull();
	// We return this object for any null allocations
	// It actually allocates 1 byte to make all the member
	// functions valid.
	
	apAlloc();
	// Null allocation. Returns pointer to gNull() memory
	
	explicit apAlloc(unsigned int size, unsigned int align = 0);
	~apAlloc();
	// Allocate the specified bytes, with the correct alignment.
	// 0 and 1 specify no alignment. 2 = word alignment,
	// 4 = double-world alignment. Must be a power of 2.
	
	apAlloc (const apAlloc& src);
	apAlloc& operator= (const apAlloc& src);
	// We need our own copy constructor and assignment operator.
	
	unsigned int size() const { return pMem_->size(); }
	unsigned int ref() const { return pMem_->ref(); }
	bool isNull() const { return (pMem_ == gNull().pMem_);}

	bool lockStorage () const { return pMem_->lock(); }
	bool unlockStorage() const { return pMem_->unlock(); }
	// Allow clients access to our lock
	
	const T* data() const { return *pMem_; }
	T* data() { return *pMem_; }
	// Access to the beginning of our memory regin. Use sparingly
	
	const T& operator[] (unsigned int index) const;
	T& operator[] (unsigned int index);
	// Access a specific element. Throws the STL range_error if
	// index is invalid.
	
	virtual A* clone();
	// Duplicate the memory in the underlying apAllocator.
	// Derived classes can override this to perform their own
	// clone, if shallow copying is not sufficient. It T
	// specifies an object that cannot be bliendly copied, you will
	// need to override this function.
	
	void duplicate();
	// Breaks any reference counting and forces this object to
	// have tis own copy.
	
protected:
	A* pMem_; // Pointer to our allocated memory
	
	static apAlloc* sNull_; // Our null object
};

template<class T, class A>
apAlloc<T,A>* apAlloc<T,A>::sNull_ = 0;

template<class T, class A>
apAlloc<T,A>& apAlloc<T,A>::gNull()
{
	if(!sNull_)
		sNull_ = new apAlloc(0);
	return *sNull_;
}

template<class T, class A>
apAlloc<T, A>::apAlloc() : pMem_(0)
{
	// Pointer ourself to sNull. We can't do an assignment in the
	// constructor since it will try to deallocate something
	// that doesn't exist.
	pMem_ = gNull().pMem_;
	pMem_->addRef();
}

template<class T, class A>
apAlloc<T,A>::apAlloc(unsigned int size, unsigned int align)
	: pMem_(0)
{
	pMem_ = new A(size, align);
}

template<class T, class A>
apAlloc<T,A>::~apAlloc()
{
	pMem_->subRef();
}

template<class T, class A>
apAlloc<T,A>::apAlloc(const apAlloc& src)
{
	src.lockStorage();
	pMem_ = src.pMem_;
	pMem_->addRef();
	src.unlockStorage();
}

template<class T, class A>
apAlloc<T, A>& apAlloc<T,A>::operator=(const apAlloc& src)
{
	// Make sure we don't copy ourself!
	if (pMem_ == src.pMem_)
		return *this;

	// Remove reference from existing object. addRef() and subRef()
	// do not throw so we dont' have to woory about catching an error
	pMem_->subRef();
	src.lockStorage();
	pMem_ = src.pMem_;
	pMem_->addRef(); // Add reference to our new object
	src.unlockStorage();

	return *this;
}

template<class T, class A>
const T& apAlloc<T,A>::operator[](unsigned int index) const
{
	if(index >= size())
		// Throw a standard STL exception
		throw std::range_error("Index out of range");

	return *(data() + index);
}

template<class T, class A>
T& apAlloc<T,A>::operator[] (unsigned int index)
{
	if (index >= size() )
		// Throw a standard STL exception
		throw std::range_error("Index out of range");

	return *(data() + index);
}

template<class T, class A>
A* apAlloc<T,A>::clone()
{
	lockStorage();

	A* copy = new A (pMem_->size(), pMem_->align());

	// Shallow copy
	T* src = *pMem_;
	T* dst = *copy;
	std::copy(src, &(src[pMem_->size()]), dst);

	unlockStorage();
	return copy;
}

template<class T, class A>
void apAlloc<T,A>::duplicate()
{
	if (ref() == 1) {
		return; // No need to duplicate
	}

	// Duplicate our existing memory
	A* copy = clone();

	pMem_->subRef(); // Remove reference from existing object;
	pMem_ = copy; // Replace it with our duplicated data
}

#endif // _ALLOCTMPL_H_



