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

##### Using push_back

Aside from *array* and *forward_list*, every sequential container (including the *string* type) supports push_back.

Because string is just a container of characters, we can use push_back to add characters to the end of the string.

``` C++
void pluralize(size_t cnt, string &word)
{
    if (cnt > 1)
        word.push_back('s');
}
```

When we use an object to initialize a container, or insert an object into a container,
a **copy** of that object's value is placed in the container, not the object itself.

##### Using push_front

*list*, *forward_list* and *deque* containers support *push_front*.
This operation inserts a new element at the front of the container.

*deque* and *vector* both offer fast random access to its elements.
But *deque* provides push_front while *vector* does not.

A deque guarantees constant-time insert and delete of elements at the **beginning and end** of the container.  
As with vector, inserting elements other than at the front or back of a deque is a potentially expensive operation.

##### Adding Elements at a Special Point in the Container

*insert* members are supported for *vector*, *deque*, *list* and *string*.  
*forward_list* provides specialized versions of these members.

Each of the insert functions takes an iterator as its first argument.
The iterator indicates where in the container to pu the element(s).  
Because the iterator might refer to a nonexistent element off the end of the container,
and because it is useful to have a way to insert elements at the beginning of a container,
element(s) are inserted **before** the position denoted by the iterator.

We can insert elements at the beginning of a container without worrying about
whether the container has *push_front*.

##### Inserting a Range of Elements

The arguments to *insert* that appear after the initial iterator argument
are analogous to the container constructors that take the same parameters,
for example, an element count and a value, a pair of iterators, or an initializer list.

When we pass a pair of iterators, those iterators may **not** refer to the same container
as the one to which we are adding elements.

The version of *insert* that take a count or a range return an iterator
to the **first** element that was inserted.  
If the range is empty, no elements are inserted, and the operation returns its first parameter.

##### Using the Return from insert

We can use the value returned by *Insert* to repeatedly insert elements at a specified position in the container.

``` C++
list<string> lst;
auto iter = lst.begin();;
while(cin >> word)
    ter = lst.insert(iter, word); // same as calling push_front
```

##### Using the Emplace Operation

*emplace_front*, *emplace* and *emplace_back*, which construct rather than copy elements,
correspond to the *push_front*, *insert*, and *push_back* operations
in that they let us put an element at the front of the container, in front of a given position, or at the back of the container, respectively.

When we call an emplace member, we pass arguments to a **constructor** for the element type.
The emplace members use those arguments to construct an element **directly** in space managed by the container.

``` C++
// construct a Sales_data object at the end of c

// use the three-argument Sales_data constructor
c.emplace_back("978-0590353403", 25, 15.99);

// error: there is no version of push_back that takes three arguments
c.push_back("978-0590353403", 25, 15.99);

// ok: we create a temporary Sales_data object to pass to push_back
c.push_back(Sales_data("978-0590353403", 25, 15.99));
```

The arguments to an emplace function vary depending on the element type.
The arguments must match a constructor for the element type.


#### 9.3.2 Accessing Elements

Here are the operations to access elements in a **sequential container**:  
(Note: *at* and *subscript* operator valid only for string, vector, deque, and array.  
 back not valid for forward_list.  
 The access operations are undefined if the container has no elements.)  
* c.back(): return a reference to the last element in c. 
* c.front(): return a reference to the first element in c.
* c[n]: return a reference to the element indexed by the unsigned integral value n. Undefined if n >= c.size().
* c.at(n): return a reference to the element indexed by n. If the index is out of range, throw an out_of_range exception.

Each sequential container has a *front* member. (including *array*)  
All except *forward_list* have a *back* member.

We can obtain references to the first and last elements in two different ways:
* Call *front* and *back*.
* Dereference the iterator returned by *begin* and **decrementing** and then dereference the iterator returned by *end*.

Before calling *front* or *back* or dereferencing the iterator from *begin* or *end*,
we should check that the contain is not empty.

##### The Access Members Return References

If the container is not const, the return is an ordinary reference that we can use to change the value of the fetched element.  
If the container is const, the return is a reference to const.

If we use *auto* to store the return from one of these functions
and we want to use that variable to change the element,
we must remember to define our variable as a reference type.

``` C++
if (!c.empty){
    c.front() = 42; // assign 42 to the first element in c
    auto &v = c.back(); // get a reference to the last element
    v = 1024; // change the element in c
    auto v2 = c.back(); // v2 is not a reference; it's a copy of c.back()
    v2 = 0; // no change to the element in c
}
```

##### Subscripting and Safe Random Access

If we want to ensure that our index is valid, we can use the *at* member instead of subscript operator.
It acts like the subscript operator, but if the index is invalid, *at* throws an *out_of_range* exception.


#### 9.3.3 Erasing Elements

Here are the erase operations on **sequential containers**:  
(Note: they are not supported by *array*.  
 *forward_list* has a special version of *erase*.  
 *pop_back* not valid for *forward_list*.  
 *pop_front* not valid for *vector* and *string*.)
* c.pop_back(): remove last element in c. Return void.
* c.pop_front(): remove first element in c. Return void.
* c.erase(p): remove the element denoted by the iterator p
              and return an iterator to the element after the one deleted or the off-the-end iterator if p denotes the last element.
* c.erase(b, e): remove the range of elements denoted by the iterators b and e.
                 Return an iterator to the element after the last one that was deleted , or an off-the-end iterator if e is itself an off-the-end iterator.
* c.clear(): remove all the element in c. Return void.

The members above do **not** check their argument(s).
The programmers must ensure that element(s) exist before removing them.

Removing elements anywhere but the beginning or end of a deque invalidates all iterators, references and pointers.  
Iterators, references and pointers to elements **after** the ensure point in a *vector* or *string* are invalidated.

##### The pop_front and pop_back Members

pop_front and pop_back return **void**.
If you need the value you are about to pop, you must store that value before doing the pop.

##### Removing an Element from within the Container

The *erase* members return an iterator referring to the location **after** the (last) element that was removed.

The following loop erases the odd elements in a *list*.

``` C++
list<int> lst = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
auto it = lst.begin();
while(it != lst.end()){
    if(*it % 2)
        it = lst.erase(it);
    else
        ++it;
}
```


#### 9.3.4 Specialized forward_list Operations

When we add or remove an element in a forward_list, we need access to its predecessor in order to update that element's links.
However, *forward_list* is a singly link list, so there is no way to get to an element's predecessor.  
For this reason, the operations to add or remove elements in a *forward_list* operate by changing the element **after** the given element.
That way, we always have access to the elements that are affected by the change.

So *forward_list* does **not** define *insert*, *emplace*, or *erase*.
Instead it defines members named *insert_after*, *emplace_after*, and *erase_after*.  
To support these operations, *forward_list* also defines *before_begin*, which returns an *off-the beginning* iterator.
This iterator lets us add or remove element after the nonexistent element before the first one in the list.

Here are the operations to insert or remove elements in a *forward_list*:
* lst.before_begin(): iterator denoting the nonexistent element just before the beginning of the list.
* lst.cbefore_begin(): return a const_iterator.
* lst.insert_after(p, t) / (p, n, t) / (p, b, e) / (p, il): 
  insert element(s) after the one denoted by iterator p. 
  t is an object, n is a count, b and e are iterators denoting a range (b and e must **not** refer to lst), and il is a braced list.
  Return an iterator to the **last** inserted element. If the range is empty, return p.
  Undefined if p is the off-the-end iterator.
* lst.emplace_after(p, args): use args to construct an element after the one denoted by iterator p.
  Return an iterator to the new element.
* lst.erase_after(p) / (b, e):
  remove the element after the one denoted by iterator p 
  or the range of elements from the one **after** the iterator b up to but **not including** the one denoted by e.
  Return an iterator to the element **after** the one deleted, or the off-the-end iterator if there is no such element.
  
When we add or remove elements in a *forward_list*, we have to keep track of two iterators:
one to the element we're checking and one to that element's predecessor.

``` C++
forward_list<int> flst = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
auto prev = flst.before_begin();
auto curr = flst.begin();

while(curr != flst.end()){
    if(*curr % 2)
        curr = flst.erase_after(prev);
    else {
        prev = curr;
        ++curr;
    }
}
```


#### 9.3.5 Resizing a Container

With the exception of *array*s, we can use *resize* to make a container larger or smaller.  
* If the current size is greater than the requested size, elements are deleted from the back of the container.
* If the current size is less than the new size, elements are added to the back of the container.

Here are the sequential container size operations:
* c.resize(n): resize c so that it has n elements. Any elements **added** are value initialized.
* c.resize(n, t): resize c to have n elements. Any elements **added** have value t.


#### 9.3.6 Container Operations May Invalidate Iterators

Operations that add or remove elements from a container can invalidate pointers, references, or iterators to container elements.  
An *invalidated** pointer, reference, or iterator is one that no longer denotes an element.

After an operation that adds elements to a container:  
* Iterators, pointers, and references to a *vector* or *string* are invalid
  if the container was **reallocated**. If no reallocation happens, indirect references to elements **before** the insertion remain valid;
  those to elements **after** the insertion are invalid.
* Iterators, pointers, and references to a *deque* are invalid
  if we add elements anywhere but at the front or back. If we add at the front or back, iterators are invalidated, but references and pointers to existing elements are not.
* Iterators, pointers, and references (including the off-the-end and the before-the-beginning iterators) to a *list* or *forward_list* remain valid.

After we remove an element:
* All other iterators, references or pointers (including the off-the-end and before-the -beginning iterators)
  to a *list* or *forward_list* remain valid.
* All other iterators, references or pointers to a *deque* are invalidated
  if the removed elements are anywhere but the front or back. If we remove elements at the back of the deque, the off-the-end iterator is invalidated but other iterators, references, and pointers are unaffected;
  they are also unaffected if we remove from the front.
* All other iterators, references, or pointers to a *vector* or *string* remain valid for elements **before** the removal point.
  Note: the off-the-end iterator is always invalidated when we remove elements.
  
When using an iterator, a reference, or a pointer to a container element,
**minimize** the part of the program during which an iterator must stay valid.  
It it especially important for *vector*, *string* and *deque*.

##### Writing Loops That Change a Container

Loops that add or remove elements of a vector, string or deque must ensure that
the iterator, reference, or pointer is refreshed on each trip through the loop.  
Refreshing an iterator is easy if the loop calls *insert* or *erase*.
Those operations return iterators, which we can use to reset the iterator.

##### Avoid Storing the Iterator Returned from *end*

Loops that add or remove elements should always call *end* rather than use a stored copy.  
Partly for this reason, C++ standard libraries are usually implemented so that calling end() is a very fast operation.



### 9.4 How a *vector* Grows

*vector* and *string* elements are stored **contiguously**.

In the case of *vector*s and *string*s, part of the implementation leaks into its interface.

Given that elements are contiguous and the size of the container is flexible,
when we add an element to a *vector* or a *string*, if there is no room for the new element,
the container must allocate new memory.

If the *vector* did this memory allocation and deallocation **each** time we added an element,
performance would be unacceptably slow.

To avoid these costs, library implementors use allocation strategies that reduce the number of times the container is reallocated.  
When they have to get new memory, *vector* and *string* implementations typically allocate capacity **beyond** what is immediately needed.
The container hold the storage **in reverse** and uses it to allocate new elements as they are needed.

##### Members to Manage Capacity

The *vector* and *string* types provide members that let us interact with the memory-allocation part of the implementation:  
(Note: shrink_to_fit valid only for *vector*, *string*, and *deque*.  
 *capacity* and *reserve* valid only for *vector* and *string*.)  
* c.shrink_to_fit(): request to reduce capacity() to equal to ().
* c.capacity(): number of elements c can have before reallocation is necessary.
* c.reserve(n): allocate space for at least n elements.

A call to *reserve* changes the capacity of the *vector* only if the requested space **exceeds** the current capacity.  
If so, *reserve* allocates **at least** as much as (and may allocate more than) the requested amount.  
If not, *reserve* does not cause the container to give back memory.

There is **no guarantee** that a call to *shrink_to_fit* will return memory.
The implementation is free to ignore this request.

##### **capacity** and **size**

* The *size* of a container is the number of elements it already holds.
* The *capacity* of a container is how many elements it can hold before more space must be allocated.

Each vector implementation can choose its own allocation strategy.  
However, it **must** not allocate new memory until it is forced to do so.

A *vector* may be reallocated **only** :
* when the user performs an insert operation when the *size* equals *capacity*.
* by a call to *resize* or *reserve* with a value that **exceeds** the current capacity.

Technically speaking, the execution time of creating an n-element vector by calling push_back n times on an initially empty vector
must never be more than a constant multiple of n.


### 9.5 Additional *string* Operations

The *string* library defines a great number of functions, which use repeated patterns.

#### 9.5.1 Other Ways to Construct *string*s

Here are there more ways to construct a string:  
(Note: n, len2 and pos2 are all **unsigned** values)  
* string s(cp, n); s is a copy of the first n characters in the array to which cp points.
  The array must have at least n characters.
* string s(s2, pos2); s is a copy of the characters in the string s2 starting at the index pos2.
  Undefined if pos2 > s2.size().
* string s(s2, pos2, len2); s is a copy of len2 characters from s2 starting at the index pos2.
  Undefined if pos2 > s2.size(). Regardless of the value of len2, copies at most s2.siz() - pos2 characters.

Ordinarily when we create a *string* from a const char*, the array to which the pointer points
must be **null terminated**; characters are copied up to the null.

When we copy from a *string*, if the position argument is greater than the size,
then the constructor throws an out_of_range exception.

##### The *substr* Operation

s.substr(pos, n): return a string containing n characters from s starting at pos.
pos defaults to 0. n defaults to a value that causes the library to copy all the characters in s starting from pos.

The substr function throws an out_of_range exception if the position exceeds the size of the string.  
If the position plus the count is greater than the size, the count is adjusted to copy only up to the end of the string.


#### 9.5.2 Other Ways to Change a *string*

*string* defines additional versions of *insert* and *erase*, which take an **index**.
The index indicates the starting element to *erase* or the position *before* which to *insert* the given value.

Here are the operations to modify strings: 
* s.insert(pos, args): insert characters specified by args before pos.
  pos can be an index or an iterator. Versions taking an index return a reference to s;
  those taking an iterator return an iterator denoting the first inserted character.
* s.erase(pos, len): remove len characters starting at position pos.
  If len is omitted, removes characters from pos to the end of s. Return a reference to s.
* s.assign(args): replace characters in s according to args. Return a reference to s.
* s.append(args): append args to s. Return a reference to s.
* s.replace(range, args): remove range of characters from s and replace them with the characters formed by args.
  range is either an index and a length or a pair of iterators into s.
  Return a reference to s.
* Note: args can be one of the following ; append and assign can use all forms;
  str must be distinct from s and the iterators b and e may not refer to s:
    * str: the string str.
    * str, pos, len: up to len characters from str starting at pos.
    * cp, len: up to len characters from the character array pointed to by cp.
    * cp: null-terminated array pointed to by pointer cp.
    * n, c: n copies of character c.
    * b, e: characters in the range formed by iterators b and e.
    * initializer list: comma-separated list of characters enclosed in braces.
* args for *replace* and *insert* depend on how *range* or *pos* is specified.
    
``` C++
s.insert(s.size(), 5, '!'); // insert five exclamation points at the end of s
s.erase(s.size() - 5, 5); // erase the last five characters from s
```

We can use a **null-terminated** character array as the value to insert or assign into a string.

``` C++
const char *cp = "Stately, plump Buck";
s.assign(cp, 7); // s == "Stately"
s.insert(s.size(), cp + 7); // s == "Stately, plump Buck"

string s = "some string", s2 = "some other string";
s.insert(0, s2); // insert a copy of s2 before position 0 in s
s.insert(0, s2, 0, s2.size()); // insert s2.size() characters from s2 starting at s2[0] before s[0]
```

##### The append and replace Functions

The *append* operation is a shorthand way of inserting at the end.  
The *replace* operations are a shorthand way of calling *erase* **and** *insert*.

```C++
string s("C++ Primer"), s2 = s;

s.insert(s.size(), " 4th Ed."); // s == "C++ Primer 4th Ed"
s2.append(" 4th Ed."); // equivalent: appends "4th Ed." to s2; s == s2

s.erase(11, 3); // s == "C++ Primer Ed."
s.insert(11. "5th"); // s == "C++ Primer 5th Ed."
s2.replace(11, 3, "5th"); // equivalent: s == s2
```

##### The Many Overloaded Ways to Change a *string*

The *append*, *assign*, *insert*, *replace* functions have several overloaded versions.  
The arguments to these functions vary as to how we specify what characters to add and what part of the string to change.

The *assign* and *append* functions have **no** need to specify what part of the string is changed:
*assign* always replaces the entire contents of the string and *append* always adds to the end of the string.

The *replace* functions provide two ways to specify the range of characters to remove:
a position and a length, or an iterator range.

The *insert* functions give us two ways to specify the insertion point:
an index or an iterator.

The added characters can be taken from another string, a character pointer, a braced-enclosed list of characters, or as a character and a count.  
When the characters come from a string or a character pointer, we can pass additional arguments to control whether we copy some or all of the characters from the argument.


#### 9.5.3 *string* Search Operations

There are 6 different search functions, each of which has 4 overloaded versions.  

Each of them returns a *string::size_type* value that is the index of where the match occurred.
If there is no match, the function returns a *static* member named *string::npos*.

The library defines npos as a const string::size_type initialized with the value **-1**.  
Because npos is an unsigned type, this initializer means npos is equal to the **largest** possible size any string could have.

It is a bad idea to use a signed type to hold the return from search functions.

Here are the *string* search operations:  
* s.find(args): find the **first** occurrence of args in s.
* s.rfind(args): find the **last** occurrence of args in s.
* s.find_first_of(args): find the **first** occurrence of **any** character form args in s.
* s.find_last_of(args): find the **last** occurrence of **any** character from args in s.
* s.find_first_not_of(args): find the **first** character in s that is **not** in args.
* s.fins_last_not_of(args): find the **last** character in s that is **not** in args.
* args must be one of:
    * c, pos: look for the character c starting at position pos in s. pos defaults to 0.
    * s2, pos: look for the string s2 starting at position pos in s. pos defaults to 0.
    * cp, pos: look for the C-style null-terminated string pointed by the pointer cp. Start looking at position pos. pos defaults to 0.
    * cp, pos, n: look for the first n characters in the array pointed to by the pointer cp. Start looking at position pos in s. No default for pos or n.
    

#### 9.5.4 The *compare* Functions

*string* provides a set of compare functions that are similar to the C library *strcmp* function.

s.compare returns zero or a positive or negative value depending on
whether s is equal to, greater than, or less than the string formed from the given arguments.

There are 6 versions of *compare.
The arguments vary based on whether we are comparing two strings or a string and a character array.  

Here are possible arguments to s.compare:
* s2: compare s to s2.
* pos1, n1, s2: compare n1 characters starting at pos1 from s to s2.
* pos1, n1, s2, pos2, n2: compare n1 characters starting at pos1 from s to the n2 characters starting at pos2 in s2.
* cp: compare s to the null-terminated array pointed to by cp.
* pos1, n1, cp: compare n1 characters starting at pos1 from s to cp.
* pos1, n1, cp, n2: compare n1 characters starting at pos1 from s to n2 characters starting from the pointer cp.


#### 9.5.5 Numeric Conversions

The new standard introduced several functions that convert between numeric data and library strings:  
* to_string(val): overloaded functions returning the *string* representation of val.
  val can be any arithmetic type. There are versions of to_string for each floating-point type and integral type that is int or larger.
  Small integral types are promoted as usual.
* stoi / stol / stoul / stoll / stoull(s, p, b):
  return the initial substring of s that has numeric content as an int, long, unsigned long, long long, unsigned long long, respectively.
  b indicates the numeric base to use for the conversion; b defaults to 10.
  p is a pointer to a size_t in which to put the index of the first nonnumeric character in s; p defaults to 0, in which case the function does not store the index.
* stof / stod / stld (s, p):
  return the initial numeric substring in s as a float, double, or long double, respectively.
  p has the same behavior as described for the integer conversions.
  
``` C++
string s = "pi = 3.14";
d = stod(s.substr(s.fin_first_of("+-.0123456789")));
```

* The string can begin with 0x or 0X to indicate hexadecimal.
* For the functions that convert to floating-point, the string may also start with a decimal point
  and may contain an e or E to designate the exponent.
* For the functions that convert to integral type, depending on the base, the string can contain alphabetic characters corresponding to numbers beyond the digit 9.

If the string can't be converted to a number, these functions throw an invalid_argument exception.  
If the conversion generates a value that can't be represented, they throw out_of_range.



### 9.6 Container Adaptors

An **adaptor** is a general concept in the library.
There are containers, iterators, and function adaptors.  
Essentially, an adaptor is a mechanism for making one thing act like another.
A container adaptor takes an existing container type and makes it act like a different type.

The library defines three sequential container adaptors: **stack**, **queue** and **priority_queue**.

Here are the operations and types that are common to all the container adaptors:
* size_type: type large enough to hold the size of the largest object of this type.
* value_type: element type.
* container_type: type of the underlying container on which the adaptor is implemented.
* A a: create a new empty adaptor named a.
* A a(c): create a new adaptor named a with a copy of the container c.
* *relational operator*: each adaptor supports all the relational operators: ==, !=, \<, \<=, \>, \>=.
  These operators return the result of comparing the underlying containers.
* a.empty(): false if a has any elements, true otherwise.
* a.size(): number of elements in a.
* swap(a, b) / a.swap(b): swap the contents of a and b; a and b must have the same type,
  including the type of the container on which they are implemented.
  
##### Defining an Adaptor

Each adaptor defines two constructors: the default constructor that creates an empty object,
and a constructor that takes a container and initializes the adaptor by copying the given container.

``` C++
// dep is a deque<int>
stack<int> stk(dep); // copy elements from dep into stk
```

By default, both *stack* and *queue* are implemented in terms of *deque*,
and a *priority_queue* is implemented on a *vector*.  
We can **override** the default container type by naming a sequential container as a second type argument.

``` C++
// empty stack implemented on top of vector
stack<string, vector<string>> str_stk;
// str_stk2 is implemented on top of vector and initially holds a copy of svec
stack<string, vector<string>> str_stk2(svec);
```

There are constraints on which containers can be used for a given adaptor.  
* All of the adaptors require the ability to add and remove elements.
  So they cannot be built on an *array*.
* All of the adaptors require operations that add, remove, or access the last element in the container.
  So they cannot be built on a *forward_list*.
* A *stack* requires only *push_back*, *pop_back*, and *back* operations,
  so we can use any of the remaining container types for a *stack*.
* A *queue* requires *back*, *push_back*, *front*, and *push_front*,
  so we can use a *list* or *deque* but not a *vector*.
* A *priority_queue* requires random access in addition to the *front*, *push_back*, and *pop_back* operations,
  so it can be built on a *vector* or a *deque* but not on a *list*.
  
##### Stack Adaptor

The *stack* type is defined in the *stack* header.

Here are the stack operations:  
(Note: use *deque* by default; can be implemented on a *list* or *vector* as well)  
* s.pop(): remove, but do not return, the top element from the stack.
* s.push(item) / s.emplace(args): create a new top element on the stack by copying or moving item,
  or by constructing the element from args.
* s.top(): return, but do not remove, the top element on the stack.

``` C++
stack<int> iniStack; // empty stack
// fill up the stack
for (size_t ix = 0; ix != 10; ++ix)
    intStack.push(ix); // intStack holds 0...9 inclusive
while (!intStack.empty()) { // while there are still values in intStack
    int value = intStack.top();
    // code that uses value
    intStack.pop(); // pop the top element, and repeat
}
```

##### The Queue Adaptor

The *queue* and *priority_queue* adaptors are defined in the *queue* header.

Here are *queue*, *priority_queue* operations:  
(By default *queue* uses *deque* and *priority_queue* uses *vector*;  
*queue* can use a *list* or *vector* as well, *priority_queue* can use a *deque*.)
* q.pop(): remove, but do not return, the front element or highest-priority element
  from the *queue* or *priority_queue*, respectively.
* q.front() / q.back(): return, but do not remove, the front or back element of q.
  **Valid only for queue**.
* q.top(): return, but do not remove, the highest-priority element.
  **Valid only for priority_queue**.
* q.push(item) / q.emplace(args): create an element with value item or constructed from args at the end of the queue
  or in its appropriate position in *priority_queue*.

