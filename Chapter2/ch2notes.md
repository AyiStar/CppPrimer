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



