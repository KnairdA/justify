# justify

...is a single purpose program for block justification of UTF-8 encoded monospace text.

Textual input is read from _STDIN_ and written to _STDOUT_ in its justified form. The default output width of 60 characters may be customized via the first application argument.

## Build

	mkdir build
	cd build
	cmake ..
	make

A current C++ compiler with support for C++14 is required.
