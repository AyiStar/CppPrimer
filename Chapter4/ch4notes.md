# Notes in Chapter4

## Chapter4. Expressions

This chapter focuses on the operators as defined in the language
and applied to operands of built-in type.  
We will also look at some of the operators defined by the library.

An **expression** is composed of one or more **operands** and yields a **result**
when it is *evaluated*.  
The simplest form of an expression is a single literal or variable,
and the result is the *value* of the literal or variable.



### 4.1 Fundamentals

There are both **unary** operators and **binary** operators:
* unary operators are ones that take a single operand.
* binary operators are ones that take two operands.

There is also one ternary operator that takes three operands,  
and one operator, function call, that takes an unlimited number of operands.

**precedence** of operators: defines the order in which different operators in a compound expression are grouped.  
Operators with higher precedence are grouped more tightly than operators with lower precedence.

**associativity** of operators: determines how operators with the same precedence are grouped.  
Operators can be either right associative or left associative.

**order of evaluation**: order, if any, in which the operands to an operator are evaluated.  
In most cases, the compiler is free to evaluate operands in any order.  
However, the operands are always evaluated before the operator itself is evaluated.  
Only the &&, ||, ? :, and comma operators specify the order in which their operands are evaluated.

Small integral type operands (e.g. bool, char, short, etc.) are
generally promoted to a larger integral type, typically int.

**overloaded operators** are a version of an operator that is
defined for use with a class type.  
When we use an overloaded operator,
the meaning of the operator -- including the type of its operand(s) and the result -- depend on how the operator is defined.  
However, the number of operands and the precedence and the associativity of the operator **cannot be changed**.

Every expression in C++ is either an **rvalue** or an **lvalue**:
* rvalue is an expression that yields a value but not the associated location, if any, of that value.
* lvalue is an expression that yields an object or function.  

In C++, some lvalue, such as const objects, may not be the left-hand operand of an assignment.  
Moreover, some expressions yield objects but return them as rvalues, not lvalues.  

Roughly speaking, when we use an object as an rvalue, we use its value (contents).  
When we use an object as an lvalue, we use its identity (location in memory).

With one exception, we can use an lvalue when an rvalue is required,  
but we cannot use an rvalue when an lvalue is required.  
When we use an lvalue in place of an rvalue, its contents are used.

* Assignment requires a (nonconst) lvalue as its left-hand operand and yields its left-hand operand as an lvalue.  
* The address-of operator requires an lvalue operand and returns a pointer to its operand as an rvalue.  
* The built-in dereference and subscript operators and the iterator dereference and string and vector subscript operators
all yield lvalues.  
* The built-in and iterator increment and decrement operators require lvalue operands and the prefix versions
also yield lvalues.

When we apply decltype to an expression, the result is
a reference type if the expression yields an lvalue.  
If p is int\*, decltype(\*p) is int&, and decltype(&p) is int**.

For operators that do not specify evaluation order,
it is an error for an expression to *refer to* and *change* the same object.  
Expressions that do so have undefined behavior.

Order of operand evaluation is **independent of** precedence and associativity.  
In an expression such as f() + g() * h() + j():
* Precedence guarantees that the result of g() and h() are multiplied.
* Associativity guarantees that the result of f() is added to the product of g() and h()
  and that the result of that addition is added to the value of j().
* There are **no guarantees** as to the order in which these functions are called.
* If any of these functions affect the same object, then the expression is in error and has undefined behavior.

Order of evaluation for most of the binary operators is left undefined
to give the compiler opportunities for optimization.  
This strategy presents a **trade-off** between efficient code generation
and potential pitfalls in the use of the language by the programmer.

When writing compound expressions:
* When in doubt, **parenthesize** expressions to force the grouping that
the logic of your program requires.
* If you change the value of an operand, **don't** use that operand elsewhere in the **same** expression.
* An exception th the second rule occurs when the subexpression that changes the operand
  is itself the operand of another subexpression. For example, \*++iter.
  
  
  
### 4.2 Arithmetic Operators
  
Arithmetic operators include:  
+(unary plus), -(unary minus)  
*(multiplication), /(division), %(remainder)  
+(addition), -(subtraction)

The unary arithmetic operators have higher precedence than the multiplication and division operators,  
which in turn have higher precedence than the binary addition and subtraction.

Arithmetic operators are all left associative.

The operands and results of these operators are rvalues.

The unary plus operator and the addition and subtraction operators
may also be applied to pointers.

For most operators, operands of type bool are promoted to int.

Division between integers returns an integer.
If the quotient contains a fractional part, it is truncated toward 0.

The *modulus* operator is defined so that:
* If m and n are integers and n is nonzero,
  then (m / n) * n + m % n is equal to m.
* (-m) / n and m / (-n) are always equal to -(m / n).
* m % (-n) is equal to m % n, and (-m) % n is equal to -(m % n).
``` C++
21 % 6; // is 3
21 % 7; // is 0
21 / 7; // is 3
-21 % -8; // is -5
21 / -8; // is 2
21 % -5; // is 1
21 / -5; // is -4
```



### 4.3 Logical and Relational Operators

Logical and relational operators include:  
!  (right associative)  
\<, \<=, \>, \>= (left associative)  
==, != (left associative)  
&& (left associative)  
|| (left associative)

The relational operators take operands of arithmetic or pointer type.  
The logical operators take operands of any type that can be converted to bool.

The operands to these operators are rvalues,
and the result is an rvalue.

When using a range for to a string, if the string may be large,
we can use a reference type to avoid copying.

Because the relational operators return bool type,
it is often an error to chain these operators together.

if(val == true) is often not so good as if(val):
* It is longer and less direct.
* When val is not a bool, true may be promoted to 1,
  the result may be different.
  
So it is often a bad idea to use the boolean literals true and false
as operands in a comparison.  
These literals should be used only to compare an object of type bool.



### 4.4 Assignment Operators

The left-hand operand of an assignment operator must be a **modifiable lvalue**.

Initializations are not assignments.

The result of an assignment is its *left-hand operand*, which is an lvalue.  
The type of the result is the type of the left-hand operand.  
If the type of left and right operands differ, the right-hand operand is **converted** to the type of the left.

In C++11, we can use a *braced initializer list* on the right-hand side.
``` C++
int k = 0;
k = {3.14}; // error: narrowing conversion
vector<int> vi; // initially empty
vi = {0,1,2,3,4,5,6,7,8,9}; // vi now has ten elements
```
If the left-hand operand is of a built-in type,
the initializer list may contain at most one value,
and that value must not require a narrowing conversion.  
For class types, what happens depends on the details of the class.

Regardless of the type of the left-hand operand, the initializer list may be empty.  
In this case, the compiler generates a value-initialized temporary
and assigns that value to the left-hand operand

Assignment is right associative, so we may chain them together,
but remember that each object in a multiple assignment must have the same type as its right-hand neighbor
or a type to which that neighbor can be converted.

Assignment has relatively low precedence.  
When we use them as conditions, we usually must parenthesize them for the condition to work properly.

The only difference between the compound assignment and the ordinary operator is,
the left-hand operand is evaluated only once if we use the compound assignment, and twice if we use the ordinary one.  
In most contexts this difference is immaterial aside from possible performance consequences.



### 4.5 Increment and Decrement Operators

++ and -- operators provide a **convenient** notational shorthand for adding or subtracting 1 from an object.  
This notation rises above **mere** convenience when we use these operators with iterators, because many iterators do not support arithmetic.

The prefix form increments/decrements its operand and yields the *changed* object as its result.  
The postfix form increments/decrements its operand but yields *a copy of the original, unchanged* value as its result.

These operators require lvalues.  
The prefix operators return the object itself as an lvalue.  
The postfix operators return a copy of the object's original value as an **rvalue**.

Use postfix operators **only when necessary**.  
The prefix version avoids unnecessary work.
It increments the value and returns the incremented version.  
The postfix operator must store the original value so that it can return the unincremented value as its result.  
For ints and pointers, the compiler can optimize away this extra work.
For more complicated iterator types, this extra work potentially might be more costly.

\*iter++ is a common and useful idiom.  
It is worthwhile to study such code until their meanings are immediately clear.



### 4.6 The Member Access Operators

The dot and arrow operators provide for member access.  
The dot operator fetches a member from an object of class type.  
The arrow is defined so that ptr-\>mem is a synonym for (\*ptr).mem.

Because dereference has a lower precedence than dot, we must parenthesize the dereference subexpression.

The arrow operator requires a pointer operand and yields an lvalue.  
The dot operator yields an lvalue if the object from which the member is fetched is an lvalue; otherwise the result is an rvalue.



### 4.7 The Conditional Operator

The conditional operator (? : ) lets us embed simple if-else logic inside an expression.  

cond ? expr1: expr2;  
cond is an expression that is used as a condition,
and expr1 and expr2 are expressions **of the same type** or types that **can be converted** to a common type.  
If cond is true, expr1 is evaluated; otherwise expr2 is evaluated.

The result of the conditional operator is an lvalue if both expressions are lvalues or if they convert to a common lvalue type;
otherwise the result is an rvalue.

We can nest one conditional operator inside another.

The conditional operator is right associative, meaning (as usual)
that the operands group right to left.  
``` C++
string finalgrade = (grade > 90) ? "high pass" : (grade > 60) ? "pass" : "fail";
// the right associativity accounts for the fact that the right-hand conditianal forms the : branch of the left-hand conditional expression.
```

Nested conditionals quickly become unreadable.
It is a good idea to nest no more than two or three.

The conditional operator has fairly **low** precedence, so we usually
must parenthesize them in a large expression.

We often use the conditional operator in an output expression
to print one or another value, depending on the result of a condition.



### 4.8 The Bitwise Operators

The bitwise operators include: (all left associative)  
~  
\<\<, \>\>  
&  
^  
|  

The bitwise operators take operands of **integral** type that they use
as a collection of bits.  
They let us test and set individual bits.

We can also use these operators on a library type named **bitset**
that represents a flexibly sized collection of bits.

The operand(s) can be either signed or unsigned.

If the operand is signed and its value is negative,
then the way that the "sign bit" is handled in a number of the bitwise operations
is **machine dependent**.  
Doing a left shift that changes the value of the sign bit is undefined.

It is strongly recommended that using unsigned type with the bitwise operations.

Bitwise shifted operators (\<\<, \>\>) yield a **copy** of the (possibly promoted)
left-hand operand with the bits shifted as directed by the right-hand operand.  
Right-hand operand must **not be negative** and must be a value that is strictly **less than** the number of bits in the result.
Otherwise, the operation is undefined.  
Bits that are shifted off the end are discarded.

The left-shifted operator inserts 0-valued bits on the right.

The behavior of the right-hand operator depends on the type of the left-hand operand.  
If it is unsigned, then the operator insets 0-valued bits on the left.  
If it is a signed type, the result is implementation defined -- either copies of the sign bit or 0-valued bits are inserted on the left.  

The bitwise NOT operator generates a new value with the bits of its operand inverted.  
Each 1 bit is set to 0; each 0 bit is set to 1.

The bitwise AND, OR, XOR operators generate new values with the bit pattern
composed from its two operands.

The shift operators have mid-level precedence:
lower than the arithmetic operators but
higher than the relational, assignment, and conditional operators.



### 4.9 The sizeof Operator

The sizeof operator returns the size, **in bytes**, of an expression or a type name.  
The operator is right associative.  
The result of sizeof is a **constant expression** of type size_t.

The operator takes one of two forms:
* sizeof (type)
* sizeof expr: return the size of the type returned by the given expression.
  But the sizeof operator does not evaluate its operand.
``` C++
int i = 0;
int *p; 
sizeof(p); // size of a pointer to int
sizeof(*p); // size of a int; it does not dereference p, so it doesn't matter p is invalid
```

in C++11, we can use the scope operator to ask for the size of a member of a class type.  

The result of applying sizeof depends in part on the type involved:
* sizeof char or an expression of type char is guaranteed to be 1.
* sizeof a reference type returns the size of an object of the referenced type.
* sizeof a pointer returns the size needed to hold a pointer.
* sizeof a dereferenced pointer returns the size of an object of the type to which the pointer points;
  the pointer need not be valid.
* sizeof an array is the size of the **entire array**.
  It is equivalent to taking the sizeof the element type times the number of elements in the array.
  Note that sizeof does not convert the array to a pointer.
* sizeof a string or a vector returns only the size of the fixed part of these types;
  it does not return the size used by the object's elements.  
  Through my test code, all the string/vector variable has the same fixed size returned by sizeof operator,
  regardless of how many elements they hold.
  
Because sizeof returns a constant expression, we can use the result to specify the dimension of an array.



### 4.10 Comma Operator

The comma operator takes two operands, which it evaluates from left to right.  
It guarantees the order in which its operands are valued.

The left-hand expression is evaluated and its *result is discarded*.

The result of a comma expression is the value of its right-hand expression.  
The result is an lvalue if the right-hand operand is an lvalue.

One common use for the comma operator is in a for loop:
``` C++
for(i = 0, j = n; i < j; ++i, --j)
{
    ...
}
```



### 4.11 Type Conversions

In C++ some types are **related** to each other.  
When two types are related, we can use an object or value of one type where an operand of the related type is expected.  
Two types are related if there is a conversion between them.

Implicit conversion is a conversion that is automatically generated by the compiler.
Given an expression that needs a particular type but has an operand of a differing type,
the compiler will automatically convert the operand to the desired type if an appropriate conversion exists.

The implicit conversions among the arithmetic types are defined to **preserve precision**, if possible.  
Most often, if an expression has both integral and floating-point,
the integer is converted to floating-point.

The compiler automatically converts operands in the following circumstances:
* In most expressions, values of integral types smaller than int are **promoted** to an appropriate larger integral type.
* In conditions, nonbool expressions are converted to bool.
* In initializations, the initializer is converted to the type of the variable;
  in assignment, the right-hand operand is converted to the type of the left-hand.
* In arithmetic and relational expressions with operand of mixed types,
  the types are converted to a common type.
* Conversions also happen during function calls.

The integral promotions convert the small integral types to a larger integral type:
* The type bool, char, signed char, unsigned char, short, and unsigned short
  are promoted to int if all possible values of that type fit in an int.
  Otherwise, the value is promoted to unsigned int.
* The larger char types (wchar_t, char16_t, and char32_t) are promoted to
 the smallest type of int, unsigned int, long, unsigned long, long long or unsigned long long
 in which all possible values of that character type fit.
 
If any operand is an unsigned type,
the type to which the operands are converted depends on the relative sizes of the integral types on the machine.  
* As usual, integral promotions happen first. If the resulting type(s) match, no further conversion is needed.  
* If both operands have the same signedness, then the operand with the smaller type is converted to the larger type.  
* When the signedness differs and the type of the unsigned operand is the same as or larger than that of the signed operand,
  the signed operand is converted to unsigned.
* When the signed operand has a larger type than the unsigned operand,
  the result is machine dependent:
    * If all values in the unsigned operand fit in the signed type,
      then the unsigned operand is converted to the signed type.
    * If the values don't fit, then the signed operand is converted to the unsigned type.
    
Examples:
``` C++
bool flag;
char cva;
short sval;
unsigned short usval;
int ival;
unsigned int uival;
long lval;
unsigned long ulval;
float fval;
double dval;

a.14159L + 'a'; // 'a' promoted to int, then that int converted to long double
dval + ival; // ival converted to double
dval + fval; // fval converted to double
ival = dval; // dval converted (by truncation) to int
flag = dval; // if dval is 0, then flag is false; otherwise true
cval + fcal; // cval promoted to int, then that int converted to float
sval + cval; // sval and cval promoted to int
cval + lval; // cval converted to long
ival + ulval; // ival converted to unsigned long
usval + ival; // promotion depends on the size of unsigned short and int
uival + lval; // conversion depends on the size of unsigned int and long
```

There are several additional kinds of implicit conversions:
* Arrays to pointers conversions: In most expressions, when we use an array,
  the array is automatically converted to a pointer to the first element in that array.  
  This conversion is not performed when:
  * with decltype, address-of, sizeof, and typeid operators.
  * when initialize a reference to an array.
* Pointer conversions: A constant value of 0 and the literal nullptr can be converted to any pointer type.
  a pointer to any nonconst type can be converted to void\*.
* Conversions to bool: If the pointer or arithmetic value is zero, the conversion yields false, any other value yields true.
* Conversions to const: We can convert a pointer to a nonconst type to a pointer to the corresponding const type,
  and similarly for references.  
  The reverse conversion -- removing a low-level const -- does not exist.
* Conversions defined by class type: Class types can define conversions that the compiler will apply automatically.
  The compiler will apply only one class-type conversion at a time.  
  For example, istream to bool, C-style character string to library string.
  
We use a **cast** to request an explicit conversion.

Although necessary at times, casts are inherently **dangerous** constructs.

A **named cast** has the following form:  
*cast-name\<type\>(expression)*  
where *type* is the target type of the conversion, and
*expression* is the value to be cast.  
If *type* is a reference, then the result is the an lvalue.  
The *cast-name* may be one of **static_cast**, **dynamic_cast**, **const_cast**, and **reinterpret_cast**.  
The cast-name determines what kind of conversion is performed.
* static_cast: an explicit request for a well-defined type conversion.
  Often used to override an implicit conversion that the compiler would otherwise perform.
* dynamic_cast: used in combination with inheritance and run-time type identification.
* const_cast: a cast that converts a low-level const object to the corresponding nonconst type or vice versa.
* reinterpret_cast: interpret the contents of the operand as a different type.

Any well-defined type conversion, **other than** those involving low-level const,
can be requested using a static_cast.

A static_cast is often useful when a larger arithmetic type is assigned to a smaller type.  
The cast *informs* both the reader of the program and the compiler that
we are aware of and are not concerned about the potential loss of precision.

A static_cast is also useful to perform a conversion that the compiler will not generate automatically.

A const_cast changes only a **low-level** const in its operand.
``` C++
const char *pc;
char *p = const_cast<char*>(pc); // ok: but writing through p is undefined
```
Once we have cast away the const of an object,
the compiler will no longer prevent us from writing to that object.  
If the object was originally not a const, using a cast to obtain write access is legal.  
However, using a const_cast in order to write to a const object is undefined.

const_cast can only change the **constness** of an expression, but not the type.   
And the constness can be changed only by const_cast, but not by the other forms of named cast.
``` C++
const char *cp;
char *q = static_cast<char*>(cp); // error
static_cast<string>(cp); // ok
const_cast<string>(cp); // error
```

A reinterpret_cast generally performs a **low-level reinterpretation** of the bit pattern of its operand.
``` C++
int *ip;
char *pc = reinterpret_cast<char*> ip;
```

A reinterpret_cast is inherently machine dependent.  
Safely using reinterpret_cast requires completely understanding the types involved
as well as the details of how the compiler implements the cast.

In early versions of C++, an explicit cast took one of the following two forms:
* *type (expr)*: function-style cast notation
* *(type) expr*: C-language-style cast notation

Casts **interfere** with normal type checking.  
It is strongly recommended that programmers avoid casts.  
This advice is particularly applicable to reinterpret_casts.  
A const_cast is **useful** in the context of overloaded functions.
Other uses of const_cast often indicate a design flaw.

Every time we write a cast, we should think hard about
whether we can achieve the same result in a different way.  
If the cast is unavoidable, errors can be mitigated by limiting the scope in which the cast value is used
and by documenting all assumptions about the types involved.

Depending on the types involved, an old-style cast has the same behavior
as a const_cast, a static_cast, or a reinterpreted_cast.  
When we use an old-style cast where a static_cast or a const_cast would be legal,
the old-style cast does the same conversion as the respective named cast.  
If neither cast is legal, then an old-style cast performs a reinterpreted_cast.



### 4.12 Operator Precedence Table

* L  ::(global/class/namespace scope)  
* L .(member selector), -\>(member selectors), \[\](subscript), ()(function call), ()(type construction)  
* R ++(post increment), --(post decrement), typeid(type ID), typeid(run-time type ID), explicit casts  
* R ++(prefix increment), --(prefix decrement), ~(bitwise NOT), !(logical NOT), +(unary plus), -(unary minus),
  \*(dereference), &(address-of), ()(type conversion), sizeof(size of object/type/parameter pack),
  new(allocate object), new\[\](allocate array), delete(deallocate object), delete\[\](deallocate array),
  noexcept(can expr throw)
* L -\>\*(ptr to member select), .\*(ptr to member select)  
* L \*(multiply), /(divide), %(modulo)  
* L +(add), -(subtract)  
* L \<\<(bitwise left shift), \>\>(bitwise right shift)  
* L \<(less than), \<=(less then or equal), \>(greater than), \>=(greater than or equal)  
* L ==(equality), !=(inequality)
* L &(bitwise AND)
* L ^(bitwise XOR)
* L |(bitwise OR)
* L &&(logical AND)
* L ||(logical OR)
* R ? :(conditional)
* R =(assignment), \*=, /=, %=, +=, -=, \<\<=, \>\>=, &=, |=, ^=(compound assign)
* R throw(throw exception)
* L ,(comma)



### Chapter Summary

