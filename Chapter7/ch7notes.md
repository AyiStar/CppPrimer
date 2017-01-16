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