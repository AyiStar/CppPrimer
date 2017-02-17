# Notes in Chapter 10

## Chapter 10. Generic Algorithms

Rather than adding lots of functionality to each container,
the library provides a set of **algorithms**, most of which are **independent** of any particular container type.  
These algorithms are *generic*: they operate on different types of containers and on elements of various types.


### 10.1 Overview

Most of the algorithms are defined in the *algorithm* header.  
There are also generic numeric algorithms defined in the *numeric* header.

Generic algorithms don't work directly on a container.
Instead, they operate by traversing a range of elements bounded by two iterators.

``` C++
int val = 42; // value we look for
// result will denote the element we want if it's in vec, or vec.cend() if not
auto result = find(vec.cbegin(), vec.cen(), val);
// repret the reault
cout << "The value " << val
     << (result == vec.cend()) ? " is not present" : " is present") << endl;
```

``` C++
string val = "a value"; // value we look for
// this call to find looks through string elements in a list
auto result = find(lst.cbegin(), lst.cend(), val);
```

``` C++
int ia[] = {27, 210, 12, 47, 109, 83};
int val = 83;
int* result = find(begin(ia), end(ia), val);

// search the elements starting from ia[1] up to but not including ia[4]
auto ret = find(ia + 1, ia + 4, val);
```

##### How the Algorithms Work

The job of *find* is to find a particular element in an **unsorted** sequence of elements.  
If we look close to the steps *find* must take, we can find that
**none** of the operations depends on the type of the container that holds the elements.
So long as there is an iterator that can be used to access the elements,
*find* does not depend in any way on the container type.

Iterators make the algorithms container independent,
but algorithms do depend on element-type **operations**.

##### Key Concept: Algorithms Never Execute Container Operations

The generic algorithms do **not** themselves execute container operations.
They operate solely in terms of iterators and iterator operations.  
Thus, algorithms **never change** the **size** of the underlying container.
But they **may change** the **values** of the elements stored in the container,
and they **may move** elements around within the container.
They do **not add or remove** elements directly.

There is a special class of iterators, the **inserters**, that do more than traverse the sequence to which they are bound.
When an algorithm operates on one of these iterators, the *iterator* may have the effect of adding elements to the container.


### 10.2 A First Look at the Algorithms

With only a few exceptions, the algorithms operate over a range of elements ("input range").
They always use their **first two** parameters to denote that range.
Those two are iterators denoting the first and **one past the last** elements to process.

#### 10.2.1 Read-Only Algorithms

*count* is defined in \<algorithm\>.
It takes a pair of iterators and a value,
and returns a count of how often that value appears.

*accumulate* is defined in \<numeric\>.
It takes a pair of iterators and an initial value for the sum,
and returns the sum of the elements in the range.

##### Algorithms and Element Types

