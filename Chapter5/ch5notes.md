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

A **dangling else**, is used to refer to the problem of
how to process nested if statements in which there are more ifs than elses.  
In C++, an else is always paired with the closest preceding unmatched if.  
But curly braces can be used to to effectively hide an inner if
so that the programmer can control which if a given else should match.

A switch statement executes by evaluating the parenthesized expression that follows the keyword switch.  
The expression may be an initialized variable declaration.  
The expression is converted to integral type.  
The result is compared with the value associated with each case.

If the expression matches the value of a case label,
execution begins with the first statement following that label.  
Execution **continues** normally from that statement through the end of the switch or until a break statement.  
If no match is found, execution falls through to the first statement following the switch.

The *case* keyword and its associated value together are known as the **label case**,
which must be **integral constant** expressions.  
It is **error** for any two case labels to have the same value.
In addition, *default* is a special case label.

There are situations where the default switch behavior is exactly what is needed.

Sometimes we have two or more values that share a common set of actions.
In such instances, we omit a break statement, allowing the program to fall through multiple case labels.  
Case labels need not appear on a new line.
We can emphasize that the cases represent a range of values by listing them all on a single line.

If we do omit a break, we'd better include a comment explaining the logic.

Although it is not necessary to include a break after the last label of a switch,
the safest way is to provide one.  
That way, if an additional case is added later, the break is already in place.

The statements following the default label are executed when no case label matches the value of the switch expression.  
It can be useful to define a default label even if there is no work for the default case.  
Defining an empty default section indicates to subsequent readers that the case was considered.

A label may not stand alone, it must precede a statement or another case label.

When execution jumps to  particular case, any code that occurred inside the switch **before** that label is ignored.  
It is illegal to jump from a place where a variable with an **initializer** is out of scope
to a place where that variable is in scope.
``` C++
case true: // this switch statement is illegal because thses initializations might be bypassed
    string file_name; // error: control bypasses an implicitly initializd variable
    int val = 0; // error: control bypasses an explicitly initialized variable
    int jval; // ok: because jval is not initialized
    break;
case false:
    jval = next_num(); // ok: jval is in scope but is not initialized, assign a value to jval
    if(file_name.empty()) // file_name is in scope but wasn't initialized
```
If this code is legal, then any time control jumped to the false case,
it would bypass the initialization of file_name and ival.  
Those variables would be in scope, and code following false could use them.  
However, they would not be initialized. Thus, the language does not allow us to jump over an initialization
if the initialized variable is in scope at the point to which control transfers.

If we need to define an initialize a variable for a particular case,
we can do so by defining the variable inside a *block*.



### 5.4 Iterative Statements

In a while statement, the condition can be an expression
or an initialized variable declaration.

Variables defined in a while condition or while body are created and **destroyed** on each iteration.
``` C++
while (int i = 1){
    ...
    --i;
}
// This loop will never terminate!
```

A while loop is generally used when we want to iterate *indefinitely*,
or also when we want access to the value of the loop control variable **after** the loop finished.

The syntactic form of the *for statement* is:  
for (*initializer*; *condition*; *expression*) (called the for header)   
    *statement*  
1. *initializer* is executed once at the start of the loop.
2. Next, *condition* is evaluated.
3. If *condition* is true, *statement* executes.
4. Finally, *expression* is evaluated.

The visibility of any object defined within the for header is limited to the body of the for loop.

The *initializer* in a for header may be only a single declaration statement.
Thus, all the variables must have the same base type.

A for header can omit any (or all) part(s),
but the semicolons may not be omitted.  
Omitting *condition* is equivalent to writing *true* as the condition.

The syntactic form of the *range for statement* is:  
for (*declaration* : *expression*)  
    statement  
* *expression* must represent a sequence, such as a braced initializer list,
  an array, or an object of a type such as vector or string that has begin and end members
  that return iterators.
* *declaration* defines a variable.  It must be possible to convert each element of the sequence
  to the variable's type. The easiest way is to use the *auto* type specifier.
  If we want to write to the elements in the sequence, the loop variable must be a reference type.
  
On each iteration, the control variable is defined and initialized by the next value in the sequence,
after which *statement* is executed.  

A range for is defined in terms of the equivalent traditional for:
``` C++
vector<int> v = {0,1,2,3,4,5,6,7,8,9};
for(auto &r : v){...}
// equivalen to
for(auto beg = v.begin(), end = v.end(); beg != end; ++beg)
{
    auto &r = *beg;
    ...
}
```

And that is why we cannot use a range for to add elements to a vector (or other container).
In a range for, the value of end() is cached.
If we add elements to (or remove elements from) the sequence, the value of *end* might be invalidated.

A *do while* end with a semicolon after the parenthesized condition.

In *do while*, variables used in *condition* must be defined **outside** the body of the do while statement.  
Because the *condition* is not evaluated until after the statement or block is executed, the do while loop
does not allow variable definitions inside the condition.



### 5.5 Jump Statements

Jump statements interrupt the flow of execution.  
C++ offers 4 jumps: *break*, *continue*, *goto*, *return*.

A break statement terminates **the nearest enclosing while, do while, for or switch** statement.
Execution resumes at the statement immediately following the terminated statement.

A break can appear only within an **iteration** statement or a **switch** statement
(including inside statements or blocks nested inside such loops).

Example:
``` C++
string buf;
while(cin >> buf && !buf.empty()){
    switch(buf[0]){
    case '-':
        // process up to the first blank
        for(auto it = buf.begin() + 1; it != bug.end(); ++it){
            if(*it == ' ')
                break; // #1, leave the for loop
                // ...
        }
        // break #1 transfers control here
        // remaining '-' processing
        break; // #2, leave the switch statement
    
    case '+':
        // ...
    } // end switch
    // break #2 transfers control here
} // end while
```

A **continue** statement terminates the **current iteration** of
the nearest enclosing loop and immediately begins the next iteration.

A continue can appear only inside a for, while, or do while loop,
including inside statement or blocks nested inside such loops.

A **goto** statement provides an *unconditional* jump
from the goto to another statement **in the same function**.

Programs **should not** use gotos.
They make programs hard to understand and hard to modify.

The syntactic form of a goto statement is  
goto *label*;  
where *label* is an identifier that identifies a statement.  

A labeled statement is any statement that is preceded by an identifier followed by a colon.  
Label identifiers are independent of names used for variables and other identifiers.

The goto and the labeled statement to which it transfers control
must be in the same function.

A goto statement cannot transfer control from a point where an initialized variable is out of scope
to a point where that variable is in scope.
``` C++
// ...
goto end;
int ix = 10; // error: goto bypasses an initialized variable definition
end: ix = 42; // error: code here could use ix but the goto bypassed its declaration
```
A jump backward over an already executed definition is **ok**.  
Jumping back to a point before a variable is defined **destroys** the variable and constructs it again.
``` C++
begin:
    int sz = get_size();
    if(sz <= 0){
        goto begin; // sz is destroyed and initialize anew when control passes back through its definition after the jump back to begin
    }
```



### 5.6 *try* Blocks and Exception Handling

**Exceptions** are run-time anomalies that exist outside the normal functioning of a program.

Dealing with exceptions can be one of the most difficult part of designing any system.

Exception handling is generally used
when one part of a program detects a problem that it cannot resolve
and the problem is such that the detecting part of the program cannot continue.  
The detecting program needs a way to signal that something happened and that it cannot continue,
without knowing what part of the program will deal with the exceptional condition.  
Having signaled what happened, the detecting part stops processing.

