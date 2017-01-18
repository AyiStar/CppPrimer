# Notes in Chapter 7




## Chapter7. Classes

The fundamental ideas behind classes are **data abstraction** and **encapsulation**.
* Data abstraction is a programming (and design) technique tht relies on
  the separation of **interface** and **implementation**.
    * The interface of a class consists of the **operations** that users of the class can execute.
    * The implementation includes the class' data members, the bodies of the functions that constitute the interface,
      and any functions needed to define the class that are not intended for general use.
* Encapsulation enforces the separation of a class' interface and implementation.
  A class that is encapsulated **hides** its implementation -- users of the class can use the interface
  but have no access to the implementation.
  
A class that uses data abstraction and encapsulation defines an **abstract data type**(ADT).  
In an ADT, the class **designer** worries about how the class is implemented.
Programmers who **use** the class need not know how the type works. They can instead think *abstractly* about what the type does.




### 7.1 Defining Abstract Data Type

#### 7.1.1 Designing the Sales_data Class

Ultimately, We want, Sales_data to support the same set of operations as the Sales_item class.

The interface to Sales_data consists of the following operations:
* An *isbn* member function to return the object's ISBN.
* A *combine* member function to add one Sales_data object into another.
* A function named *add* to add two Sales_data objects.
* A *read* function to read data from an istream into a Sales_data object.
* A *print* function to print the value of a Sales_data object on an ostream.

C++ programmers tend to speak of **users** interchangeably as
users of the application or users of a class.

Example of using the interface to write a version of the bookstore program
with Sales_data objects rather than Sales_items.
``` C++
Sales_data total; // variable to hold the running sum

if(read(cin, total)){
    Sales_data trans; // variable to hold data for the next transaction
    while(read(cin, trans)){
        if(total.isbn() == trans.isbn())
            total.combine(trans);
        else{
            print(cout, total) << endl;
            total = trans;
        }
    }
    print(cout, total) << endl;
}
else{
    cerr << "No data?!" << endl;
}
```


#### 7.1.2 Defining the Revised Sales_data Class

* Member functions **must** be **declared** inside the class.  
  Member functions **may** be **defined** inside the class itself or outside the class body.  
  Functions defined in the class are implicitly **inline**.
* Nonmember functions that are part of the interface, such as add, read, and print, are **declared and defined** outside the class.

The newer Sales_data
``` C++
struct Sales_data {
	std::string isbn() const { return bookNo; }
	Sales_data& combine(const Sales_data&);
	double avg_price() const;

	std::string bookNo;
	unsigned units_sold = 0;
	double revenue = 0.0;
};

Sales_data add(const Sales_data&, const Sales_data&);
std::ostream &print(std::ostream&, const Sales_data&);
std::istream &read(std::istream&, Sales_data&);
```

Member functions access the object on which they were called through
an extra, implicit parameter named **this**.  
When we call a member function, *this* is initialized with the **address of the object** on which the function was invoked.

Inside a member function, we can refer directly to the members of the object on which function was called.  
We **do not** have to use a member access operator to use the member of the object.  
Any direct use of a member of the class is assumed to be a an implicit reference through *this*.

The *this* parameter is **defined** for us implicitly.  
It is illegal for us to define a parameter or variable named *this*.  
Inside the body of a **member** function, we can **use** *this*.

*this* is a **const pointer** (top-level const).  
By default, the type of *this* is a const pointer to the **nonconst** version of the class type.  
Although it is implicit, it follows the normal initialization rules,
which means that (by default) we cannot bind it to a const object,
which means that we cannot call an ordinary member function on a const object.

Sometimes, if the member function doesn't change object
on which it is called, it is more flexible for *this* to be a (const) pointer to a const object.  
C++ resolves the problem by letting us put **const** **after** the parameter list of a member function.

A **const** following the parameter list indicates that *this* is a pointer to const.  
Member functions that use const this way are called **const member functions**.

Const member functions **cannot** change the object on which they are called.  
Objects that are const, and references or pointers to const objects, may call only const member functions.

A class is itself a scope.

The compiler processes classes in two steps.  
The member declarations are compiled **first**,
after which the member function bodies, if any, are processed.  
Thus, member function bodies may use other members of their class regardless of
where in class those members appear.

The name of a member defines outside the class must include the name of the class of which it is a member.

We do not need to use the implicit *this* pointer to access the members of the object
on which a member function is executing.  
But we do need to use this to access the object **as a whole**.


#### 7.1.3 Defining Nonmember Class-Related Functions

Functions that are conceptually part of the class, but not defined inside the class,
are typically **declared** (but **not defined**) in the same header as the class itself.

When taking IO classes as parameters, functions usually take ordinary references because:
* The IO classes are types that cannot be copied.
* Reading or writing to a stream **changes** that stream.

Ordinarily, functions that do output should do **minimal formatting**.  
So they usually do not print a newline at the end.
That way user code can decide whether the newline is needed.


#### 7.1.4 Constructors

Each class defines **how objects of its type can be initialized**.  
Classes control object initialization by defining one or more **special member functions**
known as **constructors**.

A constructor is run **whenever** an object of a class type is created.

Constructors have the **same name** as the class, and have **no return type**.  
A class can have multiple constructors, with the same rules of overloaded functions.  
Constructor **may not** be declared as **const**.
When we create a const object of a class type, the object does not assumes its constness 
until after the constructor completes the object's initialization.

Classes control default initialization by defining a special constructor,
known as the **default constructor**.
The default constructor is one that **takes no arguments**.

If our class does not *explicitly* define any constructor,
the compiler will *implicitly* define the default constructor for us.  
The compiler-generated constructor is known as the **synthesized default constructor**.  
For most classes:
* If there is an in-class initializer, use it to initialize the member.
* Otherwise, default-initialize the member.

Some classes **cannot** rely on the synthesized default constructor.  
So these classes **must** define a default constructor.
* The compiler generates the default for us only if we do not define **any** other constructors for the class.  
  If we define any constructors, the class will not have a default constructor unless we define that constructor ourselves.
* For some classes, the synthesized default constructor does the **wrong** thing.  
  Members of built-in type and compound type (e.g. arrays and pointers) have undefined value when default initialized without in-class initializers.
* Sometimes the compiler is unable to synthesize a default constructor.  
  For example, a member of a class type, which does not have a default constructor.
 
In C++11, if we want the default behavior, we can ask the compiler to generate the constructor for us
by writing **= default** after the parameter list.  
It can appear with the declaration inside the class body, and the default constructor will be inline,
or on the definition outside the class body.

The **constructor initializer** is a list of member names, each of which is followed by that member's initial value
in **parentheses** (or inside **curly braces**).  
Multiple constructor initializers are separated by commas.

The **constructor initializer list** specifies initial values of the data members of a class.
The members are initialized to the values specified in the initializer list
**before** the body of the constructor executes.  

When a member is omitted from the constructor initializer list,
it is implicitly initialized using the same process as is used by
the synthesized default constructor.

It is usually best for a constructor to use an in-class initializer
if one exists and gives the member the correct value.


#### 7.1.5 Copy, Assignment, and Destruction

Classes also control what happens when we copy, assign or destroy objects of the class type.
* Objects are copied such as when we initialize a variable, or when we pass or return an object by value.
* Objects are assigned when we use the assignment operator.
* Objects are destroyed when we ceased to exist.

Objects stored in a vector or an array are destroyed
when that vector or array is destroyed.

If we do not define these operations, the compiler will *synthesize* for us.  
Ordinarily, the versions that the compiler generates execute by copying, assigning or destroying
each member of the object.

Some classes **cannot** rely on the synthesized versions.  
In particular, they are unlikely to work correctly for classes that
**allocate** resources that reside **outside** the class objects themselves.

Many classes that need *dynamic memory* can (and generally should)
use a vector or a string to manage the necessary storage.  
Classes that use vectors and strings avoid the complexities involved in allocating and deallocating memory.
* The synthesized versions for copy, assignment, and destruction work **correctly**
  for classes that have vector or string members.
* When we copy or assign an object that has a vector member,
  the vector class takes care of copying or assigning the elements in that member.
* When the object is destroyed, the vector member is destroyed,
  which in turn destroys the elements in the vector.
* Similar for strings.



### 7.2 Access Control and Encapsulation

In C++ we use **access specifier** to enforce *encapsulation*:
* Members defined after a **public** specifier are accessible to
  **all part** of the program.  
  The public members define the **interface** to the class.
* Members defined after a **private** specifier are accessible to
  the **member functions** of the class, but are **not** accessible to
  code that **uses** the class.  
  The private sections encapsulate (i.e. hide) the **implementation**.
  
A class may contain zero or more (no restrictions) access specifiers.  
The specified access level remains until the **next** access specifier or the **end** of the class body.

We can define a class type using either *class* or *struct*.  
The **only** difference between struct and class is the default access level.  
* If we use struct, the members before the first access specifier are **public**.
* If we use class, the members before the first access specifier are **private**.


#### 7.2.1 Friends

A class can allow another class of function to access its **nonpublic** members
by making that class of function a **friend**.

A class makes a function its friend by including a **declaration** for that function
preceded by the keyword **friend**.

Friend declarations may appear only **inside** a class definition,
and may appear anywhere in the class.  
Ordinarily it is a good idea to group friend declarations together
at the beginning or end of the class definition.

Friends are **not** members of the class and are **not** affected by the access control of the section in which they are declared.

Encapsulation provided two important advantages:
* User code cannot inadvertently corrupt the state of an encapsulated object.
* The implementation of an encapsulated class can change over time
  without requiring changes in user-level code.
  
Although user code need not change when a class definition changes,
the source files that use a class must be **recompiled** any time the class changes.

A friend declaration only specifies **access**.
It is not a general declaration of the function.  
If we want users of the class to be able to call a friend function,
then we must also declare the function **separately** from the friend declaration.  
To make a friend visible to users of the class,
we usually declare each friend (outside the class) in the same header as the class itself.



### 7.3 Additional Class Features


#### 7.3.1 Class Member Revisited

In addition to defining data and function members, a class can define
its own **local names** for types.  
Type names defined by a class are subject to the same access controls as any other member
and may be either public or private.

Unlike ordinary members, members that define types must appear **before they are used**.  
Thus, they usually appear at the beginning of the class.

We can explicitly declare a member function as **inline**:
* as part of its declaration inside the class body.
* on the function definition that appears outside the class body.
* also legal on both sides (although not required).

Specifying inline only on the definition outside the class
can make the class easier to read.

Member functions may be overloaded as normal functions.

Sometimes a class has a data member that we want to be able to modify,
even inside a **const** member function.  
We indicate such members by including the **mutable** keyword in their declaration.

A *mutable data member* is **never const**, even when it is a member of a const object.  
A const member function may change a mutable member.

When we initialize a member of class type,
we are supplying arguments to a **constructor** of that member's type.

In-class initializers must use either the = form of initialization
or the direct form of initialization using curly braces.


#### 7.3.2 Functions That Return \*this

A const member function that returns \*this as a reference should
have a return type that is a reference to const.

We can overload a member function based on whether it is const
for the same reasons that we can overload a function based on whether a pointer parameter points to const.

Use private utility for functions for common code:


#### 7.3.3 Class Types

Every class defines a unique type.  
Two different classes define two different type **even** if they define the same members.

We can refer to a class type directly by using the class name as a type name.  
Alternatively, we can use the class name following the keyword class or struct.

We can declare a class without defining it.  
These declarations are referred to a forward declaration.  
After a declaration and before a definition is seen, the class type is an **incomplete type**.  
We can use an incomplete type in only two ways:
* define pointers or references to such types.
* declare (but **not define**) functions that use an incomplete type as a parameter or return type.

The class must be defined **before** a reference or pointer is used
to access a member of the type.

With one exception, data members can be specified to be of a class type
**only if** the class has been defined.

Because a class is not defined until its class body is complete,
a class **cannot** have data members of its own type.  
However, a class is considered declared as soon as its class name has been seen.
So a class can have data members that are pointers or references to its own type.


#### 7.3.4 Friendship Revisited

A class can make another class its friend
or it can declare specific member functions of another (defined) class as friends.  
In addition, a friend function can be defined inside the class body, and implicitly inline.

The member functions of a friend class can access **all** the members,
including the nonpublic members.

Friendship is **not transitive**.

Rather than making the entire class a friend, we can instead specify that
only a member is allowed access.  
When we declare a member function to be a friend, we must specify
the class of which that function is a member.

Making a member function a friend requires careful structuring of our programs
to accommodate interdependencies among the declarations and definitions.

A class must declare as a friend each function in a set of overloaded functions
that it wishes to make a friend.

Classes and nonmember functions need **not** have been declared before they are used in a friend declaration.

When a name first appears in a friend declaration, that name is implicitly
*assumed* to be part of the surrounding scope.  
However, the friend itself is **not** actually declared in that scope.

Even if we define the function inside the class, we must still provide a declaration
outside of the class itself to make the function visible.  
A declaration must exist even if we only call the friend from members of the friendship granting class.
``` C++
struct X {
    friend void f() { /* friend function can be defined in the class body */}
    X() { f(); } // error: no declaration for f
    void g();
    void h();
};

void X::g() { return f(); } // error: f hasn't been declared
void f(); // declare the function defined inside X
void X::h() { return f(); } // ok: declaration for f is now in scope
```



### 7.4 Class Scope

Every class defines its own new scope. Outside the class scope:  
* Ordinary data and function members may be accessed only through
  an object, a reference, or a pointer using a member access operator.
* Type members may be accessed from the class using the scope operator.

Once the class name is seen, the remainder of the definition, including
the parameter list and the function  body, is in the scope of the class.  
Thus, we can refer to other class members **without** qualification.

The return type of a function normally appears **before** the function's name.  
When a member function is defined outside the class body,
any name used in the return type is outside the class scope.  
Thus, the return type must specify the class of which it is a member.


#### 7.4.1 Name Lookup and Class Scope

**name lookup** is the process of finding which declarations match the use of a name:
* First, look for a declaration of the name in the block in which the name was used.
  Only names declared **before** the use are considered.
* If the name isn't found, look in the enclosing scope(s).
* If no declaration is found, then the program is in error.

Class definitions are processed in two phases:
* First, the member declarations are compiled.
* Function bodies are compiled only after the **entire** class has been seen.

Thus, member functions can use any name defined inside the class **in the function body**.  

However, names used in declarations, including names used for the return type and types in the parameter list,
**must** be seen **before** they are used.  
If a member declaration uses a name that has not yet been seen inside the class,
the compiler will look for that name in the scope(s) in which the class is defined.

In a class, if a member uses a name from an outer scope and that name is a **type**,
then the class may **not** subsequently redefine that name:
``` C++
typedef double Money;
class Account{
public:
    Money balance() { return bal; } // uses Money from the outer scope
private:
    typedef double Money; // error: connot redefine Money
    Money bal;
    
    // ...
};
```

Definitions of type names usually should appear at the **beginning** of a class.

A name used in the body of a member function is resolved as follows:
* First, look for a declaration of the name **inside the member function**.
  Only declarations in the function body that **precede** the use of the name are considered.
* If the declaration is not found inside the member function,
  look for a declaration **inside the class**. **All** the members of the class are considered.
* If a declaration for the name is not found in the class,
  look for a declaration that is **in scope before** the member function definition.
  
It is a **bad** idea to use the name of another member as the name for a parameter in a member function.  

Even though the class member is hidden, it is still possible to use that member
by qualifying the member's name with the name of its class
or by using the *this* pointer explicitly.

Even though the outer object is hidden, it is still possible to access that object
by using the scope operator.
``` C++
// bad pracitce: don't hide names that are needed from surrounding scopes

void Screen::dummy_fcn(pos height){
    cursor = width * ::height; // the global "height"
}
```

When a member is defined **outside** its class, the third step of name lookup
includes names declared in the scope of the member definition as well as those
that appear in the scope of the class definition.
``` C++
int height;
class Screen {
public:
    typedef std::string::size_type pos;
    void setHeight(pos);
    pos height = 0;
};

Screen::pos verify(Screen::pos);
void Screen::setHeight(pos var){
    // var: refers to the parameter
    // height: refers to the class member
    // verify: refers to the global function
    height = verify(var);
}
```



### 7.5 Constructors Revisited


#### 7.5.1 Constructor Initializer List

Exactly the **same distinction** between initialization and assignment
applies to the data members of objects.  
How significant this distinction is depends on the type of the data member.  
* In the constructor initializer list: initialization.
* In the constructor body: assignment.

If we do not explicitly initialize a member in the constructor initializer list,
that member is default initialized before the constructor body starts executing.

``` C++
Sales_data::Salel_data (const string &s, unsigned cnt, double price)
{
    bookNo = s;
    units_sold = cnt;
    revenue = cnt * price;
}
```
The constructor above **assigns** values to the data members rather than **initializes**.

We can often, but **not always**, ignore the distinction between
whether a member is initialized or assigned.
* Members that are const or references must be initialized.
* Members that are of a class type that does not define a default constructor
  also must be initialized.
  
By the time the **body** of the constructor begins executing, initialization is **complete**.  
The **only** chance to initialize const or reference data members is
in the constructor initializer.

Advice: use constructor initializers routinely.

Each member may be named only **once** in the constructor initializer.

The constructor initializer list **does not** specify the **order** in which
those initializations are performed.  
Members are initialized in the order in which they appear in the **class definition**.  

It is a good idea to write constructor initializers in the **same** order
as the members are **declared**.  
Moreover, if possible, avoid using members to initialize other members.

A constructor that supplies default arguments for **all** its parameters
also define the **default** constructor.


#### 7.5.2 Delegating Constructors

In C++11, a **delegating constructor** uses another constructor from
its own class to perform its initialization.

A delegate constructor has a member initializer list and a function body as well.  
The member initializer list has a **single entry** that is the name of the class itself.
The bane of the class is followed by a parenthesized list of arguments.  
The argument list must match another constructor in the class.

``` C++
class Sales_data{
public:
    // nondelegating constructor initializes members from corresponding arguments
    Sales_data(std::string s, unsigned cnt, double price):
        bookNo(s), units_sold(cnt), revenue(cnt * price){}
    // remaining constructors all delegate to another constructor
    Sales_data():
        Sales_data("", 0, 0) {}
    Sales_data(std::string s):
        Sales_data(s, 0, 0) {}
    Sales_data(std::istream &is):
        Sales_data() { read(is, *this); }
    
    // ...
};
```

When a constructor delegates to another constructor, the constructor initializer list
and function body of the delegated-to constructor are **both** executed.  
Then the function body of the delegating constructor is executed.


#### 7.5.3 The Role of the Default Constructor

The default constructor is used automatically whenever an object is
**default** or **value** initialized.

Default initialization happens:
* When we define *nonstatic* variables or arrays at **block scope** without initializers.
* When a class that itself has members of **class** type uses the **synthesized default constructor**.
* When members of class type are not explicitly initialized in a constructor initializer list.

Value initialization happens:
* During array initialization when we provide fewer initializers than the size of the array.
* When we define a local static object without an initializer.
* When we explicitly request value initialization by writing an expression of the form T()
  where T is the name of a type.
  
In practice, it is almost **always right** to provide a default constructor
if other constructors are being defined.

``` C++
class NoDefault {
public:
    NoDefault(const std::string &);
};

struct A {
    NoDefault my_mem;
};

A a; // error: cannot synthesize a constructor for A

struct B {
    B() {} // error: no initializer for b_member
    NoDefault b_member;
};
```

The correct way to define an object that uses the default constructor for initialization
is to **leave off** the trailing, empty parentheses.  
If we don't leave off the parentheses, we will declare a function, not an object.  

