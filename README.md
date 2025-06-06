# tharrify

** 6:th of June 2025 - Renamed from previous name 'tha' (local clones beware)**

An initiative to try to split 'C-language-based' source code into arrays or lists based on scopes and separators.

The goal is to se how much information we can get out of splitting source code with this simple, more or less syntax agnostic, approach?

The name of a word play on name 'Tha' of the four meta tier type system model and 'arrify' from 'to make into an array'.

Also see ['cpptha'](https://github.com/kjelloh/cpptha) for the attempt to use C++ meta-code in C++ source code and actually compile it.

**Note: This initiative may or may nbot be used as part of final Tha modelling of source code.**

# tha0

This is an experimental (index 0 iteration) of some meta-processing of C++ code.

* See what we get if we parse C++ code into just ranges and lists?

The hunch is, that we can get quite far by parsing C++ so that:

* Ranges of code are defined by begin (opening) chars "([{<" and end chars ")]}>"?
* Lists are defined by tokens separated by chars ",;:"?
* With glue-rule that a range is itself followed by an implicit list separator (ranges need not be separated by special char)?

Let's see what we get :)
