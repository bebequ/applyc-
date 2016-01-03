#ifndef _FRAMEWORK_H_
#define _FRAMEWORK_H_

#include <vector>
#include <iostream>

/**
 * @brief : apUinitTestFunction is the base class for all uni test functions.
 *
 */

class apUnitTestFunction
{
public:
	apUnitTestFunction( const std::string& name);

	enum eResult { eNotRun, eRunning, eUnknown, eSuccess, eFailure };
	// Each unit test has a result, even if the user never sets it
	
	const std::string& name () const { return name_; }
	eResult result () const { return result_; }
	double elapsed () const { return elapsed_; }
	const std::string& message () const { return message_; }
	const std::string& description () const { return description_; }
	std::string resultString() const;

	void setDescription (const std::string& s) { description_ = s; }
	// Set the description of this test function
	
	void run (bool verbose = false);
	// Run this unit test. Called by the unit test framework
	
protected:
	virtual void test() = 0;
	// All unit tests define this function to perform a single test
	
	bool verify (bool state, const std::string& message="");
	// Fails test if state is fales. Used by VERIFY() macro
	
	bool verifyFloat (double d1, double d2);
	// Verifies d1=d2, within a value delta. Used by VERIFYFLOAT()
	
	void addMessage (const std::string& message);
	// Adds the message string to our message
	
	bool verbose_; // true for verbose output

	eResult result_; // Result of this unit test
	std::string name_; // Unit test name (must be unique)
	std::string description_; // Description of function
	std::string message_; // Message, usual a failure message
	double elapsed_; // Execution time, in seconds
};

/**
 * @brief : apUnitTest
 *
 */
class apUnitTest
{
public:
	static apUnitTest& gOnly();
	// The only instance of this object we create
	
	bool run(bool verbose = false);
	// Run all the unit tests. Returns true if all tests are ok
	
	void dumpResults (std::ostream& out);
	// Dump results to specified stream
	
	int size() const { return static_cast<int>(tests_.size()); }
	const apUnitTestFunction* retrieve (int index) const;
	// Retrieves the specific test, or NULL if invalid index
	
	void addTest (const std::string& name, apUnitTestFunction* test);
	// Used by our macro to add another unit test
	
private:
	apUnitTest(); // We will only have one instance, gOnly()

	static apUnitTest* sOnly_; // Points to our only instance

	std::vector<apUnitTestFunction*> tests_; // Array of tests
	time_t start_, stop_; // Start, stop time

};

#define UTFUNC(utx)								\
class UT##utx : public apUnitTestFunction		\
{												\
	UT##utx();									\
	static UT##utx sInstance;					\
	void test();								\
};												\
UT##utx UT##utx::sInstance;						\
UT##utx::UT##utx() : apUnitTestFunction(#utx)	\
{												\
	apUnitTest::gOnly().addTest(#utx, this);	\
}												\
void UT##utx::test()							

#define VERIFY(condition) verify(condition, #condition)
#define VERIFYFLOAT(d1, d2) verifyFloat(d1, d2)

#endif // _FRAMEWORK_H_
