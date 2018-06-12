# 31251-data-structures-algorithms Notes
# Week 1 - Strings, Arrays, Pointers, Classes
## Strings
- In C – Null terminated char arrays
- C++ has a proper string class (`std::string`) that acts as a wrapper for `char[]`
- C++11, null_ptr type exists, before that pointers were either just 0, or something that looks like it
## Static and Dynamic Allocation
- Things can be statically allocated: 
	- They are automatically deallocated when they go out of scope. 
	- What does this mean for return data? 
- Or dynamically allocated: 
	- Created on the heap with the `new` keyword. 
	- C++ has no garbage collection, so you have to manage it yourself. 
- Don’t use `new` unless you mean it!
## Arrays
```C++
int a[4] = {1,2,3,4};
int a[] = {1,2,3,4};
int a[4] = {};
int a[4];
```
- Arrays are statically created
- We also need to declare a size. (Which is bad most of the time).
- `std::vector` helps with this.
- Arrays can be treated as pointers e.g. `int[] = int*`
## Pointers
- A pointer is an object that refers to another object

![px = &x](https://gyazo.com/85b731ecf986c7087c77bc0d5563798b.png)
```C++
double* px; // initialise a pointer
double x = 5.1234
px = &x;   // setting a pointer to the memory address of an object
*px; // obtains the value pointed to by the pointer (dereferencing)
(*px).bar = px->bar // arrow notation can be used to access 
```
## References
- A reference variable is used to give a name to an object. It refers to the same object. 
```C++
int& rx = x; // references x, so if you change the value in rx, it also changes x
```
- Useful for when passing a value into a function by reference
```C++
void do_something_cool(int& x) {
	x = x + 1;
}
int y = 1;
do_something_cool(y); // y now equals 2
```
## Classes
```C++
Class myClass : public parentClass {
private: 
	int private_int;
public:
	int getPrivateInt();
	void setPrivateInt(int value);
	string toString();
}
```
C++ Separates definitions from source code
- Definitions are placed in a header file (`.h, .hpp` etc.)
- Source Code is in source files (`.cpp` etc.)
- Code can also be placed entirely in the header file
## Abstract Data Types
- Don’t specify implementations, are just specifications of behaviour of Data Types (Same as an `interface` and `abstraction`)
```C++
Class intList {
public: 
	virtual ~intList() {};
	virtual bool isEmpty() = 0;
	virtual void prepend(int c) = 0;
	virtual int head() = 0;
	virtual intList tail() = 0;
}
```
# Week 2 - I/O, Destructors, Stacks, Queues
## cin and cout
```C++
int n;
std::cout << “Enter a number!” << std::endl();
std::cin >> n;
```
To get an entire line: 
`std::getline(std::cin, [variable to read into]);`
`std::err` can be used to output errors
## File I/O
