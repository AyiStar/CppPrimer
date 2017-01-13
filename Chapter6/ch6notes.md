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

