# Notes in Chapter 9

## Chapter 9. Sequential Containers

The container classes share a **common interface**,
which each of the containers **expands in its own way**.

A **container** holds a collection of objects of a specified type.  
The **sequential container** let us control the **order** in which the elements are stored and accessed.  
That order **does not** depend on the values of the elements.
Instead, the order corresponds to the position at which elements are put into the container.  
By contrast, the ordered and unordered associative containers store their elements based on the **value** of a key.


### 9.1 Overview of the Sequential Container

The sequential containers all provide fast sequential access to their elements.  
These containers offer different performance trade-offs relative to:  
* The costs to add or delete elements to the container
* The costs to perform nonsequential access to elements of the container

Here are the sequential container types: 
* vector: 
    * Flexible-size array.
    * Support fast random access.
    * Inserting or deleting elements other than at the back may be slow.
* deque:
    * Double-ended queue.
    * Support fast random access.
    * Fast insert/delete at front or back.
* list:
    * Doubly linked list.
    * Support only bidirectional sequential access.
    * Fast insert/delete at any point in the list.
* forward_list:
    * Singly linked list.
    * Support only sequential access in one direction.
    * Fast insert/delete at any point in the list.
* array:
    * Fixed-size array.
    * Support fast random access.
    * Cannot add or remove elements.
* string:
    * A specialized container, similar to vector, that contains characters.
    * Fast random access.
    * Fast insert/delete at the back.

An **array** is a safer, easier-to-use alternative to built-in arrays.

The library containers almost certainly perform as well as (and usually better than)
even the most carefully crafted alternatives.

##### Deciding Which Sequential Container to Use

There are a few rules of thumb that apply to selecting which container to use:
* Unless you have a reason to use another container, use a **vector**.
* If your program has lots of small elements and space overhead matters,
  **don't** use **list** or **forward_list**.
* If the program requires random access to elements, use a **vector** or a **deque**.
* If the program needs to insert or delete elements in the middle of the container, 
  use a **list** or **forward_list**.
* If the program needs to insert or delete elements at the front and the back, but not in the middle,
  use a **deque**.
* If the program needs to insert elements in the middle of the container only while reading input,
  and subsequently needs random access to the elements:
    * First, decide whether you actually need to add elements in the middle of a container.
      It is often easier to append to a vector and then call the library *sort* function to reorder the container when you're done with input.
    * If you must insert into the middle, consider using a **list** for the input phase.
      Once the input is complete, copy the **list** into a **vector**.

If you're not sure which container to use, write your code so that it uses only operations **common** to both vectors and lists:  
Use iterators, not subscripts, and avoid random access to elements.


### 9.2 Container Library Overview

Some operations are provided by all container types:
* Type Aliases:
    * iterator: type of the iterator for this container type.
    * const_iterator: iterator type that can read but not change its elements.
    * size_type: unsigned integral type big enough to hold the size of the largest possible container of this container type.
    * difference_type: signed integral type big enough to hold the distance between two iterators.
    * value_type: element type.
    * reference: element's lvalue type; synonym for value_type&.
    * const_reference: element's const lvalue type (i.e., const value_type&).
* Construction:
    * C c; Default constructor, empty container. (except for array)
    * C c1(c2); Construct c1 as a copy of c2.
    * C c(b, e); Copy elements from the range denoted by iterators b and e (not valid for array).
    * C c{a, b, c, ...}; List initialize c
* Assignment and swap:
    * c1 = c2; Replace elements in c1 with those in c2
    * c1 = {a, b, c, ...}; Replace elements in c1 with those in the list (not valid for array).
    * a.swap(b); Swap elements in a with those in b.
    * swap(a, b); Equivalent to a.swap(b).
* Size:
    * c.size(): number of elements in c (not valid for forward_list).
    * c.max_size(): maximum number of elements c can hold.
    * c.empty(): false if c has any elements, true otherwise.
* Add/Remove Elements (not valid for array):  
  Note: the *interface* to these operations varies by container type.
    * c.insert(args): copy element(s) as specified by args into c.
    * c.emplace(inits): use inits to construct an element in c.
    * c.erase(args): remove element(s) specified by args.
    * c.clear(): remove all elements from c; return void.
* Equality and Relational Operators:
    * ==, !=: equality valid for all container types.
    * \<, \<=, \>, \>=: relationals (not valid for unordered associative containers).
* Obtain Iterators:
    * c.begin(), c.end(): return iterator to the first, one past the last element in c.
    * c.cbegin(), c.cend(): return const_iterator.
* Additional Members of Reversible Container (not valid for forward_list):
    * reverse_iterator: iterator that addresses elements in reverse order.
    * const_reverse_iterator: reverse iterator that cannot write the elements.
    * c.rbegin(), c.rend(): return iterator to the last, one past the first element in c.
    * c.crbegin(), c.crend(): return const_reverse_iterator.
    
In general, each container is defined in a header file with the same name as the type.

We must supply additional information to generate a particular container type.
For most but not all of the containers, the information we must supply is the **element type**.

##### Constraints on Types That a Container Can hold

Although we can store almost any type in a container, some container operations impose requirements of their own on the element type.  
For example, the sequential container constructor that takes a size argument uses the element type's default constructor.
Some classes do not have a default constructor.

#### 9.2.1 Iterators

Iterators have a common interface with one exception.  
The exception is that the forward_list iterators **do not** support the decrement operator.
The iterator arithmetic operations apply only to iterators for string, vector, deque and array.

##### Iterator Ranges

An **iterator range** is denoted by a pair of iterators each of which refers to
an element, or to one past the last element, in the **same** container.  
These two iterators, often referred to as begin and end (or as first and last), mark a range of elements from the container.

The second iterator **never** refers to the last element of the range.
Instead, it refers to a point one past the last element.

The elements in the range include the element denoted by the first
and every element from first up to but not including last.

Requirements on iterators forming an iterator range:  
Note: the compiler **cannot** enforce these requirements.
* They refer to elements of, or one past the end of, the same container.
* It is possible to reach end by repeatedly incrementing begin.
  In other words, end must not precede begin.
  
##### Programming Implications of Using Left-Inclusive Ranges

Left-inclusive ranges have three convenient properties:
* If begin equals end, the range is empty.
* If begin is not equal to end, there is at least one element in the range,
  and begin refers to the first element in that range.
* We can increment begin some number of times until begin == end.


#### 9.2.2 Container Type Members

A **reverse iterator** is an iterator that goes backward through a container
and inverts the meaning of the iterator operations.

If we need the element type, we refer to the container's **value_type**.  
If we need a reference to that type, we use **reference** or **const_reference**.


#### 9.2.3 *begin* and *end* Members

``` C++
list<string> a = {"Milton", "Shakespeare", "Austen"};
auto it1 = a.begin(); // list<string>::iterator
auto it2 = a.rbegin(); // list<string>::reverse_iterator
auto it3 = a.cbegin(); // list<string>::const_iterator
auto it4 = a.crbegin(); // list<string>::const_reverse_iterator
```

The functions that do not begin with a c are overloaded.  
There are actually two members, one is a const member, the other is nonconst member.  
When we call one of these members on a nonconst object, we get the version that returns iterator.
We get a const version of the iterators only when we call these functions on a const object.

We can convert a plain iterator to the corresponding const_iterator, but not vice versa.


#### 9.2.4 Defining and Initializing a Container

Excepting *array*, the default constructor creates an empty container of the specified type,
and the other constructors take arguments that specify the size of the container and initial values for the elements.

##### Initializing a Container as a Copy of Another Container

There are two ways to create a new container as a copy of another one:
* directly copy the container.
* (excepting *array*) copy a range of elements denoted by a pair of iterators.

To create a container as a copy of another container, the container and element types must **match**.  
When we pass iterators, the element types in the new and original containers can differ as long as
it is possible to convert the elements we're copying to the element type of the container we are initializing.

``` C++
list<string> authors = {"Milton", "Shakespeare", "Austen"};
vector<const char*> articles = {"a", "an", "the"};
list<string> list2(authors); // ok: types match
deque<string> authList(authors); // error: container types don't match
vector<string> words(articles); // error: element types don't match
forward_list<string> words(articles.begin(), articles.end()); // ok: converts const char* elements to string
```

##### Sequential Container Size-Related Constructor

We can also initialize the sequential containers (other than array)
from a size and an (optional) element initializer.  
If we do not supply an element initializer, the library creates a value-initialized one for us.

If the element type does not have a default constructor, then we must specify an explicit element initializer along with the size.

The constructors that take a size are valid only for **sequential** containers.
They are not supported for the **associative** containers.

##### Library arrays Have Fixed Size

The size of a library array is part of its type.  
When we define an array, in addition to specifying the element type, we also specify the container size:

``` C++
array<int, 42> // type is: array that holds 42 ints
array<string, 10> // type is: array that holds 10 strings

array<int, 10>::size_type i; // array type includes element type and size
array<int>::size_type j; // error: array<int> is not a type
```

*array* does not support the normal container constructors,
because they implicitly or explicitly determine the size of the container.

A default-constructed array is **not empty**.
It has as many elements as its size. These elements are default initialized.  

If we list initialize the array, the number of the initializers must be equal to or less than the size of the array.  
If there are fewer initializers than the size of the array, the initializers are used for the first elements and any remaining elements are value initialized.

Although we cannot copy or assign objects of built-in array types,
there is no such restriction on array.


### 9.2.5 Assignment and *swap*

The sequential containers (except array) also define a member named **assign**
that lets us assign from a different but compatible type, or assign from a subsequence of a container.  
The *assign* operation replaces all the elements in the left-hand container with (the copies of) the elements specified by its arguments.

The first version of *assign* takes two iterators.
``` C++
list<string> names;
vector<const char*> oldstyle;
names = oldstyle; // error: container types don't match
names.assign(oldstyle.cbegin(), oldstyle.cend());
```

Because the existing elements are replaced, the iterators passed to *assign*
must not refer to the container on which *assign* is called.

The second version of *assign* takes an integral value and an element value.
It replaces the elements in the container with the specified number of elements, each of which has the specified element value.

``` C++
list<string> slist1(1); // one element, which is the empty string
slist1.assign(10, "Hiya!"); // ten elements; each one is Hiya!
```

The **swap** operation exchanges the contents of two containers of the **same type**.

With the exception of *array*s, swapping two containers is guaranteed to be fast.  
The elements themselves are not swapped; internal data structures are swapped.  
It does **not** copy, delete, or insert any elements and is guaranteed to run in **constant time**.

So with the exception of *string*, iterators, references, and pointers into the containers are **Not invalidated**.
They refer to the same elements as they did before the swap.  
However, after the swap, those elements are in a different container.  
Differently, a call to swap on a *string* may invalidate iterators, references and pointers.

Swapping two *array*s does exchange the elements.
As a result, swapping two *array*s requires time proportional to the number of elements in the array.

In the new library, the containers offer both a member and nonmember version of *swap*.  
The nonmember swap is of most importance in generic programs.  
As a matter of habit, it is best to use the nonmember of version of swap.


#### 9.2.6 Container Size Operations

* The *size* member returns the number of elements in the container.
* The *empty* member returns a bool that is true if size is zero and false otherwise.
* The *max_size* member returns a number that is **greater than or equal to** the number of elements a container of that type can contain.

With one exception: forward_list provides max_size and empty, but not size.


#### 9.2.7 Relational Operators

**Every** container type supports the equality operators (== and !=).  
All the containers **except** the unordered associative containers also support the relational operators (\>, \>=, \<, \<=).

The right- and left-hand operands must be the same kind of container and must hold elements of the same type.

* If both containers are the same size and all the elements are equal,
  then the two containers are equal; otherwise, they are unequal.
* If the containers have different size but every element of the small one is equal to the corresponding element of the larger one,
  then the smaller one is less than the other.
* If neither container is an initial subsequence of the other, then the comparison depends on comparing the first unequal elements.

##### Relational Operator Use Their Element's Relational Operator

We can use a relational operator to compare two containers only if
the appropriate comparison operator is defined for the **element type**.



### 9.3 Sequential Container Operations

The **sequential** and **associative** containers differ in how they **organize** their elements.

#### 9.3.1 Adding Elements to a Sequential Container

Operations that add elements to a sequential container:  
(Note: they are not supported by *array*s;
 forward_list has special versions of *insert* and *emplace*;
 *push_back* and *emplace_back* not valid for *forward_list*;
 *push_front* and *emplace_front* not valid for vector or string)  
* c.push_back(t): create an element with value t at the and of c. Return void.
* c.emplace_back(args): create elements constructed from args at the end of c. Return void.
* c.push_front(t): create an element with value t on the front of c. Return void.
* c.emplace_front(args): create elements constructed from args on the front of c. Return void.
* c.insert(p, t): create an element with value t before the element denoted by *iterator* p. Return an iterator referring to the element that was added.
* c.emplace(p, args): create elements constructed from args before the element denoted by iterator p. Return an iterator referring to the element that was added.
* c.insert(p, n, t): insert n elements with value t before the element denoted by iterator p.
                     Return an iterator to the first element inserted. If n is zero, return p.
* c.insert(p, b, e): insert the elements from the range denoted by iterators b and e before the element denoted by iterator p.
                     b and e may not refer to elements in c.
                     Return an iterator to the first element inserted; if the range is empty, return p.
* c.insert(p, il): il is a braced list of element values. Insert the given values before the element denoted by the iterator p.
                   Return an iterator to the first inserted element; if the list is empty, return p.

Adding elements to a vector, string, or deque potentially invalidate all existing iterators, references, and pointers into the container.

The container use different strategies for allocating elements and that these strategies affect performance.
* Adding elements anywhere but at the end of a *vector* or *string*, or anywhere but the beginning of end of a *deque*,
  requires elements to be **moved**.
* Adding elements to a *vector* or a *string* may cause the entire object to be **reallocated**.

