# Copit
Yet another terminal library but it actually ~~will have features others don't~~.  
Windows support is **untested**.

## Usage
Copit supports both C and C++ and will adjust it's API for the language used.  
In C++, Copit will use namespaces (`copit::fg`) instead of C-namespaces (`copit_fg`).  
So switching between API modes is self-explanatory.  
Each function in the API **will** return a `const char*` (including `copit::init`, which returns an empty string).  
This is so that it may be used in `printf` or `std::cout`.

	// Functions.
	
    copit::init(); // For Windows.
	
	copit::line_return(); // Returns `\r`.
	copit::fg(color); // Sets the foreground color. View below section for possible values.
	copit::bg(color); // Sets the background color. View below section for possible values.

	// Possible colors. Do not use their internal values, as they are different for each system.

    copit::black
    copit::blue
    copit::green
    copit::aqua
    copit::red
    copit::purple
    copit::yellow
    copit::white
    copit::gray
    copit::lightblue
    copit::lightgreen
    copit::lightaqua
    copit::lightred
    copit::lightpurple
    copit::lightyellow
    copit::lightwhite

## License

You may use Copit under the terms of the [Expat License](https://github.com/lvivtotoro/copit/blob/master/LICENSE).
