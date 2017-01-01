#notes in chapter 1

## Chapter 1. Getting Started

### 1.1 Writing a Simple C++ Program

**function definition**:
 * return type
 * function name
 * parameter list
 * function body
  
Main function is required to have a return type of **int**.

A **function body** is a block of statements starting with an open curly brace and ending with a close curly

The value returned from main is a status indicator: 0 for success, nonzero for what kind of error occurred (defined by the system).

A **type** defines both the *contens of the data* and the *operations that are possible on those data*.

**data** are stored in **variables**, and every **variables** has a **type**.


### 1.2 A First Look at I/O

C++ **does not** define statements to do I/O, but includes **standard library** that provides I/O.

Fundamental to the *iostream* library are two *types* names **istream** and **ostream**.

A **stream** is a *sequence of characters read from or written to an IO device*.
**stream** is intended to suggest that the characters are *generated or consumed sequentially over time*.

Four IO **objects**:
* **cin**: standard input (istream)
* **cout**: standard output (ostream)
* **cerr**: standard error (ostream)
* **clog**: general infomation about the execution of the program. (ostream)

The #include directive must be written in a single line, and outside of any function.

An **expression** yields a *result* and is composed of one or more *operands* and (usually) an *operator*.

The **<<** operator in ostream:
* two operands: an *ostream object*(left-hand), a *value* to print(right-hand). 
* functionality: writes the given *value* on the given *ostream*.
* result: left-hand operand, i.e. the *ostream* which we wrote on.

A **string literal** is a sequence of characters enclosed in double quotation marks.

**std::endl** is a special value called a *manipulator*, and has the effect of *ending the current line* and *flushing the buffer associated with that device.

**Flushing the buffer** ensures that all the output the program has generated so far is actually written to the output stream, rather than sitting in memory waiting to be written.

Print statements for debugging should *always* flush the stream to ensure that if the programs crashes, output won't be left in the buffer, leading to incorrect inferences about where the program crashed.
 
When initializing a variable, we give it the indicated value *at the same time as the variable is created*.
 
The **>>** operator in istream:
* two operands: an *istream object*(left-hand), an *object* (right-hand). 
* functionality: reads data from the given istream and stores what was read in the given object.
* result: left-hand operand, i.e. the *istream* which we read from.


### 1.3 A Word About Comments

**Comment pairs do not nest**: a comment that begins with /* ends with the next *./.\


### 1.4 Flow of Control

A **condition** is an expression that yields a result that is either *true* or *false*.

An *istream* can be used as a *condition*, and the effect is to test the condition of the stream.  
If the stream is valid (hasn't encountered an error), the condition is *ture*.  
An istream becomes invalid when it reads EOF or wrong input.

The most common kinds of errors a *compiler* will detect:
* *Syntax error*: a grammartical error in the language
* *Type error*
* *Declaration error*

Correct errors in the sequence they are reported, and recompile the code after each fix.


### 1.5 Introducing Classes

To use a **class** we should know:
* What is its *name*?
* *Where* is it defined?
* What *operations* does it support?

The standard library headers typically have *no suffix* at all.

Every *class* defines a *type*, whose name is the same as the class.

Part of what we can do with class *Sales_item* :
* Define an object of the class type as with built-in type.
* Call *isbn* function to fetch the ISBN from a Sales_item object.
* Use >> and << to read and write objects of type Sales_item.
* Use = to assign one Sales_item object to another.
* Use + to add two Sales_item objects. The result is a new Sales_item object whose ISBN is that of its operands and whose number sold and revenue are the sum of the corresponding values in its operands
* Use += to add one Sales_item object into another.

Headers from the standard library are enclosed in <>  
Headers not part of the library are enclosed in ""

A **member function** is a function that is defined as a part of a class.  
Member functions are somtimes referred to as *methods*.

The **dot operation (.)** :
* left-hand operand: an object of class type.
* right-hand operand: name of a member of that type.
* result: member named by the right-hand operand.


### 1.6 The Bookstore Program

### Chapter Summary

Defined Terms:
* **argument**: Values passed to a function.
* **buffer**: A region of storage used to hold data.
    IO facilities often store input/output in a buffer and read/write the buffer independently from actions in the program.
    Output buffers can be explicitly flushed to force the buffer to be written.
    By defalut, reading cin flushes cout; cout is also flushed when the program ends normally.
* **cerr**: ostream object tied to the standard error.
    By default, writes to cerr are *not buffered*.
    Usually used for error messages or other output that is not part of the normal logic of the program.
* **clog**: ostream object tied to the *standard error*.
    By default, writes to clog are *buffered*.
    Usually used to *report information about program execution to a log file*.
* **()operator**: Call operator. A pair of parentheses "()" following a function name.
    The operator causes a function to be invoked.
    Arguments to the function may be passed inside the parentheses.
    