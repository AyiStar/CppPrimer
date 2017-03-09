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
  
