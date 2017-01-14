# Notes in Chapter6

## Chapter6. Functions

A **function** is a block of code with a name.  
We *execute* the code by *calling* the function.  
A function may take zero or more *arguments* and (usually) yields a result.

### 6.1 Function Basics

A function definition typically consists of:
* a return type.
* a name.
* a list of zero or more parameters: which are specified in a comma-separated list enclosed in parentheses.
* a body: the actions that the function performs 
  and that are specified in a statement block.
  
We execute a function through the **call operator ()**.  
It takes an expression that **is a function** or **points to a function**.  
Inside the parentheses is a comma-separated list of arguments,
which are used to **initialize** the function's parameters.  
The type of a call expression is the return type of the function.

A function call does teo things:
* Initialize the function's parameters from the corresponding arguments.
* Transfer control to that function. Execution of the calling function is suspended and execution of the called function begins.

Execution of a function begins with the implicit definition and initialization of its parameters.  
Execution of a function ends when a return statement is encountered.

A return statement does two things like a function call:
* Return the value (if any) in the return.
* Transfer control out of the called function back to the calling function.  

The value returned by the function is used to initialize the result of the call expression.  
Execution continues with whatever remains of the expression in which the call appeared.

**Arguments** are the initializers for a function's parameters.  
There is **no guarantee** about the order in which arguments are evaluated.

The type of each argument must match the corresponding parameter in the same way
that the type of any initializer must match the type of the object it initializes.

We must pass **exactly** the same number of arguments as the function has parameters,
so that parameters are always initialized.

A function's **parameter list** can be empty but cannot be omitted.  
Typically we define a function with no parameters by writing an empty parameter list.  
For compatibility with C, we also can use the keyword *void* to indicate there are no parameters.

A parameter list typically consists of a comma-separated list of parameters,
each of which looks like a declaration with a single declarator.  
**Even** when the types of two parameters are the same, the type must be **repeated**.  
No two parameters can have the same name,
moreover, local variables at the outermost scope of the function may not use the same as any parameter.

Parameter names are **optional**, but there is no way to use an unnamed parameter,
so parameters ordinarily have names.  
Occasionally a function has a parameter that is **not used**.
Such parameters are often left unnamed to indicate that they aren't used.  
Leaving a parameter unnamed **does not** change the number of arguments that a call must supply.  
A call must supply an argument for every parameter, even if the parameter isn't used.

Most type can bu used as the return type of a function, including *void*.  
However, the return type may not be an array type or a function type,
but can be a pointer to an array or a function.

In C++, **names** have **scope**, and **objects** have **lifetimes**:
* The scope of a name is the **part of the program's text** in which that name is visible.
* The lifetime of an object is the **time during the program's execution** that the object exists.

A function body is a statement block, and thus forms a new scope.
Parameters and variables defined inside a function body are referred to as *local variables*.  
They are local to that function and hide declarations of the same name made in an outer scope.

Objects defined outside any function exist throughout the program's execution.  
Such objects are **created when the program starts** (not when declared or defined)
and are not destroyed until the program ends.  

The lifetime of a local variable depends on how it is defined.

The objects that correspond to ordinary local variables
are created when the function's control path **passes through the variable's definition**.
They are destroyed when control **passes through the end of the block** in which the variable is defined.

Objects that exist only while a block is executing are known as **automatic objects**.  
After execution exits a block, the values of the automatic objects created in that block are *undefined*.

Parameters are automatic objects.  
Storage for the parameter is allocated when the function begins.
They are destroyed when the function terminates.

It can be useful to have a local variable whose lifetime continues across calls to the function.  
We obtain such objects by defining a local variable as **static**.  

Each *local static object* is initialized **before the first time execution passes through the object's definition**.  
They are destroyed **when the program terminates**.

If a local static has no explicit initializer, it is **value initialized**.

The name of a function must be declared before we can use it.  
A function may be defined only once but may be declared multiple times.  
With one exception, we can declare a function that is not defined so long as we never use it.

A function declaration is just like a function definition,
except that a declaration has no function body, and has a semicolon at the end.  
Thus there is no need for parameter names. They are often omitted in a declaration.
Yet they can be used to help users of the function understand what the function does.

Function declarations are also known as the function prototype.

Functions should be declared in header files and defined in source files, as with variables.  
The header that *declares* a function should be included in the source file that *defines* that function.

**Separated compilation** lets us split our programs into several files,
each of which can be compiled independently.
``` command-line
# main.cc has the main function
# func.cc has the definitions of other functions
# main.cc includes the header file which has the declarations of the functions in func.cc
$ CC main.cc func.cc # generates a.out

$ CC -c main.cc # generates main.o
$ CC -c func.cc # generates func.o
$ CC main.o func.o # generates a.out
```


### 6.2 Argument Passing

Parameter initialization works **the same way** as variable initialization.

The type of a parameter determines the interaction between the parameter and its argument.  
* If the parameter is a reference, then the parameter is bound to its argument.  
  When a parameter is a reference, we say that its corresponding argument is "**passed by reference**".
* Otherwise, the argument's value is copied, and the parameter and argument are independent objects.
  We say such arguments are "**passed by value**" or that the function is "**called by value**".
  

#### 6.2.1 Passing Arguments by Value

When the argument is passed by value, nothing the function does to the parameter
can affect the argument.

Pointers behave like any other nonreference type.  
However, a pointer also gives us indirect access to the object to which that pointer points.
We can change the value of that object by assigning through the pointer.


#### 6.2.2 Passing Arguments by Reference

It can be inefficient to copy objects of large class types or large containers.  
Moreover, some class types (including the IO types) cannot be copied.  
Functions must use reference parameters
to operate on objects of a type that cannot be copied or to avoid copies.  

Functions should use reference to const
for reference parameters they do not need to change.

A function can return only a single value.
However, sometimes a function has more than one value to return.  
Reference parameters let us effectively return multiple results.  
Example
``` C++
// return the index of the first occurrence of c in s
// the reference parameter occurs counts how often c occurs
string::size_type find_char(const string &s, char c, string::size_typpe &occurs)
{
    auto ret = s.size(); // position of the first occurrence, if any
    occurs = 0; // set the occurrence count number
    for(decltype(ret) i = 0; i != s.size(); ++i){
        if(s[i] == c){
            if(ret == s.size())
                ret = i; // remember the occurrence count
            ++occurs; // increment the occcurrence count
        }
    }
    return ret; // count is returned implicitly in occurs
}
```


#### 6.2.3 const Parameters and Arguments

When we copy an argument to initialize a parameter, top-level consts are ignored.
So top-level const on parameters are ignored.  
We can pass either a const or a nonconst object to a parameter that has a top-level const.

In C++, we can define several different functions that have the same name.
However, we can do so only if their parameter lists are **sufficiently different**.  
Because top-level consts are ignored, we can pass exactly the same types to either version of
const and nonconst.
Despite appearances, the parameter lists don't differ.
``` C++
void fcn(const int i) { /* fcn can read but not write to i */ }
void fcn(int i) { /* ... */ } // error: redefines fcn(int)
```

We can initialize an object with a low-level const from a nonconst object
but not vice versa, and a plain reference must be initialized from an object of the same type.  
Exactly the same initialization rules apply to parameter passing.

It is a somewhat common mistake to define parameters that a function does not change
as (plain) references.  
Doing so gives the function's caller the misleading impression that 
the function might change its argument's value.  
Moreover, using a reference instead of a reference to const unduly limits the type of arguments
that can be used with the function.
For example, we cannot pass a const object, or a literal, or an object that requires conversion
to a plain reference parameter.


#### 6.2.4 Array Parameters

Arrays have two special properties that affect how we define and use functions that operate on them:
* We cannot copy an array. So we cannot pass an array by value.
* When we use an array, it is (usually) converted to a pointer.
  So when we pass an array to a function, we are actually passing a pointer to the array's first element.
  
We can write a parameter that *looks like* an array:
``` C++
// despite appearances, these three declarations of print are equivalent
// each function has a single parameter of type const int*
void print(const int*);
void print(const int[]); // shows the intent that the function takes an array
void print(const int[10]); // dimension for documentation purposes (at best)
// when the compiler checks a call to print, it checks only that the argument has type const int*
// the size of the array is irrelevant
```

Functions ordinarily don't know the size of the array they are given.
They must rely on additional information provided by the caller.

There are three common techniques used to manage pointer parameters:
* Using a marker to specify the extent of an array.  
  It requires the array itself to contain an end marker. C-style character strings are an example.
  This works less well with data such as ints.
* Using the standard library conventions.  
  To pass pointers to the first and one past the last element in the array.
  This approach is inspired by techniques used in the standard library.
  We can use the standard *begin* and *end* functions.
* Explicitly Passing a Size Parameter.  
  It is common in C programs and older C++ programs.
  
When a function does not need write access to the array elements,
the array parameter should be a pointer to **const**.  
A parameter should be a plain pointer to a nonconst type *only if*
the function needs to change element values.

We can define a parameter that is a reference to an array.
``` C++
void print(int (&arr)[10])
{
    for (auto elem : arr)
        cout << elem < endl;
}
```
Because the size of an array is *part of its type*,
it is safe to rely on the dimension in the body of the function.  
However, we may call the print function above only for an array of exactly 10 ints.

A multidimensional array is passed as a pointer to its first element.  
The size of the second (and any subsequent) dimension is part of the element type and must be specified.
``` C++
// matrix points to the first element in an array whose elements are arrays of ten ints
void print(int (*matrix)[10], in rowSize)
{ /* ... */ }
// is equivalent to
void print(int matrix[][10], int rowSize)
{ /* ... */ }
```


#### 6.2.5 main: Handling Command-Line Options

We sometimes need to pass arguments to main.  
The most common use of arguments to main is 
to let the user specify a set of options to guide the operation of the program.  
``` command-line
$ prog -d  -o ofile data0
```
Such command-line options are passed to main in two (optional) parameters:
``` C++
int main(int argc, char *argv[])
{ /* ... */ }
```
The second parameter, argv, is an array of pointers to C-style character strings.  
The first parameter, argc, passes the number of strings in that array.  
When arguments are passed to main, the first element in argv points either to the name of the program or to the empty string.
Subsequent elements pass the arguments provided on the command line.  
The element just past the last pointer is **guaranteed to be 0**.

Remember that the optional arguments begin in argv[1].


#### 6.2.6 Functions with Varying Parameters

C++11 provides two primary ways to write a function that takes a varying number of arguments:
* If all the arguments have the same type, we can pass a library type named *initializer_list*.
* If the argument types vary, we can write a special kind of function, known as a variadic template.

C++ also has a special parameter type, *ellipsis*,
that can be used to pass a varying number of arguments.  
However, it should be used only in programs that need in interface to C functions.

An *initializer_list* parameter is a **library type** that
represents an array of values of the specified type.  
This type is defined in the header \<initializer_list\>.

Here are the operations that initializer_list provides:
* initializer_list<T> lst: Default initialization; an empty list of elements of type T.
* initializer_list<T> lst(a,b,c,...): lst has as many elements as there are initializers;
  elements are copied of the corresponding initializers.
  Elements in the list are **const**.
* lst2(lst) / lst2 = lst: Copy or assign an initializer_list does not copy the elements in the list.
  After the copy, the original and the copy share the elements.
* lst.size(): Numbers of elements in the list.
* lst.begin / lst.end(): Return a pointer to the first and one past the last element in lst.

*initializer_list* is a template type like vector.
We must specify the type of the elements when we define it.

Unlike a vector, the elements in an initializer_list are **always const** values.  
There is **no way** to change the value of an element in an initializer_list.

Example:
``` C++
void
error_msg(initializer_list<string> il)
{
    for(auto beg = il.begin(); beg != il.end(); ++beg)
        cout << *beg << " ";
    cout << endl;
}
```

When we pass a sequence of values to an initializer_list parameter,
we must **enclose** the sequence in curly braces.

We can use a range for to process an initializer_list.

Ellipsis parameters are in C++ to allow programs to interface to C code
that uses a C library facility named *varargs*.  
Generally an ellipsis parameter should not be used for other purposes.  
It should also be used only for types that are common to both C and C++.

An ellipsis parameter may appear only as the **last** element in a parameter list
and may take either of two forms:
* void foo(parm_list, ...); In this form, the comma following the parameter declarations is optional
* void foo(...);



### 6.3 Return Types and the *return* statement

There are two forms of return statements:
* return;
* return *expression*;


#### 6.3.1 Functions with No Return Value

A return with no value may be used only in
a function that has aa return type of *void*.  

Functions that return void are **noe required** to contain a return.  
In a void function, an implicit return takes place after the function's last statement.

Typically, void functions use a return to exit the function **at an intermediate point**.
 
A function with a void return type may use the second form of the return statement
only to return the result of calling another function that returns void.  
Returning any other expression from a void function is a compile-time error.


#### 6.3.2 Functions That Return a Value

Every return in a function with a return type other than void
must return a value that has the same type as the function return type,
or a type that can be implicitly converted to that type.

The compiler may or may not detect whether each case in the program can
return an appropriate value.

Values are returned exactly the same way as variables and parameters are initialized:  
The return value is used to initialize a temporary at the call site,
and that temporary is the result of the function call.

When a function returns a reference, that reference is just another name for the object to which it refers.
``` C++
// return a reference to the shorter of two strings
const string &shorterString(const string &s1, const string &s2)
{
    return (s1.size() <= s2.size() ? s1 : s2);
}
```
In the example above, the strings are not copied
when the function is called or when the result is returned.

Never return a reference or pointer to a **local object**.  
When a function completes, its storage is freed.
After a function terminates, references and pointers to local objects 
refer to and points to memory that is no longer valid.
``` C++
// disaster: this function returns a reference to a local object
const string &manip()
{
    string ret;
    // transform ret in some way
    if(!ret.empty())
        return ret; // WRONG: returning a reference to a local object!
    else
        return "Empty"; // WRONG: "Empty" is a local temporary string
}
```

The call operator has the same precedence as the dot and arrow operators.  
The call operator is left associative.  
Thus, if a function returns a pointer, reference, or object of class type,
we can use the result of a call to call a member of the resulting object.

Calls to functions that return references are lvalues;  
other return types yield rvalues.
``` C++
char &get_val(string &str, string::size_type ix)
{
    return str[ix];
}

int main()
{
    string s("a value");
    cout << s << endl;
    get_val(s,0) = 'A';
    cout << s << endl;
    return 0;
}
```

In C++11, functions can return a braced list of values.  
The list is used to initialize the temporary that represents the function's return.
If the list is empty, that temporary is value initialized.
Otherwise, the value of the return depends on the function's return type.

Example:
``` C++
vector<string> process()
{
    // ...
    // expected and actual are strings
    if(expected.empty())
        return {}; // return an empty vector
    else if(expected == actual)
        return {"functionX", "okay"}; // return list-initialized vector
    else
        return {"functionX", expected, actual};
}
```

In a function that returns a built-in type,
a braced list may contain at most one value,
and that value must not require a narrowing conversion.  
If the function returns a class type,
then the class itself defines how the initializers are used.

The main function, which has a return of int type, as an exception,
is allowed to terminate without a return.  
If control reaches the end of a main and there is no return,
then the compiler implicitly inserts a return of **0**.

To make return values of main machine independent,
the header \<cstdlib\> defines two preprocessor variables that we can use to indicate success or failure.  
Because these are preprocessor variables, we must not precede them with std::,
nor may we mention them in using declarations.
``` C++
int main()
{
    if(some_failure)
        return EXIT_FAILURE; // defined in cstdlib
    else
        return EXIT_SUCCESS; // defined in cstdlib
}
```

A function that calls **itself**, either *directly* or *indirectly*,
is a **recursion function**.

There must always be a path through a recursive function
that does not involve a recursive call;
otherwise, the function will recurse "forever".
Such functions are sometimes described as containing a recursion loop.

The main function **may not** call itself.


#### 6.3.3 Returning a Pointer to an Array

A function **cannot** return an array because we cannot copy an array.
But a function can return a pointer or a reference to an array.

We can define a function that returns a pointer or a reference to an array
by using a type alias:
``` C++
typedef int arrT[10]; // arrT is a synonym for the type array of ten ints
using arrtT = int[10]; // equivalent declaration of arrT
arrT* func(int i); // func returns a pointer to an array of ten ints
```

To declare func without a type alias, we must remember that
the dimension of an array follows the name being defined.  
If we want to define a function that returns a pointer to an array,
the dimension must **follow** the function's name.
And, the parameter list **precedes** the dimension.  
Hence, the form of a function that returns a pointer to an array is:  
*Type* (\**function(parameter_list)*)[*dimension*]  
The parentheses around (\*function(parameter_list)) are necessary.
Without them, we would be defining a function that returns an array of pointers.

In C++11, we can simplify the declaration of func by using **trailing return type**.
They can be defined for any function, but are most useful for functions with complicated return types.

A trailing return type follows the parameter list and is preceded by -\>.
To signal that the return follows the parameter list, we use auto where the return type ordinarily appears:
``` C++
// func takes an int atgument and returns a pointer to an array of ten ints
auto func(int i) -> int(*)[10];
```
Because the return type comes after the parameter list,
it is easier to see that func returns a pointer and that pointer points to an array of ten ints.

As another alternative, if we know the array(s) to which our function can return a pointer,
we can use decltype to declare the return type.
``` C++
int odd[] = {1,3,5,7,9};
int even[] = {0,2,4,6,8};
// returns a pointer to an array of 5 ints
decltype(odd) *arrPtr(int i)
{
    return (i % 2) ? &odd : &even;
}
```

The only tricky part is that we must remember that
decltype does not automatically convert an array to its corresponding pointer type.



### 6.4 Overloaded Functions

Functions that have the **same name** but **different parameter lists**
and that appear in the **same scope** are **overloaded**.  
When we call these functions, the compiler can deduce which function we want based on the argument type we pass.

Function overloading eliminates the need to invent and remember names
that exist only to help the compiler figure out which function to call.

The main function **may not** be overloaded.

Overloaded functions must differ in the number or the type(s) of their parameters.  
It is an error for two functions to differ only in terms of their *return types*.

Two parameter lists can be identical even if they don't *look the same*.  
For example, type alias or parameter names can both make the list *seem different*.

Top-level const has **no effect** on the objects that can be passed to the function.  
A parameter that has a top-level const is **indistinguishable** from one without a top-level const.
``` C++
Record lookup(Phone);
Record lookup(const Phone); // redeclare Record lookup(Phone)

Record lookup(Phone*);
Record lookup(Phone* const*); // redeclare Record lookup(Phone*)
```

On the other hand, we can overload based on whether the parameter list
is a reference (or pointer) to the const or nonconst version of a given type,
i.e. low-level const.  
In these cases, the compiler can use the *constness* of the argument to distinguish which function to call.
* Because there is **no** conversion from const, we can pass a const object (or a pointer to const)
  only to the version with a const parameter.
* Because there is a conversion to const, we can call **either** function on a nonconst object or a pointer to nonconst.  
  However, the compiler will prefer the **nonconst** versions when we pass a nonconst object or pointer to nonconst.

*const_casts* are most useful in the context of overloaded functions.
``` C++
// return a reference to the shorter of two strings
const string &shorterString(const string &s1, const string &s2)
{
    return (s1.size() <= s2.size()) ? s1 : s2;
}

// version of nonconst
string &shorterString(string &s1, string &s2)
{
    auto &r = shorterString(const_cast<const string&>(s1), const_cast<const string&>(s2));
    return const_cast<string &> (r);
}
```

There are cases where providing different function names adds information that makes the program easier to understand.

**Function matching** (or **overload resolution**) is the process by which
a particular function call is associated with a specific function from a set of overloaded functions.
* Often the functions in the overloaded set differ in terms of 
  the number of arguments, or the types of the arguments are **unrelated**.  
  In such cases, it is easy to determine which function is called.
* When the overloaded functions have the same number of parameters and
  those parameters are related by conversions, it can be less obvious which function is called.

For any given call to an overloaded function, there are 3 possible outcomes:
1. The compiler finds exactly one function that is a **best match** for the actual arguments
   and generates code to call that function.
2. There is no function with parameters that match the arguments in the call,
   in which case the compiler issues an error message that there was **no match**.
3. There is more than one function that matches and none of the matches is clearly best.
   This case is also an error; it is an **ambiguous call**.
   
   
#### 6.4.1 Overloading and Scope

Ordinarily, it is a **bad** idea to declare a function locally.

Overloading has no special properties with respect to scope.  
If we declare a name **(including function names and variable names)** in an inner scope, that name *hides* uses of that name declared in an outer scope.  
Names do not overload across scopes.

In C++, name lookup happens **before** type checking.  
The compiler first looks up the name, so even if the use of the local name is invalid,
the names in outer scopes are still hidden.



### 6.5 Features for Specialized Uses


#### 6.5.1 Default Arguments

Some functions have parameters that are given a particular value in most,
but **not all**, calls.
In such cases, we can declare that common value as a **default argument** for the function.  
Functions with default arguments can be called with **or without** that argument.
``` C++
typedef string::size_type sz;
string screen(sz ht = 24, sz wid = 80, char backgrnd = ' ');
```
Here we've provided a default argument for each parameter.  
A default argument is specified as an initializer for a parameter in the parameter list.

If a parameter has a default argument, **all** the parameters that **follow** it must also have default arguments.
The default arguments are used for the trailing (right-most) arguments of a call.

If we want to use the default argument, we omit that argument when we all the function.

Part of the work of designing a function with default argument is
ordering the parameters so that those least likely to use a default value appear first
and those most likely to use a default appear last.

Although it is normal practice to declare a function once inside a header,
it is legal to redeclare a function multiple times.  
However, each parameter can have its default specified **only once** in a given scope.  
Thus, any subsequent declaration can add a default only for a parameter
that has not previously had a default argument.  
Defaults can be specified only if all parameters to the right already have defaults.
 
Default arguments ordinarily should be specified with the function declaration
in an appropriate header.

Local variables **may not** be used as a default argument.  
Except that restriction, a default argument can be **any** expression that
has a type that is convertible to the type of the parameter.
``` C++
// the declarations of wd, def, and ht must appear outside a function
sz wd = 80;
char def = ' ';
sz ht();
string screen(sz = ht(), sz = wd, char = def);
string window = screen(); // call screen(ht(), 80, ' ')
```

Names used as default arguments are resolved in the scope of the function declaration.  
The value that those names represent is evaluated at the time of **call**.


#### 6.5.2 Inline and *constexpr* Functions

The benefits of defining a function for a **small** operation:
* It is easier to read and understand the function than it would be
  to read and understand the equivalent expression.
* Using a function ensures uniform behavior.
  Each test is guaranteed to be done the same way.
* If we need to change the computation, it is easier to change the function
  than to find and change every occurrence of the equivalent expression.
* The function can be reused rather than rewritten for other applications.

There is, however, one potential drawback:  
* Calling a function is apt to be slower than evaluating the equivalent expression.

A function specified as **inline** (usually) is **expanded** "in line" at each call
**in the compilation**.

We can define a function as an inline function by putting the keyword *inline*
before the function's return type.

**NOTE**: the inline specification is only a **request** to the compiler.  
The compiler may choose to ignore this request.

In general, the inline mechanism is meant to optimize small, straight-line functions
that are called frequently.  
Many compilers will not inline a recursive function.  
A 75-line function will almost **surely not** be expanded inline.

A **constexpr function** is a function that can be used in a constant expression.  
It is defined like any other function but must meet certain restrictions:
* The return type and the type of each parameter must be a literal type.
* The function body must contain exactly one return statement.
``` C++
constexpr int new_sz() { return 42; }
constexpr int foo = new_sz(); // ok
```

When the compiler verify (at compile time) that a function is a constexpr function,
it will replace a call to the function with its resulting value.  
In order to be able to expand the function immediately,
constexpr functions are implicitly **inline**.

A constexpr function body may contain other statements **so long as**
those statements generate no actions at **run time**.  
For example, a constexpr function may contain null statements, type aliases, and using declarations.

A constexpr function is permitted to return a value that is **not a constant**.  
If so, the function serves as a normal function **at that call**.
``` C++
// scale(arg) is a constant expression if arg is a constant exrpession
constexpr size_t scale(size_t cnt)
{ return new_sz() * cnt; }

int arr[scale(2)]; // ok: scale(2) is a constant expression
int i = 2; // i is not a constant expression
int a2[scale(i)]; // error: scale(i) is not a constant expression
```


#### 6.5.3 Aids for Debugging

C++ programmers sometimes use a technique similar to header guards
to *conditionally execute* debugging code.  
