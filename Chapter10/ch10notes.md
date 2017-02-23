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


### 10.3 Customizing Operations

The library also defines versions of algorithms that let us supply our own operation to use in place of the default operator (\<, ==, etc.).

#### 10.3.1 Passing a Function to an Algorithm

##### Predicates

A **predicate** is an expression that can be called and that returns a value that can be used as a condition.  
The predicates used by library algorithms are either *unary predicates* (have a single parameter) or *binary predicate* (have two parameters).
The algorithms that take predicates call the given predicate on the elements in the input range.
As a result, it must be possible to convert the element type to the parameter type of the predicate.

The version of *sort* that takes a binary predicate uses the given predicate in place of \< to compare elements.

``` C++
// comparison function to be used to sort by word length
bool isShorter(const string &sl, const string &s2)
{
    return s1.size() < s2.size();
}
// sort on word length, shortest to longest
sort(words.begin(), words.end(), isShorter);
```

##### Sorting Algorithms

To keep the words of the same length in alphabetical order we can use the *stable_sort*,
which maintains the original order among equal elements.

``` C++
elimDups(words); // put words in alphabetical order and remove duplicates
// resort by length, maintaining alphabetical order among words of the same length
stable_sort(words.begin(), words.end(), isShorter);
for(const auto &s : words) // no need to copy the strings
    const << s << " "; // print each element separated by a space
cout << endl;
```

##### Partition algorithms

*partition* is defined in the *algorithm* header.
It takes a pair of iterators denoting the input range and a **unary** predicate.
It partitions the container so that values for which the predicate is *true* is in the first part
and those for which the predicate is *false* appear in the second part.
It returns an iterator just past the last element for which the predicate returned *true*.

#### 10.3.2 Lambda Expressions

The predicates we pass to an algorithm must have exactly **one or two** parameters,
depending on whether the algorithm takes a **unary** or **binary** predicate, respectively.

*find_if* takes a pair of iterators denoting the input range and a predicate.
It calls the predicate on each element in the input range.
It returns the **first** element for which the predicate returns a nonzero value,
or its end iterator if no such element is found.

##### Introducing Lambdas

An object or expression is **callable** if we can apply the *call* operator to it.

Callables in C++: functions, function pointers, classes that overload the function-call operator, and lambda expressions.

A **lambda expression** represents a callable unit of code.
It can be thought of as an unnamed, inline function.  
A lambda has a return type, a parameter list, and a function body.  
However, lambdas may be defined **inside** a function.

``` C++
// a lambda expression form
[capture list] (parameter list) -> return type { function body }
```

The **capture list** is an (often empty) list of local variables defined in the enclosing function.  
The return type, parameter list, and function body are the same as in any ordinary function.  
Unlike a function, a lambda must use a **trailing return** to specify its return type.

We can omit either or both of the parameter list and return type but must always include the capture list and function body.  
* Omitting the parentheses and the parameter list in a lambda is equivalent to specifying an empty parameter list.  
* If we omit the return type, the lambda has an inferred return type that depends on the code in the function body.
  If the function body is just a *return* statement, the return type is inferred from the type of the expression that is returned.
  Otherwise, the return type is *void*.
* Lambdas with function bodies that contain **anything other than** a single *return* statement that do not specify a return type return *void*.

``` C++
// f is a callable object that takes no arguments and returns 42
auto f = [] { return 42; }
```

We can **call** a lambda the same way we call a function by using the call operator.

##### Passing Arguments to a Lambda

The arguments in a call to a lambda are used to initialize the lambda's parameters.  
But a lambda may not have default arguments. So a call to a lambda always has as many arguments as the lambda has parameters.

``` C++
stable_sort(words.begin(), words.end(),
    [](const string &a, const string &b) { return a.size() < b.size(); });
```

##### Using the Capture List

Although a lambda may appear inside a function, it can use variables local to that function
**only** if it specifies which variables it intends to use.  
A lambda specifies the variables it will use by including those local variables in its capture list.

##### Calling *find_if*

Using lambdas, we can find the first element in words whose size is at least as big as sz:

``` C++
void biggies(vector<string> &words, vector<string>::size_type sz)
{
    // sort words and remove the duplicates
    elimDups(words);
    // resort words according to the length
    stable_sort(words.begin(), words.end(), isShorter);
    // get an iterator to the first element whose size() is >= sz
    auto wx = find_if(words.begin(), words.end(),
        [sz](const string &a) { return a.size() >= sz; });
    // compute the number of elements with size >= sz
    auto count = words.end() - wc;
    cout << count << " " << make_plural(count, "word", "s")
         << " of legth " << sz << " or longer" << endl;
}
```

##### The *for_each* Algorithm

*for_each* takes a pair of iterators denoting the input range and a callable object.
It calls the callable on each element in the input range.

``` C++
// print words of the geven size or longer, each one followed by a space
for_each(wc, words.end()),
    [](const string &s) { cout << s << " "; });
cout << endl;
```

We use the capture list only for nonstatic variables defined in the surrounding function.
A lambda can use names that are defined outside the function in which the lambda appears, and local *static*s, directly.


#### 10.3.3 Lambda Captures and Returns

When we define a lambda, the compiler generates a new unnamed class type
that corresponds to that lambda.  
When we pass a lambda to a function, we are defining both a new **type** and an **object** of that type:
the argument is an unnamed object of this compiler-generated class type.  
Similarly, when we use *auto* to define a variable initialized by a lambda, 
we are defining an object of the type generated from that lambda.

By default, the class generated from a lambda contains a **data member** corresponding to the variable **captured** by the lambda.
The data members of a lambda are also initialized when a lambda object is created.


Here is the lambda capture list:  
* \[\]: empty capture list. The lambda may not use variables from the enclosing function.
  A lambda may be local variables only if it captures them.
* \[names\]: names is a *comma-separated* list of names local to the enclosing function.
  By default, variables in the capture list are copied. A name preceded by & is captured by reference.
* \[&\]: implicit by reference capture list. Entities from the enclosing function used in the lambda body are used by reference.
* \[=\]: implicit by value capture list. Entities from the enclosing function used in the lambda body are copied into the lambda body.
* \[&, identifier_list\]: *identifier_list* is a comma-separated list of zero or more variables from the enclosing function.
  These variables are captured by value; any implicitly captured variables are captured by reference.
  The names in *identifier_list* must not be preceded by an &.
* \[=, reference_list\]: variables included in the *reference_list* are captured by reference;
  any implicitly captured variables are captured by value.
  The names in *reference_list* may not include *this* and must be preceded by an &.

##### Captured by Value

We can capture variables by **value** or by **reference**.  
Unlike parameters, the value of a captured variable is copied when the lambda is created, not when it is called.

Because the value is copied when the lambda is **created**,
subsequent changes to a captured variable have **no** effect on the corresponding value inside the lambda.

``` C++
void func1()
{
    size_t v1 = 42; // local variable
    // copies v1 into the callable object named f
    auto f = [v1] { return v1; };
    v1 = 0;
    auto j = f(); // j is 42; f stored a copy of v1 when we created it
}
```

##### Captured by Reference

A variable captured by reference acts like any other reference.
When we use the variable inside the lambda body, we are using the object to which that reference is bound.

``` C++
void func2()
{
    size_t v1 = 42; // local variable
    // the object f2 contains a reference to v1
    auto f2 = [&v1] { return v1; };
    v1 = 0;
    auto j = f2(); // j is 0; f2 refers to v1; it does not store it
}
```

Reference captures have the same problems and restrictions as reference returns.
If we capture a variable by reference, we **must** be certain that the referenced object **exists** at the time lambda is **executed**.

Reference captures are sometimes **necessary**.
For example, we might want our function to take an *ostream* on which to write.

``` C++
void biggies(vector<string> &words,
             vector<string>::size_type sz,
             ostream &os = cout, char c = ' ')
{
    // code to reorder words as before
    // statement to print count revised to print to os
    for_each(words.begin(), eords.end(),
             [&os] (const string &s) { os << s << c; });
}
```

We can also **return a lambda** from a function.  
The function might directly return a callable object or the function might return an object of a class that has a callable object as a data member.  
If the function returns a lambda, then that lambda must **not** contain reference captures.

##### Advice: Keep Your Lambda Captures Simple

A lambda capture stores information between the time the lambda is created
and the time when the lambda itself is executed.  
It is the programmer's responsibility to ensure that 
whatever information is captured has the intended meaning each time the lambda is executed.

As a rule, we can avoid potential problems with captures by **minimizing** the data we capture.  
Moreover, if possible, avoid capturing pointers or references.

##### Implicit Captures

We can let the compiler infer which variables we use from the code in the lambda's body.

##### Mutable Lambdas

By default, a lambda may **not** change the value of a variable that it copies *by value*.
If we want to be able to change the value of a captured variable,
we must follow the parameter list with the keyword **mutable**.  
Lambdas that are *mutable* may **not** omit the parameter list.

``` C++
void func3()
{
    size_t v1 = 42; // local variable
    // f can change the value of variables it captures
    auto f = [v1] () mutable { return ++v1; };
    v1 = 0;
    auto j = f(); // j is 43
}
```

Whether a variable captured by reference can be changed (as usual) depends only on
whether that reference refers to a *const* or non*const* type.

``` C++
void func4()
{
    size_t v1 = 42; // local variable
    // v1 is a reference to a non const variable
    // we can change that variable through the reference inside f2
    auto f2 = [&v1] { return ++v1; };
    v1 = 0;
    auto j = f2(); // j is 1
}
```

##### Specifying the Lambda Return Type

By default, if a lambda body contains any statements other than a *return*,
that lambda is assumed to return **void**.
Lambdas inferred to return *void* may not return a value.

``` C++
// ok: the lambda returns an int
transform(vi.begin(), vi.end(), vi.begin(),
          [] (int i) { return i < 0 ? -i : i;});
          
// error: the lambda returns void
transform(vi.begin(), vi.end(), vi.begin(),
          [] (int i)
          { if (i < 0) return -i; else return i;});
```

*transform* takes three iterators and a callable.
The first two iterators denote an input sequence and the third is a destination.
It calls the given callable on each element in the input sequence and writes the result to the destination.  
When the input iterator and the destination iterator are the same,
*transform* replaces each element in the input range with the result of calling the callable on that element.

*count_if* takes a pair of iterators denoting the input range and a predicate that it applies to each element in the given range.
It returns a count of how often the predicate is true.


#### 10.3.4 Binding Argument

If we need to do the same operation in many places, we should usually define a **function** rather than writing the same **lambda expressions**.  
If an operation requires **many** statements, it is ordinarily better to use a function.

It is usually straightforward to use a function in place of a lambda that has an **empty** capture list.  
It is not so easy to write a function to replace a lambda that **captures** local variables.

##### The Library *bind* Function

*bind* is defined in the *functional* header.
It can be thought of as a general-purpose **function adaptor**.  
It takes a callable object and generates a new callable that "adapts" the parameter list of the original object.

``` C++
auto newCallable = bind(callable, arg_list);
```

The *newCallable* is itself a callable object and *arg_list* is a comma-separated list of arguments that correspond to the parameters of the given *callable*.

The arguments in *arg_list* may include names of the form **_n**, where n is an integer.
These arguments are "placeholders" representing the parameters of *newCallable*.
They stand "in place of" the arguments that will be passed to *newCallable*.  
The number n is the position of the parameter in the generated callable.

##### Binding the *sz* Parameter of *check_size*

``` C++
bool check_size(const string &s, string::size_type sz)
{
    return s.size() >= sz;
}

// check 6 is a callable object that takes one argument of type string
// and calls check_size on its given string and the value 6
auto check6 = bind(check_size, _1, 6);

string s = "hello";
bool b1 = check6(s); // check6(s) calls check_size(s, 6);
```

Using *bind*, we can replace our original lambda-based call to *find_if*.

``` C++
auto wc = find_if(words.begin(), words.end(), bind(check_size, _1, sz));
```

##### Using placeholders Names

The **_n** names are defined in a namespace named *placeholders*.  
The namespace itself is defined in the *std* namespace.  
To use these names, we must supply the names of both namespaces.

We can use a different form of *using*:  
using namespace *namespace_name*;  
It says that we want to make all the names from *namespace_name* accessible to our program.

##### Arguments to *bind*

We can use *bind* to fix the value of a parameter.  
More generally, we can use *bind* to **bind** or **rearrange** the parameters in the given callable.

``` C++
// g is a callable object that takes two arguments
// the new callable will passits own arguments as the third and fifth arguments to f
// the first, second and fourth arguments to f are bound to the given values, a, b, and c, respectively
// when we call g, the first argument to g will be passed as the last argument to f
// the second argument to g will be passed as f's third argument.
auto g = bind(f, a, b, _2, c, _1);

// equivalent to f(a, b, Y, c, X);
g(X, Y); 
```

##### Using *bind* to Reorder Parameters

We can use *bind* to invert the meaning of *isShorter* by writing
``` C++
// sort on word length, shortest to longest
sort(words.begin(), words.end(), isShorter);

// sort on word length, longest to shortest
sort(words.begin(), words.end(), bind(isShorter, _2, _1));
```

##### Binding Reference Parameters

By default, the arguments to *bind* that are not placeholders are **copied** into the callable object that *bind* returns.  
As with lambdas, sometimes we have arguments that we want to bind but that we want to pass by reference or we might want to bind an argument that has a type that we cannot copy.

If we want to pass an object to *bind* without copying it, we must use the library **ref** function.

``` C++
for_each (words.begin(), words.end(), bind(print, ref(os), _1, ' '));
```

*ref* returns an object that contains the given reference and that is itself copyable.  
*cref* generates a class that holds a reference to const.  
They are all defined in the *functional* header.



### 10.4 Revisiting Iterators

In addition to the iterators that are defined for **each** of the containers,
the library defines several additional kinds of iterators in the *iterator* header:  
* **insert iterator**: these iterators are bound to a container and can be used to insert elements into the container.
* **stream iterator**: these iterators are bound to input or output streams and can be used to iterator through the associated IO stream.
* **reverse iterator**: these iterators move backward, rather than forward. The library contains, other than *forward_list*, have reverse iterators.
* **move iterator**: these special-purpose iterators **move** rather than **copy** their elements.


#### 10.4.1 Insert Iterators

An **inserter** is an iterator adaptor that takes a container and yields an iterator that adds elements to the specified container.  
When we **assign** a value through an insert iterator, the iterator **calls** a container operation to add an element at a specified position in the given container.

Here are insert iterator operations:  
* it = t: insert the value t at the current position denoted by it.
  Depending on the kind of insert iterator, and assuming c is the container to which it is bound,
  call c.push_back(t), c.push_front(t), or c.insert(t, p), where p is the iterator position given to inserter.
* it, ++it, it++: exist but **do nothing** to it. Each returns it.

There are three kinds of inserters. Each differs from the others as to **where** elements are inserted:  
* *back_inserter* creates an iterator that uses *push_back*.
* *front_inserter* creates an iterator that uses *push_front*.
* *inserter* creates an iterator that uses *insert*.
  This function takes a second argument, which must be an iterator into the given container.
  Elements are inserted ahead of the element denoted by the given iterator.
  
We can use *front_inserter* **only** if the container **has** *push_front*.  
Similarly, we can use *back_inserter* **only** if it **has** *push_back*.

When we call *inserter(c, iter), we get an iterator that, when used successively, inserts elements **ahead** of the element originally denoted by *iter*.  

``` C++
// If it is an iterator generated by inserter, then an assignment such as  
*it = val;  
// behaves as  
it = c.insert(it, val);  // it points to the newly added element
++it;  // increment it so that it denoted the same element as before
```

When we use *front_inserter*, elements are always inserted **ahead** of the then **first** element in the container.
Even if the position we pass to *inserter* initially denotes the first element,
as soon as we insert an element in front of that element, that element is no longer the one at the beginning of the container.

``` C++
list<int> lst = {1, 2, 3, 4};
list<int> lst2, lst3; // empty lists
// after copy completes, lst2 contains 4 3 2 1
copy(lst.cbegin(), lst.cend(), front_inserter(lst2));
// after copy completes, lst3 contains 1 2 3 4
copy(lst.cbegin(), lst.cend(), inserter(lst3, lst3.begin());
```

When we call *front_inserter*(c), we get an insert iterator that successively calls *push_front*.
As each element is inserted, it becomes the new first element in c.

*unique_copy* takes a pair of iterators denoting the input range and a third iterator denoting a destination into which to copy the unique elements.


#### 10.4.2 *iostream* Iterators

Even though the *iostream* types are not containers, there are iterators that can be used with objects of the IO types.

An **istream_iterator** reads an input stream, and an **ostream_iterator** writes an output stream.  
These iterators treat their corresponding stream as a **sequence of elements** of a specified type.  
Using a stream iterator, we can use the generic algorithms to read data from or write data to stream objects.

Here are *istream_iterator* operations:  
* istream_iterator<T> in(is); in reads values of type T from input stream is.
* istream_iterator<T> end; off-the-end iterator for an istream_iterator that reads values of type T.
* in1 ==/!= in2: in1 and in2 must read the same type. They are equal if they are both the end value or are bound to the same input stream.
* \*in: return the value read from the stream.
* in-\>mem: synonym for (\*in).mem.
* ++in, in++; read the next value from the input stream using the \>\> operator for the element type.
  As usual, the prefix version returns a reference to the incremented iterator.
  The postfix version returns the old value.

Here are *ostream_iterator* operations:  
* ostream_iterator<T> out(os); out writes values of type T to output stream os.
* ostream_iterator<T> out(os, d); out writes values of type T followed by d to output stream os.
  d points to a null-terminated character array.
* out = val: write val to the ostream to which out is bound using the \<\< operator.
  val must have a type that is compatible with the type that out can write.
* \*out, ++out, out++: these operations exist but do nothing to out. Each operator returns out.

##### Operations on *istream_iterator*s

When we create a stream iterator, we must specify the **type** of objects that the iterator will read or write.

An *istream_iterator* uses \>\> to read a stream.

When we create an *istream_iterator*, we can bind it to a stream,
or default initialize the iterator, which creates an iterator that we can use as the *off-the-end* value.

``` C++
istream_iterator<int> int_it(cin); // read ints from cin
istream_iterator<int> int_eof; // end iterator value
ifstream in("afile");
istream_iterator<string> str_it(in); // read strings from "afile"

istream_iterator<int> in_iter(cin); // read ints from cin
istream_iterator<int> eof; // istream "end" iterator

while(in_iter != eof) //while there's valid input to read
    // postfix increment reads the stream and returns the old value of the iterator
    // we dereference that iterator to get the previous value from the stream
    vec.push_back(*in_iter++);

// we can rewrite this program as
istream_iterator<int> in_iter(cin), eof; // read int from cin
vector<int> vec(in_iter, eof); // construct vec from an iterator range
```

An iterator bound to a stream is equal to the **end iterator** once its associated stream hits end-of-file or encounters an IO error.

##### *istream_iterator*s Are Permitted to Use Lazy Evaluation

When we bind an *istream_iterator* to a stream, we are **not** guaranteed that it will read the stream **immediately**.
The implementation is permitted to delay reading the stream until we use the iterator.

##### Operations on *ostream_iterators*

An *ostream_iterator* can be defined for **any** type that has an **output** operator (\<\<).  
When we create an *ostream_iterator*, we may optionally provide a *second* argument that specifies a character string to print following **each** element.
That string must be a **C-style** character string.  
We **must** bind an *ostream_iterator* to a specific stream. There is **no** empty or off-the-end *ostream_iterator*.

The \* and ++ operator **do nothing** on an *ostream_iterator*, so omitting them has no effect.
However, we prefer to write \*it++ = e; rather than it = e;
Because it uses the iterator consistently with how we use other iterator types.

Rather than writing the loop ourselves, we can more easily print the elements in a container by calling *copy*.
``` C++
copy(vec.begin(), vec.end(), out_iter);
cout << endl;
```

##### Using Stream Iterators with Class Types

