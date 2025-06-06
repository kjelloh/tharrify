# tharrify

A Playground for meta-processing of C++ code (I have named it Tha from "Meh-Tha" as in "Meta")

Also see ['cpptha'](https://github.com/kjelloh/cpptha) for the attempt to use C++ meta-code in C++ source code and actually compile it.

# tha0

This is an experimental (index 0 iteration) of some meta-processing of C++ code.

* See what we get if we parse C++ code into just ranges and lists?

The hunch is, that we can get quite far by parsing C++ so that:

* Ranges of code are defined by begin (opening) chars "([{<" and end chars ")]}>"?
* Lists are defined by tokens separated by chars ",;:"?
* With glue-rule that a range is itself followed by an implicit list separator (ranges need not be separated by special char)?

Let's see what we get :)
