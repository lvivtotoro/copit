# Copit
Yet another terminal library but it actually ~~will have features others don't~~.  
Windows support is currently **tested**.

## Usage
Copit supports both C and C++ and will adjust it's API for the language used.  
In C++, Copit will use namespaces (`copit::fg`) instead of C-namespaces (`copit_fg`).  
So switching between API modes is self-explanatory.  
Each function in the API **will** return a `const char*` (including `copit::init`, which returns an empty string).  
This is so that it may be used in `printf` or `std::cout`.

```cpp
// Functions.
copit::init(); // Turns off input buffer on Linux, gets HANDLE on Windows.

copit::line_return(); // Returns `\r`.
copit::fg(color); // Sets the foreground color. View below section for possible values.
copit::bg(color); // Sets the background color. View below section for possible values.

copit::setcur(5, 6); // Sets the terminal cursor position to (5; 6).
copit::getcur(&x, &y); // Gets the terminal cursor position into x and y.
copit::getsize(&w, &h); // Gets the terminal size into w and h. Make sure stdin is empty on Linux before calling this function.

copit::deinit(); // Resets terminal settings on Linux.

// On non-Win systems, ANSI escape sequences shall be RETURNED.
// On Windows, relevant Win32 functions shall be CALLED and shall RETURN an empty string.
// To maintain portability, it's best to print the return values of copit functions.
// Getters also return empty strings, but the real "getted" values are returned via pointers.
// So rule: Always print the return values of copit functions!

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
```

## License

You may use Copit under the terms of the [Expat License](https://github.com/lvivtotoro/copit/blob/master/LICENSE).  
Note, that GitHub mistakenly calls this the MIT License, which is incorrect.
