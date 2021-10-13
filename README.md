# tracer
A simple C++ tracer class for tracking function passed arguments and return value

It is sometimes required in competitive programming contests, specially in long-time challenges when there is enough time to trace the program execution behavior at run-time before submitting it to the automatic judge, to track the passed arguments and return value of some C++ function(s). This repository presents a simple C++ tracer class for this purpose.

The tracer can be used either by copying and pasting the tracer.hpp file into the C++ program or by adding the following include statement to the program

#include "tracer.hpp"

If the macro TRACE is defined before this tracer code, the following trace operations are enabled using Variadic Macros and Variadic Function Templates.

1. tr_begin(...) macro call increments the trace depth, and then prints the passed arguments.
2. tr(...) macro call prints the passed arguments without updating the trace depth.
2. tr_end(...) macro call prints the passed arguments, decrements the trace depth, and returns the first argument. This call can be used as the return value of the traced function.

Each traced function should have a tr_begin(...) macro call at the beginning of the function block, a tr_end(...) macro call at the end of the function block, and zero or more tr(...) macro call(s) inside the function block.

If the TRACE macro is undefined before the tracer code, the aforementioned trace operations are disabled.

The file main.cpp contains an example program to test the functionality of the tracer by tracking the execution of the recursive algorithm for computing the factorial function n!
