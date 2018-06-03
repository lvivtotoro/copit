#ifndef COPIT_H_INCLUDED
#define COPIT_H_INCLUDED

#ifdef _WIN32
    #include<windows.h>
    static HANDLE wterm;
#endif

#ifdef __cplusplus
    #define COPIT_FUNC(name, ...) inline const char* name(__VA_ARGS__)
    #define COPIT_CHAR(name) unsigned char name
    namespace copit {
#else
    #define COPIT_FUNC(name, ...) static const char* copit_##name (__VA_ARGS__)
    #define COPIT_CHAR(name) unsigned char copit_##name
#endif

#ifdef _WIN32
    COPIT_CHAR(black) = 0;
    COPIT_CHAR(blue) = 1;
    COPIT_CHAR(green) = 2;
    COPIT_CHAR(aqua) = 3;
    COPIT_CHAR(red) = 4;
    COPIT_CHAR(purple) = 5;
    COPIT_CHAR(yellow) = 6;
    COPIT_CHAR(white) = 7;
    COPIT_CHAR(gray) = 8;
    COPIT_CHAR(lightblue) = 9;
    COPIT_CHAR(lightgreen) = 10;
    COPIT_CHAR(lightaqua) = 11;
    COPIT_CHAR(lightred) = 12;
    COPIT_CHAR(lightpurple) = 13;
    COPIT_CHAR(lightyellow) = 14;
    COPIT_CHAR(lightwhite) = 15;
#else
    COPIT_CHAR(black) = 30;
    COPIT_CHAR(blue) = 34;
    COPIT_CHAR(green) = 32;
    COPIT_CHAR(aqua) = 36;
    COPIT_CHAR(red) = 31;
    COPIT_CHAR(purple) = 35;
    COPIT_CHAR(yellow) = 33;
    COPIT_CHAR(white) = 37;
    COPIT_CHAR(gray) = 37 | 0b10000000;
    COPIT_CHAR(lightblue) = 34 | 0b10000000;
    COPIT_CHAR(lightgreen) = 32 | 0b10000000;
    COPIT_CHAR(lightaqua) = 36 | 0b10000000;
    COPIT_CHAR(lightred) = 31 | 0b10000000;
    COPIT_CHAR(lightpurple) = 35 | 0b10000000;
    COPIT_CHAR(lightyellow) = 33 | 0b10000000;
    COPIT_CHAR(lightwhite) = 37 | 0b10000000;
#endif

COPIT_FUNC(init) {
    #ifdef _WIN32
        wterm = GetStdHandle(STD_OUTPUT_HANDLE);
    #endif
    return "";
}

COPIT_FUNC(line_return) {
    return "\r";
}

COPIT_FUNC(fg, unsigned char c) {
    #ifdef _WIN32
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        if(GetConsoleScreenBufferInfo(wterm, &csbi)) {
            WORD colors = csbi.wAttributes;
            SetConsoleTextAttribute(wterm, (colors & 0bF0) | c);
        }
        return "";
    #else
        static char buf[8];
        int bright = c & 0b10000000;
        sprintf(buf, "\33[%i;%sm", (int) (c & ~0b10000000), bright ? "1" : "22");
        return buf;
    #endif
}

COPIT_FUNC(bg, unsigned char c) {
    #ifdef _WIN32
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        if(GetConsoleScreenBufferInfo(wterm, &csbi)) {
            WORD colors = csbi.wAttributes;
            SetConsoleTextAttribute(wterm, (colors & 0b0F) | (c << 4));
        }
        return "";
    #else
        c += 10;

        static char buf[8];
        int bright = c & 0b10000000;
        if(bright) c += 60;
        sprintf(buf, "\33[%im", (int) (c & ~0b10000000));
        return buf;
    #endif
}

#ifdef __cplusplus
    }
#endif

#undef COPIT_FUNC
#undef COPIT_CHAR

#endif // COPIT_H_INCLUDED
