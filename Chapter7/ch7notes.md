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

