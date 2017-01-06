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


