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

When using *accumulate*, it **must be possible** to add the element type to the type of the sum.

``` C++
// ok: concatenate each element in v onto a string that starts out as the empty string
string sum = accumulate(v.begin(), v.cend(), string(""));

// error: no plus operation on const char*
string sum = accumulate(v.cbegin(), v.cend(), "");
```

It is best to use **cbegin()** and **cend()** with algorithms that read, but do not write, the elements.
However, if you plan to use the iterator returned by the algorithm to change an element's value,
then you need to pass **begin()** and **end()**.

##### Algorithms That Operate on Two Sequences

*equal* is a read-only algorithm which lets us determine whether two sequences hold the same values.  
* It compares each element from the first sequence to the corresponding element in the second.  
* It returns *true* if the corresponding elements are equal, *false* otherwise.  
* It takes three iterators: the first two denote the range of elements in the first sequence, 
  the third denotes the first element in the second sequence.
* Because *equal* operates in terms of iterators, we can call *equal* to compare elements in containers of **different** types.
  Moreover, the **element types** also need not be the same so long as we can use == to compare the element types.
* It makes an assumption that the second sequence is at least as big as the first.


#### 10.2.2 Algorithms That Write Container Elements

When we use an algorithm that assign to elements, we must take care to ensure
that the sequence into which the algorithm writes is at least as large as the number of elements we ask the algorithm to write.

*fill* is an algorithm that takes a pair of iterators that denote a range and a third argument that is a value.
It assigns the given value to **each** element in the input sequence.

##### Key Concept: Iterator Arguments

Some algorithms read elements from two sequences.  
The elements that constitute these sequences can be stored in different kinds of containers.  
Moreover, the element types in the two sequences are not required to match exactly.  
Those which use a single iterator to denote the second sequence assume that the second sequence is at least as large as the first.

##### Algorithms Do Not Check Write Operations

Some algorithms take an iterator that denotes a separate destination.
These algorithms assign new values to the elements of a sequence starting at the element denoted by the destination iterator.

*fill_n* takes a single iterator, a count, and a value.
It assigns the given value to the specified number of elements starting at the element denoted to by the iterator.  
It assumes that it is safe to write the specified number of elements starting from the denoted element.

##### Introducing back_inserter

An **insert iterator** is an iterator that *adds* elements to a container.
When we assign to a container element through an insert iterator, a new element equal to the right-hand value is added to the container.

*back_inserter* is a function defined in the *iterator* header.

``` C++
vector<int> vec; // empty vector
auto it = back_inserter(vec); // assigning through it adds elements to vec
*it = 42; // vec now has one element with value 42
```

We frequently use *back_inserter* to create an iterator to use as the destination of an algorithm.

``` C++
vector<int> vec; // empty vector
// ok: back_inserter creates an insert iterator that adds elements to vec
fill_n(back_inserter(vec), 10, 0); // appends ten elements to vec
```

##### Copy Algorithms

*copy* takes two iterators that denote an input range and one that denotes the beginning of the destination sequence.
It copies elements from its input range into elements in the destination.
It returns the (incremented) value of its destination iterator.  
The destination passed to *copy* must be at least as large as the input range.

``` C++
int a[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
int a2[sizeof(a1) / sizeof(*a1)]; // a2 has the same size as a1
// ret points just past the last element copied into a2
auto ret = copy(begin(a1), end(a1), a2); // copy a1 into a2
```

*replace* reads a sequence and replaces every instance of a given value with another value.
It takes two iterators denoting the input range, and two values.
It replaces each element that is equal to the first value with the second.

``` C++
// replace any element with value 0 with 42
replace(ilst.begin(), ilst.end(), 0, 42);
```

*replace_copy* leave the original sequence unchanged.
It takes a third iterator argument denoting a destination in which to write the adjusted sequence.

``` C++
// use back_inserter to grow destination as needed
replace_copy(ilst.cbegin(), ilst.cend(), back_inserter(ivec), 0, 42);
// after the call, ilst is unchanged, and ivec contains a copy of ilst with the exception that every element in ilst with the value 0 has the value 42 in vec.
```


#### 10.2.3 Algorithms That Reorder Container Elements

*sort* arranges the elements in the input range into sorted order
using the **element type's** \< operator.

##### Eliminating Duplicates

Once the sequence has been sorted (so that duplicated elements appear adjacent to each other),
we can use *unique* to reorder the sequence so that the unique elements appear in the first part of the sequence.  

``` C++
void elimDups(vector<string> &words)
{
    // sort words alphabetically so we can find the duplicates
    sort(words.begin(), words.end());
    // unique reorders the input range so that each word appears once in the front portion of the range and returns an iterator one past the unique range
    auto end_unique = unique(words.begin(), words.end());
    // erase uses a vector operation to remove the nonunique elements
    words.erase(end_unique, words.end());   
}
```

##### Using *unique*

*unique* takes a pair of iterators denoting the input range,
and returns an iterator denoting one past the last unique element.

##### Using Container Operations to Remove Elements

Because algorithms cannot do container operations, we should use *erase* member to actually remove the duplicated elements.

