
# Week 1 - Introduction and Simple C++ Concepts
## What is an Algorithm
An algorithm is:
- a well defined computational process that takes some **input** and produces and **output**
## What is a Data Structure
A data structure is a way to store and organise data. It can also be seen as a special type of algorithm.
## Strings
Strings in C are *null terminated* char arrays. In C++ however, there is an added implementation of a proper string class (`std::string`) that acts as a wrapper for `char[]`, as well as fixing issues when dealing with null termination
### Null Pointers
In C++ a null value is actually just 0 (or something that looks like it)
Since C++11 an actual null_ptr type exists, which means you're able to have a proper null (similar to C) that isn't just 0.
## Memory Allocation
[*] NB: C++ Standard does not specify where to allocate dynamic or static memory
### Static Allocation
Declaring a static variable is usually placed onto the stack (usually*). 
The variable will *die* at the end of the code block in which it is defined (they will be automatically deallocated).
### Dynamic Allocation
Dynamically allocating a variable will be usually placed onto the heap (usually*).
C++ does not contain any garbage collection, which means the variable will no longer be automatically deallocated, and you will have to decide where to deallocate it using the `delete` keyword.
- BIG MUST: The `delete` MUST be used if you dynamically allocate memory.
```C++
int* arr = new int[5];
[...]
delete[] arr; // delete[] is used for arrays
```
## Arrays
Arrays in C++ are very similar to Java arrays:
```C++
int a[4] = {1,2,3,4};
int a[] = {1,2,3,4};
int a[4] = {};
int a[4];
```
Arrays are statically created, which means they will automatically deallocate once out of scope.
However, one thing to note is that C++ arrays need a **size to be declared**. If we don't know the size of the array to use, we can use a pointer:
- Arrays can be treated as pointers e.g. `int[] = int*`
- Technical jargon: Arrays decay to pointers to the first element of the array. 

## Pointers
A pointer is an object that refers to another object

![px = &x](https://gyazo.com/85b731ecf986c7087c77bc0d5563798b.png)
```C++
double* px; // initialise a pointer
double x = 5.1234
px = &x;   // setting a pointer to the memory address of an object
*px; // obtains the value pointed to by the pointer (dereferencing)
(*px).bar = px->bar // arrow notation can be used to access a member
```
## References
A reference variable is used to give a name to an object. It refers to the same object.
For Example:
```C++
int& rx = x;
```
- the reference variable `rx` references `x`, which means that if you change the value of `rx`, it will also change the value of `x`.

Using references is extremely useful for when passing a value into a function by reference:
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
## Divide and Conquer
The general framework for a divide-and-conquer algorithm is:
1. Divide the instance into a set of sub-problems
2. If a subproblem is small enough, solve it, otherwise recursively split the subproblem
3. Combine the subproblem solutions into a whole solution.
