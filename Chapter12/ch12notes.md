# Notes in Chapter 12

## Chapter 12. Dynamic Memory

* *Global* objects are allocated at program *start-up* and destroyed when the program *ends*.
* *Local* *automatic* objects are created and destroyed when the block in which they are define is entered and exited.
* *Local* *static* objects are allocated before their *first use* and are destroyed when the program *ends*.
* **Dynamically allocated** objects have a lifetime that is independent of where they are created, and exist until they are *explicitly* freed.

To make using dynamic objects safer, the library defines 2 **smart pointer** types that manage dynamic objects.  
Smart pointers ensure that the objects to which they point are automatically freed when it is appropriate to do so.

* *Static memory* is used for local *static* objects, for class *static* data members, and for variables defined outside any function.
* *Stack memory* is used for *nonstatic* objects defined inside functions.
* *Heap* (*free store*) is for objects that the program dynamically allocates.



### 12.1 Dynamic Memory and Smart Pointers

Dynamic memory is managed through a pair of operators:  
* **new**, which allocates, and optionally initializes, an object in dynamic memory and returns a pointer to that object.
* **delete**, which takes a pointer to a dynamic object, destroys that object, and frees the associated memory.

A *smart pointer* acts like a regular pointer, with the important exception that it *automatically* deletes the object to which it points.

All these smart pointer types are defined in the *memory* header.
* **shared_ptr** allows multiple pointers to refer to the same object.
* **unique_ptr** *owns* the object to which it points.
* **weak_ptr** is a weak reference to an object managed by a *shared_ptr*.

Here are the operations common to *shared_ptr* and *unique_ptr*:  
* shared_ptr<T> sp, unique_ptr<T> up:
  Null smart pointer that can point to objects of type T.
* p:
  Used as a condition; *true* if p points to an object.
* *p:
  Dereference p to get the object to which p points.
* p-\>mem:
  Synonym for (*p).mem.
* p.get():
  Return the pointer in p. Use with caution; the object to which the returned pointer points will **disappear** when the smart pointer deletes it.
* swap(p, q), p.swap(q):
  Swap the **pointers** in p and q.


#### 12.1.1 The *shared_ptr* Class

Smart pointers are template. So when we create a smart pointer, we must supply the type to which the pointer can point.

``` C++
shared_ptr<string> p1; // shared_ptr that can point at a string
shared_ptr<list<int>> p2; // shared_ptr that can point at a list of int
```

A default initialized smart pointer holds a **null** pointer.

We use a smart pointer in ways that are similar to using a pointer.

``` C++
// if p1 is not null, check whether it's the empty string
if (p1 && p1->empty())
    *p1 = "hi"; // if so, dereference p1 to assign a new value to that string
```

Here are the operations specific to *shared_ptr*:  
* make_shared<T>(args):
  Return a *shared_ptr* pointing to a dynamically allocated object of type T.
  Use *args* to initialize that object.
* shared_ptr<T> p(q):
  p is a copy of the *shared_ptr* q; increment the count in q.
  The pointer in q must be convertible to T*.
* p = q:
  p and q are *shared_ptr*s holding pointers that can be converted to one another.
  Decrement p's reference count and increment q's count;
  delete p's existing memory if p's count goes to 0.
* p.unique():
  Return *true* if p.use_count() is one; *false* otherwise.
* p.use_count():
  Return the number of objects sharing with p;
  may be a **slow** operation, intended primarily for **debugging** purposes.
  
##### The *make_shared* Function

The **safest** way to allocate and use dynamic memory is to call a library function named *make_shared*.  
It allocates and initializes an object in dynamic memory and returns a *shared_ptr* that points to that object.  
It is defined in the *memory* header.  
When we call it, we must specify the type of object we want to create.

``` C++
// shared_ptr that points to an int with value 42
shared_ptr<int> p3 = make_shared<int>(42);
// p4 points to a string with value 9999999999
shared_ptr<string> p4 = make_shared<string>(10, '9');
// p5 points to an int that is value initialized to 0
shared_ptr<int> p5 = make_shared<int>();
// p6 points to a dynamically allocated, empty vector<string>
auto p6 = make_shared<vector<string>>();
```

*make_shared* uses its arguments to construct an object of the given type.
If we do not pass any arguments, then the object is value initialized.

##### Copying and Assigning *shared_ptr*

When we copy or assign a shared_ptr, each shared_ptr keeps track of *how many other shared_ptrs point to the same object*.

``` C++
auto p = make_shared_ptr<int>(42); // object to which p points has one user
auto q = p; // p and q point to the same object; object to which p and q has two users

auto r = make_shared<int>(42); // int to which r points has one user
r = q; // assign to r, making it point to a different address
       // increase the use count for the object to which q points
       // resuce the use count of the object to which r has pointed
       // the object r had pointed to has no users; that object is automatically freed
```

We can think of a *shared_ptr* as if an associated counter, usually referred to as a *reference count*.  
Whenever we copy a *shared_ptr*, the count is incremented.  
The counter is decremented when we assign a new value to the *shared_ptr* and when the *shared_ptr* itself is destroyed.  
Once a *shared_ptr*'s counter goes to zero, the *shared_ptr* **automatically frees** the object that it manages.

It is *up to the implementation* whether to use a counter or another data structure to keep track of how many pointers share state.

##### *shared_ptr*s Automatically Destroy Their Objects
 
When the **last** *shared_ptr* pointing to an object is destroyed, the *shared_ptr* class automatically destroys the object to which that shared_ptr points.  
It does so through another special *member function* known as a **destructor**.

Each class has a **destructor**. The destructor controls what happens when objects of that class type are *destroyed*.  
It generally **free the resources** that an object has **allocated**.

The destructor for *shared_ptr* decrements the reference count of the object to which that *shared_ptr* points.
If the count goes to zero, the *shared_ptr* destructor destroys the object to which the *shared_ptr* points and frees the memory used by that object.

##### *shared_ptr* Automatically Free the Allocated Memory

``` C++
// factory returns a shared_ptr pointing to a dynamically allocated object
shared_ptr<Foo> factory(T arg)
{
    // process arg as appropriate
    // shared_ptr will take care of deleting this memory
    return make_shared<Foo>(arg);
} // there is another user, the returned shared_ptr, so the created Foo will not be automatically destroyed

void use_factory(T arg)
{
    shared_ptr<Foo> p = factory(arg);
    // use p
} // p goes out of scope; the memory to which p points is automatically freed
```

If you put *shared_ptr*s in a container, and you subsequently need to use some, but not all, of the elements,
remember to **erase** the elements you no longer need.

##### Classes with Resources That Have Dynamic Lifetime

Programs tend to use dynamic memory for one of three purposes:  
* They don't know *how many* objects they'll need
* They don't know the *precise type* of the objects they need
* They want to *share data* between several objects.

A common reason to use dynamic memory is to allow multiple objects to share the same *state*.


#### 12.1.2 Managing Memory Directly

The language **itself** defines two operators that allocate and free dynamic memory:  
* the *new* operator allocates memory.
* the *delete* operator frees memory allocated by *new*.

Using these operators to manage memory is considerably more *error-prone* than using a smart pointer.

##### Using *new* to Dynamically Allocate and Initialize Objects

Objects allocated on the free store are **unnamed**, so *new* offers no way to name the objects that it allocates.
Instead, *new* returns a pointer to the object it allocates.

``` C++
int *pi = new int; // pi points to a dynamically allocated, unnamed, uninitialized int
string *ps = new string; // initialized to empty string
```

By default, dynamically allocated objects are *default initialized*,
which means that objects of built-in or compound type have **undefined** value;
objects of class type are initialized by their **default constructor**.

We can initialize a dynamically allocated object using *direct initialization*.  
We can use traditional construction (using parentheses), and under the new standard, we can also use list initialization.

``` C++
int *pi = new int(1024); // object to which pi points has value 1024
string *ps = new string(10, '9'); // *ps is "9999999999"
vector<int> *v = new vector<int> {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
```

We can also *value initialize* a dynamically allocated object by following the type name with a pair of empty parentheses.

``` C++
string *ps1 = new string; // default initialized to the empty string
string *ps = new string(); // value initialized to the empty string
int *pi1 = new int; // default initialized; *pi1 is undefined
int *pi2 = new int(); // value initialized to 0; *pi2 is 0
```

For class types that define their own constructors, requesting value initialization is of no consequence;
regardless of form, the object is initialized by the default constructor.

It is a good idea to initialize dynamically allocated objects.

When we provide an initializer inside parentheses, we can use *auto* to deduce the type of the object we want to allocate from that initializer.  
However, because the compiler uses the initializer's type of deduce the type to allocate, we can use *auto* **only** with a **single initializer** inside parentheses.

``` C++
auto p1 = new auto(obj); // p1 points to an object of the type of obj and that object is initialized from obj
auto p2 = new auto {a, b, c}; // error: must use parentheses from obj
```

##### Dynamically Allocated *const* Objects

``` C++
// allocate and initialize a const int
const int *pci = new const int(1024);
// allocate a default-initialized const empty string
const string *pcs = new const string;
```

A dynamically allocated *const* object must be initialized.  
A *const* dynamic object of a class type that defines a default constructor may be initialized implicitly.

Because the allocated object is *const*, the pointer returned by *new* is a pointer to *const*.

##### Memory Exhaustion

Once a program has used all of its *available* memory, *new* expressions will fail.  
By default, if *new* is unable to allocate the requested storage, it throws an exception of type *bad_alloc*.

We can prevent *new* from throwing an exception by using a different form of *new*, **placement new**.  
A placement new expression lets us pass additional arguments to *new*.

``` C++
// if allocation fails, new returns a null pointer
int *p1 = new int; // if allocation, new throws std::bad_alloc
int *p2 = new (nothrow) int; // if allocation fails, new returns a null pointer
```

##### Freeing Dynamic Memory

We **return** memory to the system through a *delete expression*.  
A delete expression takes a pointer to the object we want to free.  
It performs 2 actions: destroy the object to which its given pointer points, and free the corresponding mempry.

``` C++
delete p; // p must point to a dynamically allocated object or be null
```

##### Pointer Values and *delete*

The pointer we pass to *delete* must either point to dynamically allocated memory or be a *null* pointer.

Deleting a pointer to memory that was not allocated by *new*, or deleting the same pointer value *more than once*, is **undefined**.

``` C++
int i, *pi1 = &i, *pi2 = nullptr;
double *pd = new double(33), *pd2 = pd;
delete i; // error: i is not a pointer
delete pi1; // undefined: pi1 refers to a local
delete pd; // ok
delete pd2; // undefined: the memory pointed to by pd2 was already freed
delete pi2; // ok: it is always ok to delete a null pointer
```

Although the value of a *const* object cannot be modified,
the object itself can be destroyed.  
A *const* dynamic object is also freed by executing *delete* on a pointer that points to that object.

##### Dynamically Allocated Objects Exist until They Are Freed

A dynamic object managed through a built-in pointer exist **until** it is explicitly deleted.

Functions that return pointers to dynamic memory put a burden on their callers.
The caller must remember to delete the memory.

``` C++
// factory returns a pointer to a dynamically allocated object
Foo* factory (T arg)
{
    // process arg as appropriate
    return new Foo(arg); // caller is responsible for deleting this memory
}

void use_factory (T arg)
{
    Foo *p = factory(arg);
    // use p but not delete it
} // p goes out of scope, but the mempry to which p points is not freed!

void use_factory (T arg)
{
    Foo *p = factory(arg);
    // use p
    delete p; // remember to free the memory now that we no longer need it
}

Foo* use_factory (T arg)
{
    Foo *p = factory(arg);
    // use p
    return p; // caller must delete the memory
}
```

##### Caution: Managing Dynamic Memory Is Error-Prone

There are 3 common problems with using *new* and *delete* to manage dynamic memory:  
* Forgetting to *delete* memory: memory leak,
  cannot be detected until the application is run for a long enough time to actually exhaust memory.
* Using an object after it has been deleted:
  can sometimes be detected by **making the pointer null** after the delete.
* Deleting the same memory twice:
  can happen when two pointers address the same dynamically allocated object,

We can avoid *all* of the problems above by using smart pointers exclusively.  
The smart pointer will take care of deleting the memory *only* when there are no remaining smart pointers pointing to that memory.

##### Resetting the Value of a Pointer after a *delete* and Provide Only Limited Protection

When we *delete* a pointer, that pointer becomes invalid, becoming what is referred to as a *dangling pointer*.  
Dangling pointers have all the problems of uninitialized pointers.

We can avoid the problems with dangling pointers by deleting the memory associated with a pointer just before the pointer itself goes out of scope.  
If we need to keep the pointer around, we cna assign *nullptr* to the pointer after we use *delete*.

A fundamental problem with dynamic memory is that there can be *several* pointers that point to the same memory.


#### 12.1.3 Using *shared_ptr*s with *new*

Here are other ways to define and Change *shared_ptr*s:  
* shared_ptr<T> p(q):
  p manages the object to which the built-in pointer q points;
  q must point to memory allocated by *new* and must be convertible to T\*.
* shared_ptr<T> p(u):
  p assumes ownership from the *unique_ptr* u;
  make u null.
* shared_ptr<T> p(q, d):
  p assumes ownership for the object to which the built-in pointer q points.
  q must be convertible to T*.
  p will use the callable object d in place of *delete* to free q.
* shared_ptr<T> p(p2, d):
  p is a copy of the shared_ptr p2 except that p uses the callable object d in place of *delete*.
* p.reset()/ (q) / (q, d):
  If p is the only *shared_ptr* pointing at its object, *reset* frees p's existing object.
  If the optional built-in pointer q is passed, make p point to q, otherwise make p null.
  If d is supplied, will call d to free q; otherwise use *delete* to free q.

We can also initialize a smart pointer from a pointer returned by *new*.

``` C++
shared_ptr<double> p1; // shared_ptr that can point at a double
shared_ptr<int> p2(new int(42)); // p2 points to an int with value 42
```

The smart pointer constructors that take pointers are *explicit*,
hence we cannot implicitly convert a built-in pointer to a smart pointer;
we must use the **direct form** of initialization to initialize a smart pointer.

``` C++
shared_ptr<int> p1 = new int(1024); // error: must use direct initialization
shared_ptr<int> p2(new int(1024)); // ok: use direct initialization
```

A function that returns a *shared_ptr* cannot implicitly convert a plain pointer in its return statement.
We must explicitly bind a *shared_ptr* to the pointer we want to return.

``` C++
shared_ptr<int> clone(int p) {
    return new int(p); // error: implicit conversion to shared_ptr<int>
}

shared_ptr<int> clone(int p) {
    // ok: explicitly create a shared_ptr<int> from int*
    return shared_ptr<int> (new int(p));
}
```

By default, a pointer used to initialize a smart pointer must point to a **dynamic** memory because,
by default, smart pointer use **delete** to free the associated object.
  
We can bind smart pointers to pointers to **other** kinds of resources.  
However, to do so, we must supply our **own** operation to use *in place of delete*.

##### Don't Mix Ordinary Pointers and Smart Pointers ...

