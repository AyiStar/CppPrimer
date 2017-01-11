# Notes in Chapter5

## Chapter5. Statements

### 5.1 Simple Statements

Most statements in C++ end with a *semicolon*.

An expression becomes a **expression statement** when it is followed by a semicolon.  
An expression statement causes the expression to be evaluated and its result discarded.  
Commonly, an (useful) expression statement contains an expression that has a side effect,
such as assigning a new value to a variable, or printing a result, when it is evaluated.

A single semicolon is a null statement.
It is useful when the language requires a statement but the program's logic does not.
``` C++
while(cin >> s && s != sought)
    ;
```

Null statements should be **commented**.
That way anyone reading the code can see that the statement was omitted intentionally.

Beware of missing or extraneous semicolons.  
Semicolons that might appear illegal are often nothing more than null statements.
Although they are often harmless, they can alter the programmer's intent in a while or if.

A **compound statement**, or a **block**, is a (possibly empty) sequence of statements
and *declarations* surrounded by a pair of curly braces.

A block is a **scope**.

Compound statements are used when the language requires a single statement
but the logic of our program needs more than one.

A block is **not** terminated by a semicolon.



### 5.2 Statement Scope

Variable defined in the control structure (if, switch, while, for)
are visible only **within** that statement and are out of scope after the statement ends.



### 5.3 Conditional Statements

