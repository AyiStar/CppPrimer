# Notes in Chapter 3

## Chapter 3 Strings, Vectors and Arrays

C++ defines a rich library of abstract data types.  
*string*: supports variable-length character strings.  
*vector*: defines variable-size collections.  
Both above are *abstractions* of the more primitive built-in type **array** type.

*iterator*: companion type which sre used to access
  the characters in a string or the elements in a vector.


### 3.1 Namespace *using* Declarations

*using* declaration: make a name from a namespace accessible directly.  
using *namespace* :: *name* makes *name* accessible without the *namespace* :: prefix.  
```C++
#include <iostream>
using std::cin;
using std::cout;
using std::endl;

int main()
{
    cout << "Enter two numbers:" << endl;
    int v1, v2;
    cin >> v1 >> v2;
    cout << "The sum of "" << v1 << " and " << v2
        << " is " << v1 + v2 << endl;
    
    return 0;
}
```

Each *using* declaration introduces a single namespace member.
This behavior lets us be specific about which names we're using.

Code inside *headers* ordinarily should **not use using declarations**.  
Otherwise, a program that didn't intend to use the specified library name
might encounter unexpected name conflicts.


### Library String Type

A **string** is a *variable-length* sequence of characters.

To use the string type, we must include the **string** header.

string is defined in the **std** namespace.

The most common ways to *initialize* strings:
* string s1: default initialization, s1 is the empty string.
* string s2(s1): s2 is a copy of s1.
* string s2 = s1: equivalent to s2(s1), s2 is a copy of s1.
* string s3("value"): s3 is a *copy* of the string literal, **not including the null**.
* string s3 = "value": equivalent to s3("value").
* string s4(n, 'c'): initialize s4 with n *copies* of the character 'c'.

**direct** and **copy** forms of initialization:
* When we initialize a variable using =, we are asking the compiler
  to *copy initialize* the object by copying the initializer on the right-hand side
  into the object being created. The newly created object is a **copy** of the given initializer.
* When we omit the =, we use *direct initialization*.
```C++
string s5 = "hiya"; // copy initialization
string s6("hiya"); // direct initialization
string s7(10, 'c'); // direct initialization
```

When we want to use several values, we can indirectly use the copy form
of initialization by explicitly creating a (temporary) object to copy:
```C++
string s8 = string(10, 'c'); // copy initialization, s8 is cccccccccc
// equivalent to
string temp(10, 'c');
string s8 = temp;
```
The form above is legal but less readable and offers no compensating advantage.

The most common string operations:
* os << s: write s onto output stream os. Return os.
* is >> s: read **whitespace-separated** string from is into s. Return is.
* getline(is,s): read a line of input from is into s. Return is.
* s.empty(): return true if s is empty, otherwise return false.
* s.size(): return the number of characters in s.
* s[n]: return a reference to the char at position n in s.
* s1 + s2: return a string that is the concatenation of s1 and s2.
* s1 = s2: replace characters in s1 with a copy of s2.
* s1 == s2: return true if s1 and s2 contain the same characters.
* s1 != s2: equality is case-sensitive.
* <, <=, >, >=: comparisons are case-sensitive and use dictionary ordering.

cin >> s operation discards any leading whitespace, and then reads characters
until the next whitespace character is encountered (this whitespace won't be read).  
It returns false condition if encountering EOF, and cin otherwise.

**getline** takes an input stream and a string,
reads the given stream up to and **including** the first newline
and stores what it read (**not including** the newline).  
If the first character is a newline, then the string is the empty string.

getline returns its istream operator argument, so we can use it as a condition.  

getline is defined in **std** namespace.

string::size() returns a *string::size_type* value:
* Most library types define several companion types,
  making it possible to use the library types in a machine-independent manner.
* string::size_type is an **unsigned** type *big enough* to store the result of any string.
* In C++11, we can use auto/decltype to ask the compiler to provide the type.
```C++
auto len = line.size();
```

Comparing strings with dictionary ordering:
* If two strings have the same length and contain the same characters,
  they are equal. Otherwise they are unequal.
* If two strings have different lengths and if every character in the shorter string
  is equal to the corresponding character of the longer string, then
  the shorter string is less than the longer one.
* If any characters at corresponding positions in the two strings differ, then
  the result of the string comparison is the result of comparing the first character
  at which the strings differ.
* The comparison is case-sensitive:
    * **any** lower case is **larger** than **any** upper case.
      We can think that the upper case appears earlier in a dictionary.
    * examples: 'a' > 'A'; 'a' > 'Z';
    * I think it's just comparing the ASCII codes.
  
s1 += s2 is equivalent to s1 = s1 + s2;

The string library lets us convert both character literals and character string literals to strings.  
When we mix strings and character strings or character literals,
at least one operand to each + operator must be of string type.
``` C++
string s1 = "hello", s2 = "world";
string s3 = s1 + " , " + s2 + '\n'; // ok
string s4 = s1 + ", "; // ok
string s5 = "hello" + ", "; // error
string s6 = s1 + ", " + "world"; // ok
string s7 = "hello" + ", " + s2; // error
```

For historical reasons and compatibility with C, string literals
are not standard library strings.

cctype functions:
* isalnum(c): true if c is a letter or a digit.
* isalpha(c): true if c is a letter.
* iscntrl(c): true if c is a control character.
* isdigit(c): true if c is a digit.
* isgraph(c): true if c is not a space but is printable.
* islower(c): true if c is a lowercase letter.
* isprint(c): true if c is a printable character 
  (i.e. a space or a character that has a visible representation).
* ispunct(c): true if c is a punctuation character
  (i.e. a character that is not a control character, a digit, a letter or a printable whitespace).
* isspace(c): true if c is whitespace
  (i.e. a apace, tab, vertical tab, return, newline or formfeed).
* isupper(c): true if c is an uppercase letter.
* isxdigit(c): true if c is a hexadecimal digit.
* tolower(c): if c is an uppercase letter, returns its lowercase equivalent; 
  otherwise returns c unchanged.
* toupper(c): if c is a lowercase letter, returns its uppercase equivalent;
  otherwise returns c unchanged.
  
Headers in C have names of the form *name*.h.  
The C++ versions of these headers are named c*name*.  
The names defined in the c*name* headers are defined inside **std** namespace.

If we want to do something to **every** character in a string, the **range for** statement is the best approach.  
It is a control statement that iterates through a specified collection of values.  
The syntactic form is
```C++
for ( declaration : expression)
    statement
```
Where *expression* is an object of a type that represents a sequence,
and *declaration* defines the variable that we'll use to access the underlying elements in the sequence.  
On each iteration, the variable in *declaration* is initialized from the value of the next element in *expression*.
```C++
// example
string str("some thing");
// print the characters in str one character to a line
for (auto c : str) // for every char in str
    cout << c << endl; // print the current character followed by a newline
```

There are two ways to access individual characters in a string:
* use a subscript operator ([]).
* use an iterator.

[] takes a string::size_type value that denotes the position of the character we want to access,
and returns a *reference* to the character at the given position.  
Subscripts for strings start at **zero**.  
The value in the subscript is referred to as a *subscript* or an *index*.

&& evaluates its right-hand operand *only if* the left-hand operand is true.


### 3.3 Library *vector* type

A **vector** is a collection of objects, all of which *have the same type*.  
Every object in the collection has an associated index, which gives access to that object.  
A vector is often referred to as a **container**.

vector is in header <vector>, namespace std.

vector is a **class template**.  
C++ has both *class and function templates*.  
A class template is a blueprint from which specific class types can be created.

Templates can be thought of as instructions to the compiler for generating classes or functions.  
The process that the compiler uses to create classes or functions from templates is called **instantiation**.

For a class template, we specify with class to instantiate by
supplying additional information.  
In detail, we supply it inside a pair of angle brackets following the template's name.
```C++
vector<int> ivec;
vector<Sales_item> Sales_vec;
vector<vector<string>> file;
```

vector is **not a type** but a template.

We **cannot** have a vector of *references* because they are not objects.

Some compilers may require the old-style declarations for a vector of vectors,
for example, vector<vector<int> >, rather than vector<vector<int>>.

The most common ways to define vectors:
* vector<T> v1: default initialization, v1 is empty.
* vector<T> v2(v1): v2 has a copy of each element in v1.
* vector<T> v2 = v1: equivalent of vector<T> v2(v1).
* vector<T> v3(n, val): v3 has n elements of type T with value val.
* vector<T> v4(n): v4 has n copies of a value-initialized object.
* vector<T> v5(a,b,c...): v5 has as many elements as there are initializers; elements are initialized by corresponding initializers.
* vector<T> v5 = (a,b,c...): equivalent to v5(a,b,c...).

Indeed, the most common way of using vectors is to
define an initially empty vector to which elements are added as their values become known at run time.

In C++11, we can *list initialize* a vector from a list of zero or more initial element values enclosed in curly braces.
```C++
vector<string> artivles = {"a", "an", "the"};
```

* When we use the copy initialization form (=), we can supply only a single initializer.
* When we supply an in-class initializer, we must either use copy initialization or usr curly braces.
* We can supply a list of element values only by using list initialization, not using parentheses.
```C++
vector<string> v1{"a", "an", "the"}; // ok
vector<string> v2("a", "an", "the"); // error
```

**value initialization** is a kind of initializations in which
built-in types are initialized to zero and
class types are initialized by the class's default.

There are two restrictions on this form of initialization:
* Some classes require an explicit initializer.
  If our vector holds objects of a such type,
  it is impossible to create vectors of such types by supplying only a size.
* When we supply an element count without also supplying an initial value,
  we must use the direct from of initialization:
```C++
vector<int> vi = 10;
// error: must use direct initialization to supply a size
```

In a few cases, what initialization means depends on whether we use curly braces or parentheses to pass the initializer(s):
```C++
vector<int> v1(10); // v1 has ten elements with value 0
vecter<int> v2{10}; // v2 has one element with value 10
vecter<int> v3(10,1); // v3 has ten elements with value 1
vecter<int> v4{10,1}; // v4 has two elements with value 10 and 1
```

If we use braces and there is no way to use the initializers to list initialize the object,
then those values will be used to construct the object.  
If list initialization isn't possible, the compiler looks for other way to initialize the object from the given value.
``` C++
vector<string> v5{"hi"}; // list initialization: v5 has one element
vector<string> v6("hi"); // error: can't construct a vector from a string literal
vector<string> v7{10}; // v7 has ten default-initialized elemenets
vector<string> v8{10, "hi"}; // v8 has ten elements with valu "hi"
```

The *push_back* operation takes a value and "pushes" that value
as a new **last** element onto the "back" of the vector.
``` C++
vector<int> v2;
for(int i = 0; i < 100; i++){
    va.push_back(i);
}
```

The standard requires that vector implementations can **efficiently** add elements at run time.
Moreover, vectors offers capabilities to allow us to further enhance run-time performance when we add elements.  
Starting with an empty vector and adding elements at run time is distinctly different from
how we use built-in arrays in C and in most other languages.

We must ensure that any loops we write are correct even if the loop changes the size of the vector.  
We cannot use a range for if the body of the loop adds elements to the vector.

vector provides only a few operations, here are the most important ones:
* v.empty(): return true if v is empty, false otherwise.
* v.size(): return the number of elements in v.
* v.push_back(t): add an element with value t to end of v.
* v[n]: return a reference to the element at position n in v.
* v1 = v2: replace the elements in v1 with a copy of elements in v2.
* v1 = {a,b,c...}: replace the elements in v1 with a copy of the elements in the comma-separated list.
* v1 == v2: return true if v1 and v2 have the same numbers of elements and each of them is equal.
* v1 != v2: return true if v1 == v2 is not true.
* <, <=, >, >=: have their normal meanings using directory ordering.

We can use a range for to process all the elements in a vector.
``` C++
for(auto &i : v){
    i *= i;
}
```

vector<T>::size() returns a value of the size_type defined by the corresponding vector type.  
To use size_type, we must name the type in which it is defined.
``` C++
vector<int>::size_type; // ok
vector::size_type; // error
```

We can compare two vectors **only if** we can compare the elements in those vectors.

The subscript operator on vector and string *fetches* an **existing** element;
it does not add an element.  
It is an error to subscript an element that does not exist.



### 3.4 Introducing Iterators

**iterator** is a type used to access and navigate among the elements of a *container*.

All of the library containers have iterators, but only a few of them support the subscript operator.

Technically speaking, a string is **not a container type**,
but string supports many of the container operations.

An iterator may be valid or invalid:
* A valid iterator either denotes an element or denotes a position one past the last element in a container.
* All other iterator values are invalid.

Types that have iterators have *members that return iterators*.  
In particular, these types have members named *begin* and *end*.  

The begin member returns an iterator that denotes the first element, if there is one. 
``` C++
auto b = v.begin();
auto e = v.end();
```

The end member returns an iterator positioned one past the end of the associated container.
It denotes a nonexistent element and is used as a marker indicating when we have processed all the elements.  
The iterator returned by end is often referred to as the **off-the-end iterator** or "the end iterator".

If the container is empty, begin returns the same iterator as the one returned by end.
They are both off-the-end iterator.

In general, we **do not know or care about** the precise type that an iterator has.

Iterators support only a few operations, which are listed here:
* \*iter: return a reference to the element denoted by iter.
* iter->mem: dereference iter and fetch the member named mem from the underlying element.
  Equivalent to (\*iter).mem.
* ++iter: increment iter to refer to the next element in the container.
* --iter: decrement iter to refer to the previous element in the container.
* iter1 == iter2: return true only if iter1 and iter2 denote the same element 
  or if they are the off-the-end iterator for the same container.
* iter1 != iter2: return true if iter1 == iter2 is false.

Dereferencing an invalid iterator or an off-the-end iterator has undefined behavior.

Example:
``` C++
string s("some thing");
if(s.begin() != s.end()){
    auto it = s.begin();
    *it = toupper(*it);
}
```

```C++
string s("some thing");
for(auto it = s.begin(); it != s.end() && !isspace(*it); ++it)
{
    *it = toupper(*it);
}
```

C++ programmers use != as a matter of habit.
This coding style applies equally well to various kinds of containers provided by the library.  
All of the library containers have iterators that define == and != operations.
Most of those iterators do not have the \< operator.

The library types that have iterators define types named *iterator* and *const_iterator*
that represent actual iterator types.
``` C++
vector<int>::iterator it; // can read and write vector<int> elements
string::iterator it2; // can read and write characters in a string
vector<int>::const_iterator it3; // can read but not write elements
string::const_iterator it4; // can read but not write elements
```
A const_iterator may read but not write the element it denotes, like a const pointer.
If a container is const, we may use only its const_container.
With a nonconst container, we can use either iterator or const_iterator.

The term *iterator* is used to refer:
* the concept of an iterator.
* the iterator type defined a container.
* an object as an iterator.

*A type is an iterator* if it supports a common set of actions.
Those actions let us access an element in a container and let us move from one element to another.  
Each container class defines *a type named iterator*, which supports the actions of an (conceptual) iterator.

If the object is const, begin and end return a const_iterator,
otherwise, they return iterator.
``` C++
vector<int> v;
const vector<int> cv;
auto it1 = v.begin(); // it1 has type vector<int>::iterator
auto it2 = v.begin(); // it2 has type vector<int>::const_iterator 
```

It is usually best to use a const type when we need to read but do not need to write to an object.  
To let us ask specifically for the const_iterator, C++11 introduced two new functions:
cbegin and cend. These members return iterators to the first and one past the last element in the container,
but regardless of whether the container is const, they return a const_iterator.

The parentheses in (*iter).mem are necessary.  
To simplify the expressions such as this one, -> operator is defined.
iter->mem is a synonym for (*iter).mem.

Any operation, such as push_back, that *changes the size of a vector*
potentially *invalidates all iterators into that vector*.  
Loops that use iterators should not add elements to the container to which the iterator refer.

All the library containers have iterators that support increment.  
Iterators for string and vector support additional operations
that can move an iterator *multiple* elements at a time.  
These operations, including all the relational operations, are often referred to as *iterator arithmetic*.
* iter +/- n: yield an iterator that many elements forward (backward) within the container.
  The resulting iterator must denote elements in, or one past the end, of the same container.
* iter +=/-= n: compound-assignment for iterator addition and subtraction.
* iter1 - iter2: yield the number that when added to iter2 yields iter1.
  The iterators must denote elements in, or one past the end of, the same container.
* \>, \>=, \<, \<=: One iterator is less than another if is refers to an element that appears in the container before the one referred to by the other iterator.
  The iterators must denote elements in, or one past the end of, the same container.

Examples:
``` C++
// compute an iterator to the element closest to the midpoint of vi
auto mid = vi.begin() + vi.size() / 2;
```

The subtraction between iterators of vectors or strings returns
a signed integral type named *difference_type*.

An example of doing *binary search* using iterators:
``` C++
// text must be sorted
// beg and end will denote the range we're searching
auto beg = text.begin(), end = text.end();
auto mid = text.begin() + (end - beg) / 2; // original midnight

// while there are still elements to look at and we haven't yet found sought
while(mid != end && *mid != sought)
{
    if(sought < *mid) // is the element we want in the first part?
        end = mid; // if so, adjust the range to ignore the second part
    else // the element we want is in the second half
        beg = mid + 1; // start looking with the element just after mid
    
    mid = beg + (end - beg) / 2; // new midpoint
}
```

\*(iter)++ is **different from** (*(iter))++ !



### 3.5 Arrays

An array is a data structure that is similar to the library vector type,
but *offers a different trade-off between performance and flexibility*.

An array is a **container** of unnamed objects of a single type that we access by position.

Arrays have **fixed size**. We **cannot add elements** to an array.  
Because of that, they sometimes offer *better run-time performance* for specialized applications.

If you don't know exactly how many elements you need, **use a vector**.

Arrays are a **compound type**.

An array declarator has the form a[d], where a is the name and d is the *dimension*.  
The dimension must be known at *compile time*, which means that the dimension must be a *constant expression*.
``` C++
unsigned cnt = 42; // not a constant expression
constexpr unsigned sz = 42; // constant expression
int arr[10]; // array of ten ints
int *parr[sz]; // array of 42 pointers to int
string bad[cnt]; // error: cnt is not a constant expression
string strs[get_size()]; // ok if get_size is constexpr, error otherwise
```

By default, the elements in an array are default initialized.  
As with variables of built-in type, a default-initialized array of built-in type
that is defined inside a function will have undefined values.

We cannot use auto to deduce the type from a list of initializers for an array.
We must specify a type for it.

Arrays hold only objects, so there are no arrays of references.

We can list initialize the elements in an array:
* We can omit the dimension, and then the compiler infers it from the number of initializers.
* If we specify a dimension, the number of initializers must not exceed the specified size.
* If the dimension is greater than the number of initializers, the initializers are used for the first elements
  and the remaining elements are value initialized.
  
Character arrays have an additional form of initialization:
* We can initialize such arrays from a string literal.
* When using this form, string literals end with a null character, copied into the array along with the characters.

We **cannot** initialize any array as a copy of another array,
**nor** is it legal to assign one array to another.  
Some compilers allow array assignment as a *compiler extension*,
but it is usually best to avoid nonstandard features.

Defining arrays that hold pointers is fairly straightforward,
defining a pointer or reference to an array is a bit more complicated.
``` C++
int *ptrs[10]; // an array of ten pointers to int
int &refs[10] = /* ? */; // error: no arrays of references
int (*Parray)[10] = &arr; // a pointer to an array of ten ints
int (&arrRef)[10] = arr; // a reference to an array of ten ints
```

By default, type modifiers bind **right to left**.
When using parentheses, they bind **inside to outside**.  
There are no limits on how many type modifiers can be used.
``` C++
int *(&arry)[10] = ptrs; // a reference to an array of ten pointers to int.
```

We can use a *range for* or the *subscript operator* to access elements of an array.

When we use a variable to subscript an array, we normally should define that variable to have type
**size_t**, which is a machine-specific *unsigned type* that is **guaranteed to be large enough to hold the size of any object in memory**.  
The type size_t is defined in the **cstddef** header.

As in the case of string or vector, it is best to use a range for
when we want to traverse the entire array.

The most common source of security problems are *buffer overflow* bugs.
Such bugs occur when a program fails to *check a subscript* and 
mistakenly *uses memory outside the range* of an array or similar data structure.

In C++, pointers and arrays are closely intertwined:
* When we use an array, the compiler ordinarily *converts the array to a pointer*.
* Normally, we obtain a pointer to an object by using &.
  Generally speaking, & may be applied to any object.
* The element in an array are objects.
  When we subscript an array, the result is the object at that location in the array.
* Arrays have a special property: in most places when we use an array,
  the compiler automatically substitutes a pointer to the first element.
``` C++
string *p2 = nums; // equivalent to p2 = &nums[0]
```

When we use an array as an initializer for a variable defined using auto,
the deduced type is a **pointer**, not a **array**.
``` C++
int ia[] = {0,1,2,3,4,5,6,7,8,9};
auto ia2(ia); // ia2 is an int* that points to the first element in ia
// equivalent to
// auto ia2(&ia[0])
```
This conversion **does not** happen when we use *decltype*.  
The type returned by decltype(ia) is array of ten ints.