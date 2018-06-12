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
## Abstract Data Types / Linked List virtual Class example
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
![enter image description here](https://i.gyazo.com/347a00e3e1b97ebc624878d06dd4fa75.png)
![enter image description here](https://i.gyazo.com/3fa4c67b516d93249d0fcc5496797ca5.png)
## Destructors
e.g. `~intLinkedList()`
- a special method that is run when an object has the special `delete` operator called on it
```C++
delete [pointer to thing to delete]
delete[] [array variable] // because arrays are a pointer, so this works the same way
```
- `delete` is required when we've created something with `new`
	- Otherwise heap memory is not deallocated, and we have a memory leak.
## Exceptions
C++ has a try/catch implementation
```C++
try {
	throw 20;
} catch (int e) {
	// print error here
}
```
## Compiling with multiple files
Just list all other cpp files after the main.cpp `g++ main.cpp other.cpp etc.cpp`
can also use `g++ *.cpp -o output`
## Queue
- A FIFO (First-in-first-out) data structure
- Can only be added to the back
- Can only be taken off the front
- Unbounded capacity (normally)
```C++
class intQueue {
public:
	virtual ~intQueue() {};
	virtual void enqueue(int n) = 0;
	virtual int dequeue() = 0;
	virtual int peek() = 0;
};
```
### Other Queues
- A Deque (double-ended queue). Can add and remove at both ends
- Priority Queue is a queue, but elements are inserted with a priority, and come out in priority order.
## Stacks
- A LIFO (Last-in-first-out) data structure
- Add from the top
- Remove from the top
```C++
class intStack {
public:
	virtual ~intStack() {};
	virtual void push() = 0;
	virtual int pop() = 0;
	virtual int peek() = 0;
}; 
```
# Week 3 - Vectors, Templates, Iterators, Big-Oh
## Vector Class
`std::vector<T>`
- Dynamically size arrays

**ADD MORE HERE maybe even from cpp reference**
## Templates
- A good way to write certain types of code once, if the code doesn't care about the types it is working with
- We can make a `std::vector<int>`, or even a `std::vector<char>`.
Within classes:
- Make sure to add a `template <typename T>` before using templates within a class
```C++
template <typename T> 
class node {
  private:
    T data;
    node *next;
}
```
## Iterators
**CPP REFERENCES**
## Asymptotic Notations
- **O (Big-Oh) Notation:** The upper bound of an algorithm
- **Θ (Theta) Notation:** Bounds a function from above and below, defines exact asymptotic behaviou
- **Ω (Omega) Notation:** Asymptotic lower bound
## Big-Oh Notation
Comparing two functions f and g:

![enter link description here](https://i.gyazo.com/fc4ff0a9f983483bbd8cc893a75a9f3e.png)
- This helps us as we can now compare and decide which function is the fastest (in its worst case scenario)
- "One of the algorithm's running time will be larger for large enough inputs"
### Big-Oh Rules

![](https://i.gyazo.com/569cfaccdd551447aba589987ed0d680.png)
### Big-Oh Names

![](https://i.gyazo.com/5e872a4d38e5fb27f3ac50d0c8b5deff.png)
### How to get the functions
Count the number of steps

![](https://i.gyazo.com/4f15f77ded60d95d74164769e3d9b3e7.png)
### Other Properties

![](https://i.gyazo.com/fb076668f27d6330bceee0570649eaf6.png)

# Week 4 - Divide and Conquer, Recursion, Iteration
