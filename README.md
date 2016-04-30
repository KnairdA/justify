# justify

...is a single purpose program for block justification of UTF-8 encoded monospace text.

Textual input is read from _STDIN_ and written to _STDOUT_ in its justified form. The default output width of 60 characters may be customized via `--length`. Optionally an offset of leading spaces may be defined using `--offset`.

i.e. `echo "$the_paragraph_above" | justify --length 40 --offset 2` results in:

	  Textual input  is  read from _STDIN_ and
	  written  to  _STDOUT_  in  its justified
	  form.  The  default output  width  of 60
	  characters    may   be    customized via
	  `--length`.  Optionally   an   offset of
	  leading   spaces  may  be  defined using
	  `--offset`.

The seed used to pseudorandomly distribute missing spaces may be customized via the `--seed` argument.

## Requirements

* CMake
* C++ compiler with C++14 support
* Boost [Program Options](http://www.boost.org/doc/libs/1_60_0/doc/html/program_options.html)

## Build

	mkdir build
	cd build
	cmake ..
	make
