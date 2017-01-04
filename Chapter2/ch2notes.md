# Notes in Chapter 2


## Chapter 2 Variables and Basic Types

The language defines several primitive types
and provides mechanisms that let us define our own data types.


### 2.1 Primitive Built-in Types

*Primitive types* include *arithmetic types* and a special type named *void*.  
*Arithmetic types* represent characters, integers, boolean values and floating-point numbers.  
*void type* has no associated values and can be used in only a few circumstances, most commonly as the return type for functions that do not return a value.

**Arithmetic types**:
* **integer types**: include character and boolean types.
* **floating-point types**.

The *size of* a type is the *number of bits in* a type.  
They vary across machines.  
The standard guarantees minimum sizes:
* bool: NA.
* char: 8 bits.
* wchar_t (wide character): 16 bits.
* char16_t (Unicode character): 16bits.
* char32_t (Unicode character): 32 bits.
* short: 16 bits.
* int: 16 bits.
* long: 32 bits.
* long long: 64 bits.
* float: 6 significant digits.
* double: 10 significant digits.
* long double: 10 significant digits.

A *char* is the same size as a single *machine byte*.

An *int* will be as least as large as *short*.  
A *long long* will be at least as large as *long*. 

The smallest chunk of addressable memory is referred to as a *byte*.  
The basic unit of storage, usually a small number of bytes, is referred to as a *word*.  
A *byte* has at least as many bits as are needed to hold a character in the machine's basic character set.  
On most machines a byte contains 8 bits and a word is 4 or 8 bytes.

The *type* determines:
* How many bits are used.
* How to interpret those bits.

*Typically*:
* floats are represented in 1 word.
* doubles are represented in 2 words.
* long doubles are represented in 3 or 4 words.
* float yields about 7 significant digits.
* double yields about 16 significant digits.
* long double's precision varies with implementation.

A few rules of thumb useful in deciding *which type to use*:
* Use an unsigned type when you know that the value cannot be negative.
* Use int for integer arithmetic.  
  If the values are larger than the minimum guaranteed, use long long.
* Do not use plain char or bool in arithmetic expressions.  
  Use them only to hold characters or truth values.  
  char is signed on some machines and unsigned on others.
* Use double for floating-point computations.  
  float does not have enough precisions, and the cost of double is negligible.  
  On some machines, double operations are faster than single.  
  long double is usually unnecessary and often entails considerable run-time cost.

When we *assign one arithmetic type to another*:
* boolean <- nonbool : false if the value is 0 and true otherwise.
* nonbool <- bool: 1 if the bool is true and 0 if the bool is false.
* integer type <- floating-point type: the value is truncated (the part before the decimal point).
* floating-point type <- integer type: the fraction is zero  
  and precision may be lost if the integer has more bits than the floating-point object can accommodate. 
* unsigned type <- out-of-range value: the result is  
  the remainder of the value modulo the number of the values the target type can hold.
* signed type <- out-of-range value: the result is *undefined*.

*Unsigned types* in expressions:
* If we use both unsigned and signed values in an expression, the signed value ordinarily is converted to unsigned.
* If we subtract a value from an unsigned, we must be sure that rhe result cannot be negative..
* When we write a loop, it's worth noting that unsigned values cannot be less than zero.

A **literal** is a value such as a number, a character, or a string characters. The value cannot be changed.  
Every literal has a type, determined by its form and value: 
* Integer: 
    * By default, decimal literals are signed; octal and hexadecimal literals can be either signed or unsigned.
    * A decimal literal has the smallest of int, long or long long in which the literal's value fits.
    * Octal and hexadecimal literals has the smallest type of int, unsigned int, long, unsigned long, long long, or unsigned long long in which its value fits.
* Floating-point literals:
    * Include either a decimal point or an exponent (e/E).
    * By default, has type double.
* Character and character string literals:
    * A character enclosed within single quotes ('') is a literal of type char.
    * Zero or more characters enclosed in double quotation marks is a string literal.
    * Two string literals that appear adjacent to one another and that are separated only by spaces, tabs, or newlines
      are concatenated into a single literal.
* Boolean and Pointer literals:
    * The word true and false are literals of type bool.
    * the word nullptr is a pointer literal.
* It's an error to use a literal that is too large to fit in the largest related type.
* We can specify the type of a literal explicitly, overriding the default:
    * prefix u: char16_t
    * prefix U: char32_t
    * prefix L: wchar_t
    * prefix u8: char
    * suffix u or U (integer): unsigned (minimum)
    * suffix l or L (integer): long (minimum)
    * suffix ll or LL (integer): long long (minimum)
    * suffix f or F (floating): float
    * suffix l or L (floating): long double
* The minus sign ('-') is not a part of the literal, but an operator that negates the value of its operand.

When write a *long* literal, use the uppercase L suffix in case of being mistaken for the digit 1.

An **escape sequence** is an alternative mechanism for representing characters,
particularly for those without printable representations.  
An escape sequence is a backslash (/) followed by a character, three or fewer octal digits, or an x followed by a hexadecimal number.  
* newline: \n
* horizontal tab: \t
* vertical tab: \v
* alert(bell): \a
* backspace: \b
* double quote: \"
* backslash: \\
* question mark: \?
* single quot" \'
* carriage return: \r
* formfeed: \f


### 2.2 Variables

A **variable** is a *named object or reference*,
providing us with a *named storage* that our program can manipulate.  
Each variable has a type, which determines:
* the size and layout of the variable's memory.
* the range of values that can be stored within that memory.
* the set of operations that can be applied to the variable.

A simple **variable definition** consists of:
* a *type specifier* (the name of a type).
* (followed by) a list of one or more *variable names* separated by commas.
* (ends with) a semicolon.
* May provide an initial value for one or more of the names it defines.

What is an **object**:
* More generally, an object is a region of memory that can contain data and has a type.
* Sometimes only refers to variables or values of class types.
* Sometimes refers to *unnamed* objects, while *variable* refers to *named* objects.
* Sometimes refers to data that can be changed by the program, while *value* refers to data that are read-only.

When a definition defines two or more variables,
the name of each object becomes *visible* **immediately**.  
Thus, it is possible to initialize a variable to the value of one defined earlier in the *same* definition.

**Initialization** in C++ is a surprisingly *complicated* topic.  
Initialization and assignment are different operations in C++.  
Initialization happens when a variable is given a value when it is created.
Assignment obliterates an object's current value and replaces that value with a new one.

Here are some examples of initializations:
```C++
int a = 0;
int a = {0};
int a{0};
int a(0);
```

**List initialization**: form of initialization that uses curly braces
to enclose one or more initializers.  
Compiler will not let uslist initialize *built-in type* variables
if the initializer might lead to the loss of information.

**Default initialization**: how objects are initialized when no explicit initializer is given.
* How class type objects are initialized is controlled by the class.
* Built-in type objects defined at global scope are initialized to 0.
* Those defined at local scope are uninitialized and have undefined values.

It is an error to *copy* or try to *access* the value of a variable whose value is *undefined*.

Initialize **every** object of built-in type.

A **declaration** asserts the existence of a variable, function, or type defined elsewhere.
It makes a name known to the program.
A file that wants to use a name defined elsewhere includes a declaration for that name.  
A **definition** creates the associated entity.  
A variable definition is a declaration.  
In addition to specifying the name and type (what a declaration does),
a definition also allocates *storage* and may provide an *initial value*.  

To obtain a declaration that is not also a definition, we add *extern* keyword and may not provide an explicit initializer.  
Any declaration that includes an explicit initializer is a definition, which overrides the extern.

Variables must be defined *once* but can be declared *many times*.

C++ is a **statically typed** language: *type checking* occurs at *compile time*.  
A static type checking can help find bugs, but requires the type of every entity used known to the compiler,
i.e. declared before used.

**Identifier**:
* make up a name.
* can be composed of letter, digits and the underscore character.
* has no limit on length.
* is case-sensitive.
* A set of names are reserved.

The identifiers we define in our own programs **may not**:
* contain two consecutive underscores.
* begin with an underscore followed immediately by an uppercase letter.
* begin with an underscore if defined outside a function.

Conventions for variable names:
* An identifier should give some indication of its meaning.
* Variable names normally are lowercase.
* Class we define usually begin with an uppercase letter.
* Identifiers with multiple words should visually distinguish each word.

**Scope** is the portion of a program in which names have meaning:
* global scope: names defined outside any other scope.  
  Once declared, names at the global scope are accessible throughout the program.
* class scope: names defined inside a class namespace.
* block scope: names defined inside a block.

Names are *visible* from the point where they are declared
until the end of the scope in which the declaration appears.

Define variables **where you first use them**:
* Improve readability.
* Easier to give initial value.

Scopes can **nest**:
* The nested scope is referred to as an inner scope.
* The containing scope is referred to as an outer scope.
* Once a name has been declared in a scope, that name can be used by nested scoped.
* Names declared in the outer scope can also be redefined in an inner scope.
* However, it's always a bad idea to define a local variable with the same name as a global variable that the function uses or might use.


### 2.3 Compound Types

A **compound type** is a type that is defined in terms of another type.

A *declaration* is a *basic type* followed by a list of *declarators*.  
Each declarator names a variable and gives the variable a type that is related to the base type.

A **reference** defines an alternative name for an object:
* We define a reference type by writing a declarator of the form *&d*.
* When we define a reference, we *bind* the reference to its initializer.  
* Once initialized, a reference *remains bound to* refer to its initial object.
  There is **no way** to rebind a reference to refer to a different object.
  So references **must** be initialized.
  
A reference is **not** an object but just another name for an already existing object.  
After a reference has been defined, **all operations** on that reference are actually operations on the object to which the reference is bound.

Because references are not objects, we may **not** define a reference to a reference.
But it's not an error.
Instead, it is bound to the object the reference is bound.

A reference can't be bound to a literal or the result of a more general expression. It's an error.

A **pointer** is an **object** that can hold the address of an object,
the address one past the end of an object, or zero.

Pointers defined at block scope have undefined value if they are not initialized.

References do not have addresses, so we may not define a pointer to a reference.

The value (i.e. the address) stored in a pointer can be in one of four states:
* It can point to an object.
* It can point to the location just immediately past the end of an object.
* It can be a null pointer, indicating that it is not bound to any object.
* It can be invalid: value other than the preceding three are invalid.

The result of accessing an invalid pointer is undefined.  
Although pointers in case 2 and 3 above are valid, they do not point to any object,
so if we try to access an object through such pointers, the behavior is also undefined.

In declarations, & and * are used to form compound types.  
In expressions, these same symbols are used to denote an operator.  
It can be helpful to *ignore appearances* and think of them as if they were *different symbols*.

Ways to obtain a null pointer:
```C++
int *p1 = nullptr;
int *p2 = 0;
int *p3 = NULL; // must include cstdlib
```
The most direct approach is using the literal nullptr.  
nullptr is a literal that has a *spacial type* that can be converted to any other pointer type.

Modern C++ program should *avoid using NULL* and *use nullptr* instead.

It is illegal to assign an int variable to a pointer **even if the variable's value is 0**.

Initialize **all pointers**.  
If possible, define a pointer *only after the object to which it should point has been defined*.
If there is no object to bind to a pointer, then initialize the pointer to nullptr.

When we use a pointer in a condition, the condition is false only if the pointer is 0,
and any nonzero pointer evaluates as true.

Given two *valid pointers of the same type*, we can *compare* them:  
Two pointers are equal if they hold the same address and unequal otherwise.

**void*** is a special pointer type that can hold the address of **any object**.  
There are only limited things we can do with them:
* Compare it to another pointer.
* Pass it to or return it from a function.
* Assign it to another void* pointer.
* **CANNOT** use it to operate on the object it address because the type is unknown.
* Generally, use it to *deal with memory as memory*, rather than using the pointer to access the object stored in that memory.

The type modifier, which is a part of a declarator,
**does not** apply to all the variables defined in a single statement.

There are two common styles used to define multiple variables with pointer or reference type:
* Place the type modifier adjacent to the identifier.  
  This style emphasizes that the variable has the indicated compound type.
* Place the type modifier with the type but defines only one variable per statement.  
  This style emphasizes that the declaration defines a compound type.
  
It can be easier to understand complicated pointer or reference declarations
if you read them form right to left.
```C++
int *p = nullptr; // is a pointer to int
int *&r = p; // is a reference to a pointer to int
int **pp = &p; // is a pointer to a pointer to int
```


### 2.4 const Qualifier

**const** is a *type qualifier* used to define objects that may not be changed.  
Const objects must be initialized, because we can't change it after we define it.

A const type can use *most but not all* of the same operations as its nonconst version:
* We may use only those cannot change an object.
* When we use an object to initialize another object, it does not matter whether either or both are consts.

By default, const objects are **local to file**,
because compile has to substitute the value for the variable during compilation.
  
Sometimes we have a const variable that we want to share across files but whose initializer is not a const expression,
i.e. we don't want the compiler to generate a separate variable in each file.  
We want to define the const in one file and declare it in other files.  
We use keyword *extern* on both its definition and declarations.

A **reference to const** is a reference that refers to a const type.  
A reference to const cannot be used to change the object to which the reference is bound.
```C++
const int ci = 42;
const int &r1 = ci; // ok
r1 = 0; // error
int &r2 = ci; // error
```

const reference is just an abbreviation to a reference to const.  
In fact, a reference is not an object so it cannot be const.  
Or in a sense, all references are "const".

There are two exceptions to the rule that the type of a reference must match the type of the object to which it refers,  
here is the first one:
* We can initialize a reference to const from any expression that can be converted to the type of the reference.  
  In particular, we can bind a reference to const to a nonconst object, or a more general expression.
* A reference can be bound to a temporary object, which is an unnamed object created by the compile
  when it needs a place to store a result from evaluating an expression.
* If a reference which is bound to a temporary is not const,
  the temporary can be changed through the reference, but it makes no sense,
  because why not use a variable instead?
  So C++ *makes it illegal*.
* A reference to const restrict only what we do *through that reference*,
  so a reference to const may refer to an object that is not const itself.  
  In that case, we can change the value through the object itself but
  cannot through the reference.
  
A **pointer to const** is a pinter that holds the address of a const object,
and may not be used to change the value of the object to which it points.
```C++
const double pi = 3.14;
double *p = &pi; // error
const double *cp = &pi; // ok
*cp = 4.0; // error
```

Like a reference to const, a pointer to const **says nothing about
whether the object to which it points is const**.  
Define a pinter to const **affects only what we can do with the pointer**.  
There is **no guarantee** that an object pointed to by a pinter to const won't change.

It is helpful to think of pointers and references to const as
pointers or references that **think** they point to refer to const.

A **const pointer** is indicated by putting the const *after* the *.  
This placement indicates that it is the **pointer**, not the **point-to** type, that is const.
```C++
int i = 0;
int *const p = &i; // p is a const pointer
```

The fact that a pointer is itself const says **noting about
whether we can use the pointer to change the underlying object**.  
Instead, it depends entirely on the type to which the pointer points.

We use the term **top-level const** to indicate that the pointer itself is a const.  
When a pointer can point to a const object, we refer to that const as a **low-level** const.  
Top-level const can appear in *any* object type.  
Low-level const appears in the base type of compound types such as pointers and references.

Note:
```C++
const int i = 42, &ri = i;
// it's ok, and equal to
const int i = 42;
const int &ri = i;
```

The distinction between top-level and low-level matters when copying objects.  
Top-level consts are ignored, while low-level consts is never ignored.  
Copying an object does not change the copied object,
so it is immaterial whether the object copied from or copied into is const.  
But both objects must have the same low-level const qualification
or there must be a convention between the types of the two objects.

A **constant expression** is an expression whose value cannot change
and that can be evaluated at compile time.  
Whether a given object or expression is a constant expression depends on
the types and the initializers.
```C++
const int max_files = 20; // max_files is a constant expression
const int limit = max_files + 1; // limit is a constant expression
int staff_size = 27; // staff_size is not a constant expression because it is a plain int
const int sz = get_size(); // sz is not a constant expression because the initializer is not known until run time
```

In C++11, we can ask the compiler to verify that a variable is a constant expression
by declaring the variable in a **constexpr** declaration.  
Variables declared as a constexpr are implicitly const and must be initialized by constant expressions.
```C++
constexpr int mf = 20; // ok
constexpr int limit = mf + 1; // ok
constexpr int sz = size();  // ok only if size is a constexpr function
```
C++11 lets us define certain functions as constexpr.  
Such functions must be simple enough that the compiler can evaluate them at compile time.

It is a good idea to use constexpr for variables that you intend to use as constant expressions.

The types we can use in a constexpr declaration are known as "**literal types**"
because they are simple enough to have literal values.
* The arithmetic, reference and pointer types are literal types.
* Class types and the library IO and string types are not literal types.

We can initialize a constexpr pointer with nullptr literal, literal 0 or the address of an object that remains at a fixed address:
* The variables defined inside a function ordinarily are not stored at a fixed address.  
* The address of an object defined outside of any function is a constant expression.  
* The functions may also define variables that exist across calls to that function, which have fixed addresses.

When we define a pointer in a constexpr declaration, the constexpr specifier
applies to the **pointer**, not the type to which the pointer points.  
So constexpr imposes a top-level const on the objects it defines.

### 2.5 Dealing with Types

Complications in using types:
* Some types have forms that are tedious and error-prone,
  or can obscure its purpose or meaning.
* Sometimes it's hard to determine the exact type we need.

A **type alias** is a name that is a synonym for another type,
and can appear wherever a type name can appear:
* Declarations including *typedef* keyword define type alias.  
* C++11 introduces alias declaration, which starts with the keyword
  *using* followed by the alias name and an =.  
  The alias declaration defines the name on the left-hand side of the =
  as an alias for the type that appears on the right-hand.
```C++
typedef double wages;
using wages = double;
```

It can be tempting , albeit incorrect, to interpret a declaration that uses a type alias
by conceptually replacing the alias with its corresponding type:
```C++
typedef char *pstring; // pstring is a pointer to char
const pstring cstr = 0; // cstr is a constant pointer to char, rather than a pointer to const char
const pstring *ps; // ps is a pointer to a constant pointer to char
```
The **base type** in the declarations above is const pstring.
A const that appears in the base type modifies the given type.
```C++
const pstring cstr; // the base type is pstring
const char *cstr; // the base type is char and the * is  part of the declarator
```

Under C++11, we can let the **compiler** figure out the type
by using **auto** type specifier.  
auto tells the compiler to deduce the type from the *initializer*.  
A variable that uses auto must have an initializer.

We can define multiple variables whose initializers' types are consistent with each other (the same *base type*)
in a single declaration using auto.
```C++
auto i = 1, *p = &i; // ok
auto sz = 0, pi = 3.14; // error
```

The type that the compiler infers for auto is *not always*
the same as the initializer's type:
* When using a reference as an initializer, the compiler uses that corresponding object's type
  for auto's deduction.
* auto originally ignores top-level const but keeps low-level const.
* If we want the deduced type to have a top-level const, we must say explicitly.
* We can also specify that we want a reference to the auto-deduced type.
  When we ask for a reference to an auto-deduced type, top-level consts are not ignored.
```C++
int i = 0, &r = i;
auto a = r; // a is an int

const int ci = i, &cr = ci;
auto b = ci; // b is an int
auto c = cr; // c is an int
auto d = &i; // d is an int*
auto e = &ci; //e is const int*

const auto f = ci; // deduced type of ci is int; f has type const int

auto &g = ci // g is a const int& that is bound to ci
auto &g = 42; // error: we can't bind a plain reference to a literal
const auto &j = 42; // ok
```

**decltype** is a type specifier that returns the type of its operand.  
The compiler analyzes the expression to determine its type but does not evaluate the expression.
```C++
decltype(f()) sum = x; // sum has whatever type of f returns
// the compiler does not call f but uses the type f returns
```

When the expression to which we apply decltype is a variable,
decltype returns the type of that variable, including top-level const and reference.
When the variable is a reference, the returned type is bound to the object the variable is bound to.
When the expression is not a variable, we get the type that expression yields.

decltype is the *only context* in which a variable defined as a reference
is **not** treated as a synonym for the object to which it refers.

Generally, decltype returns a reference type for expressions that
yield objects that can stand on the left-hand side of the assignment.
```C++
int i = 42, *p = &i, &r = i;
decltype(r) a ; // a is a reference to i 
decltype(r + 0) b; // b is an int
decltype(*p) c; // error: c is int& and must be initialized
```

The dereference operator is an example of an expression for which
decltype returns a reference.

When we apply decltype to a variable without any parentheses, we get the type of that variable.  
If we wrap the variable's name in one or more sets of parentheses, the compiler will evaluate the operand as an expression.  
A variable is an expression that can be the left-hand side of an assignment,
so decltype on such an expression yields a reference.
```C++
int i = 42;
decltype((i)) d; // error: d is int& and must be initialized
decltype(i) e; // ok: e is an int
```
decltype((*variable*)) is always a reference type,  
but decltype(*variable*) is a reference only if *variable* is a reference.

The type of an assignment expression is a **reference** to
the type of the **left-hand** operand.  
If *i* is an int, then i = 42 is int&.



### 2.6 Defining Our Own Data Structures

Ordinarily, it's a **bad idea** to define an object as part of a class definition.

The *data members* define the contents of a class type.
Every object has its own copy of the class data members.

Under C++11, we can supply an **in-class initializer** for a data member.
When we create objects, the in-class initializers will be used to initialize the data members.
Members without an initializer are default initialized.  
In-class initializers must either be enclosed inside curly braces or follow an = sign,
and may not be inside parentheses.

The *string* type holds a sequence of characters.  
Its operations include the >>, <<, and == operators to read, write and compare strings, respectively.

Class can be defined inside a function, but such classes have limited functionality.  
Typically, classes are stored in headers whose name derives from the name of the class.  

Headers (usually) contain entities that can be defined only once in any given file,
such as class definitions and const and constexpr variables.  
Headers often need to use facilities from other headers, so a header might be included more than once.
Thus, we need to write headers in a way that is safe even if the header is included multiple times.

**header guard**: preprocessor variable used to prevent a header from being included more than once in a single file.  
Preprocessor variables have one of two possible states: defined or not defined.  
\#define takes a name and defines it as a preprocessor variable.  
\#ifdef is true if the variable has been defined.  
\#ifndef is true if the variable has not been defined.  
\#endif matches #ifdef or #ifndef.

We can guard against multiple inclusion as follows:
```C++
#ifndef XXX_H
#define XXX_H
... ...
#endif
```
* Preprocessor variables names **do not** respect C++ scoping rules.  
* Preprocessor variables must be unique **throughout the program**.  
* Typically we ensure that by basing the guard's name on the name of a class in the header.  
* Preprocessor variables usually are written in all uppercase.

Headers should **always have guards**.



### Chapter Summary

