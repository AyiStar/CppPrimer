# Notes in Chapter 8

## Chapter 8. The IO Library

### 8.1 The IO Classes

The IO types and objects that we've used so far manipulate *char* data.

To support different kinds of IO processing, the library defines a collection of IO types,
which are defined in three separated headers:
* \<iostream\> defines the basic types used to read from and write to a *stream*.
    * istream, wistream read from a stream.
    * ostream, wostream write to a stream.
    * iostream, wiostream read and write a stream.
* \<fstream\> defines the types used to read and write *named files*.
    * ifstream, wifstream read from a file.
    * ofstream, wofstream write to a file.
    * fstream, wfstream read and write a file.
* \<sstream\> defines the types used to read and write *in-memory strings*.
    * istringstream, wistringstream read from a string.
    * ostringstream, wostringstream write to a string.
    * stringstream, wstringstream read and write a string.

The names of the wide-character versions of types and objects begin with a "w",
such as wcin, wcout, wcerr.  
They are defined in the same header as the plain char types.

Conceptually, neither the *kind of device* nor the *character size*
affects the IO operations we want to perform.  
The library lets us ignore the differences among these different kinds of stream
by using **inheritance**.

Inheritance lets us say that a particular class inherits from another class.
Ordinarily, we can use an object of an inherited class as if were an object
of the same type as the class from which it inherits.


#### 8.1.1 No Copy or Assign for IO Objects

We **cannot** copy or assign objects of the IO types.  
Thus, we cannot have a *parameter* or *return type* that is one of the stream types.

Functions that do IO typically pass and return the stream through references.  
Reading or writing an IO object changes its state, so the reference must no be const.


#### 8.1.2 Condition States

The IO classes define functions and flags that let us access and manipulate the *condition state* of a stream.  
* strm::iostate: a machine-dependent integral **type** that represents the condition state of a stream.
* strm::badbit: strm::iostate **value** used to indicate that a stream is **corrupted**.
* strm::failbit: strm::iostate **value** used to indicate that an IO operation **failed**.
* strm::eofbit: strm::iostate **value** used to indicate that a stream hits **end-of-file**.
* strm::goodbit: strm::iostate **value** used to indicate that a stream is **not in an error state**.
    This value is **guaranteed** to be zero.
* s.eof(): true id eofbit in the stream is set.
* s.fail(): true if failbit **or badbit** in the stream is set.
* s.good(): true if the stream is in a valid state.
* s.clear(): Reset all condition values in the stream s to **valid** state.
* s.clear(flags): Reset the condition of s to flags. Type of flags is is strm::iostate. Return void.
* s.setstate(flags): Add specified condition(s) to s. Type of flags is strm::iostate. Return void.
* s.rdstate(): Return current condition of s as a strm::iostate value.

For example, std::cin will be in an error state if we enter an end-of-file or something that it does not expect.

Once an error has occurred, subsequent IO operations on that stream will **fail**.

The easiest way to determine whether a stream is in a non-error state is
use that object as a *condition*.

##### Interrogating the State of a Stream

* badbit indicates a system-level failure, such as an unrecoverable read or write error.
  it is usually **not possible** to use a stream once badbit has been set.
* failbit is set after a recoverable error, such as reading a character when numeric data was expected.
  It is often possible to correct such problems and continue using the stream.
* eofbit (and failbit) is set after an eof is read.
* goodbit indicates no failures on the stream.

If any of badbit, failbit, or eofbit are set, then a condition that evaluates that stream will fail.

The right way to determine the overall state of a stream is to use either good or fail.  
Indeed, the code that is executed when we use a stream as a condition is equivalent to calling **!fail()**.

##### Managing the Condition State

To turn off a single condition, we use the rdstate member and the **bitwise operators**
to produce the desired new state.
``` C++
// turn off failbit and badbit but all other bits unchanged
cin.clear(cin.rdstate() & ~cin.failbit & ~cin.badbit);
```


#### 8.1.3 Managing the Output Buffer

Each output stream manages a buffer, which it uses to hold the data
that the program reads and writes.  
Using a buffer allows the OS to combine several output operations
from our program into a single system-level write.

There are several conditions that causes the buffer to be **flushed**
(that is, to be **written**) to the actual output device or file:
* The program completes normally. All output buffers are flushed as part of the return from main.
* At some indeterminate time, the buffer can become **full**, in which case it will be flushed before writing the next value.
* We can flush the buffer **explicitly** using a manipulator such as std::endl.
* We can use the **unitbuf** manipulator to set the stream's internal state
  to empty the buffer after each output operation.  
  By default, unitbuf is set for cerr, so that writes to cerr are flushed immediately.
* An output stream may be tied to another stream. In this case, the buffer of the tied stream is flushed
  whenever the tied stream is read or written.  
  By default, cin and cerr are both tied to cout. Hence, reading cin or writing to cerr flushes the buffer in cout.
  
In addition to endl, there are two other similar manipulators to flush the buffer:**flush** and **ends**.  
**flush** flushes the stream but adds no characters to the output.  
**ends** inserts a null character into the buffer and then flushes it
``` C++
cout << "hi" << endl; // writes hi and a newline, then flushes the buffer.
cout << "hi" << flush; // writes hi, then flushes the buffer
cout << "hi" << ends; // writes hi and a null, then flushes the buffer
```

##### The unitbuf Manipulator

If we want to flush after **every** output, we can use the **unitbuf** manipulator.  
The **nounitbuf** manipulator restores the stream to use normal, system-level buffer flushing.
``` C++
cout << unitbuf; // all writes sill be flushed immediately
// any output is flushed immediately without buffering
cout << nounitbuf; // return to normal buffering
```

##### Caution: Buffers Are Not Flushed If the Program Crashes

Output buffers are not flushed if the program terminates abnormally.

When debugging a program that has crashes, it is essential to make sure
that any output you *think* should have been written was actually flushed.

##### Tying Input and Output Streams Together

When an input stream is tied to an output stream, any attempt to read the input stream will first flush the buffer associated with the output stream.

The library ties cout to cin.

Interactive systems usually should tie their input stream to their output stream.  
Doing so means that all output, which might include *prompts* to the user,
will be written before attempting to read the input.

There are two overloaded versions of **tie**:
* One version that takes no argument and returns a pointer to the output stream,
  if any, to which this object is currently tied. The function returns the null pointer if the stream is not tied.
* The second version takes a pointer to an ostream and ties itself to that ostream.

We can tie either an istream or an ostream object to another ostream.
``` C++
cin.tie(&cout); // illustration only: the library ties cin and cout for us

// old_tie points to the stream (if any) currently tied to cin
ostream *old_tie = cin.tie(nullptr); // cin is no longer tied

// ties cin and cerr; not a good idea because cin should be tied to cout
cin.tie(&cerr); // reading cin flushes cerr, not cout
cin.tie(old_tie); // reestablish normal tie between cin and cout
```

Each stream can be tie to **at most one** stream at a time.  
Multiple streams can tie themselves to the same ostream.



### 8.2 File Input and Output

\<fstream\> header defines three types to support file IO:
ifstream, ofstream, fstream.

These types provide the **same** operations as those we have previously used on the objects cin and cout,
such as \<\<, \>\>, getline.  
In addition, the types add members to manage the file associated with the stream.  
* fstream fstrm; create an unbound file stream. fstream presents one of the types defined in \<fstream\>.
* fstream fstrm(s); create an fstream and opens the file named s.
  s can have type string or can be a pointer to a C-style character string.
* fstream fstrm(s, mode); Like the previous constructor, but opens s in the given mode.
* fstrm.open(s): open the file named by s and bind that file to fstrm. Return void.
* fstrm.open(s, mode): Like the previous constructor. The default mode depends on the type of fstream. Return void.
* fstrm.close(): Close the file to which fstrm is bound. Return void.
* fstrm.is_open(): Return a bool indicating whether the file associated with fstrm was successfully opened and has not been closed.


#### 8.2.1 Using File Stream Objects

When we want to read or write a file, we define a file stream object and **associate** that object with the file.  
Each file stream class defines a member function named **open** that does whatever system-specific operations are required
to locate the given file and open it for reading or writing as appropriate.

When we create a file stream, we can (optionally) provide a file name.
When we supply a file name, *open* is called automatically.  
``` C++
ifstream in(ifile); // construct an ifstream and open the given file
ofstream out; // output file stream that is not associated with any file
```

``` C++
ifstream input(arg[1]); // open the file of sales transactions
ofstream output(arg[2]); // open the output file
Sales_data total; // variable to hold the running sum
if (read(input, total)){ // read the first transaction
    Sales_data trans; // variable to hold data for the next transaction
    while (read(input, trans)){ // read the remaining transactions
        if (total.isbn() == trans.isbn()) // check isbns
            total.combine(trans); // update the running total
        else{
            print(output, total) << endl; // print the results
            total = trans; // process the next book
        }
    }
    print(output, total) << endl; // print the last transaction
} else
    cerr << "No data?!" << endl;
```

We can use an object of an **inherited** type in places
where an object of the original type is expected.

##### The *open* and *close* Members

When we define an empty file stream object, we can subsequently associate
that object with a file by calling **open**.  
``` C++
ifstream in(ifile); // construct an ifstream and open the given file
ofstream out; // output file that is not associated with any file
out.open(ifile + ".copy"); // open the specified file
```

If a call to *open* fails, **failbit** is set.  
Because a call to open might fail, it is usually a good idea to verify that the *open* succeeded.  
``` C++
if (out) // check that the open succeeded
    // the open succeeded, so we can use the file
```

Calling *open* on a file stream that is already open will *fail* and set *failbit*.  
To associate a file stream with a different file, we must first **close** the existing file.
``` C++
in.close(); // close the file
in.open(ifile + "2"); // open another file
```


##### Automatic Construction and Destruction

Here an example whose main function takes a list of files it should process.
``` C++
for (auto p = argv + 1; p != argv + argc; ++p) {
    ifstream input(*p); // create input and open the file
    in (input) { // if the file is ok, process the file
        process(input);
    } else
        cerr << "couldn't open: " + string(*p);
} // input goes out of scope and is destroyed on each iteration
```

When an fstream object goes out of scope, the file it is bound to
is automatically **closed**.


#### 8.2.2 File Mode

Each stream has an associated **file mode** that represents how the file may be used.  
* in: open for input
* out: open for output
* app: seek to the end before every write
* ate: seek to the end immediately after the open
* trunc: truncate the file
* binary: do IO operations in binary mode

We can supply a file mode whenever we open a file.  
The modes that we can specify have the following restrictions:  
* out may be set only for an ofstream or fstream object.
* in may be set only for an ifstream or fstream object.
* trunc may be set only when out is also specified.
* app mode may be specified so long as trunc is not.
  If app is specified, the file is always opened in output mode, even if out was not explicitly specified.
* By default, a file opened in out mode is truncated even if we do not specify trunc.  
  To preserve the contents of a file opened with out, we must also specify app, or we must also specify in.
* ate and binary modes may be specified on any file stream object type
  and in combination with any other file mode.
  
Each file stream type defines a **default** mode:  
* ifstream: in mode.
* ofstream: out mode.
* fstream: in and out modes.

##### Opening a File in out Mode Discards Existing Data

By default, when we open an ofstream, the contents of the file are **discarded**.

``` C++
// file1 is truncated in each of these cases
ofstream out("file1"); // out and trunc are implicit
ofstream out2("file1", ofstream::out); // trunc is implicit
ofstream out3("file1", ofstream::out | ofstream::trunc);

// to preserve the file's contents, we must explicitly specify app mode
ofstream app("file2", ofstream::app); // out is implicit
ofstream app2("file2", ofstream::out | ofstream::app); 
```

The only way to preserve the existing data in a file opened by an ofstream
is to specify app or in mode explicitly.

##### File Mode Is Determined Each Time *open* Is Called

The file mode fo a given stream may change each time a file is opened.  

``` C++
ofstream out; // no file mode is set
out.open("scratchpad"); // mpde implicitly out and trunc
out.close();
out.open("previous", ofstream::app); // mode is out and app
out.close();
```


### 8.3 *string* Streams

\<sstream\> defines 3 types to support in-memory IO.  
These types read from or write to a string as if the string were an IO stream.

stringstream-specified operations:  
* sstream strm; strm is an unbound stringstream. sstream is one of the types defined in \<sstream\>.
* sstream strm(s); strm is an sstream that holds a copy of the string s.
  This constructor is explicit.
* strm.str(): return a copy of the string that strm holds.
* strm.str(s): copies the string s into strm. Return void.


#### 8.3.1 Using an istringstream

An istringstream is often used when we have some work to do on an **entire line**,
and other work to do with individual **words** within a line.

``` C++
struct PersonInfo{
    string name;
    vector<string> phones;
};

string line, word; // will hold a line and word from input, respectively
vector<PersonInfo> people; // will hold all the records from the input

// read the input a line at a time until cin hits end-of-file (or another error)
while (getline(cin, line)) {
    PersonInfo info; // create an object to hold this record's data
    istringstream record(line); // bind record to the line we just read
    record >> info.name; // read the name
    while (record >> word) // read the phone numbers
        info.phones.push_back(word); // and store them
    people.push_back(info); // append this record to people
```

#### Using ostringstreams

An ostringstream is useful when we need to **build up our output a little at a time**
but **do not** want to print the output until later.

``` C++
for (const auto &entry : people) { // for each entry in people
    ostringstream formatted, badNums; // objects created on each loop
    for (const auto &nums : entry.phones) { // for each number
        if (!valid(nums)) {
            badNums << " " << nums; // string in badNums
        } else
            // "writes" to formatted's string
            formatted << " " << format(nums);
    }
    if (badNums.str().empty()) // there were no bad numbers
        os << entry.name << " " //print the name
           << formatted.str() << endl; // and reformatted numbers
    else
        cerr << "input error: " << entry.name
             << " invalid number(s) " << badNums.str() << endl;
}
```

