#ifndef COPIT_H_INCLUDED
#define COPIT_H_INCLUDED

#ifdef _WIN32
    #include<windows.h>
    static HANDLE wterm;
#else
    #include<termios.h>
    #include<unistd.h>
    static struct termios lterm;
#endif

#ifdef __cplusplus
    #define COPIT_FUNC(name, ...) inline const char* name(__VA_ARGS__)
    #define COPIT_CHAR(name) unsigned char name
    #define COPIT_GETFUNC(name) name
    namespace copit {
#else
    #ifdef __GNUC__
        #define COPIT_FUNC(name, ...) __attribute__((unused)) static const char* copit_##name (__VA_ARGS__)
    #else
        #define COPIT_FUNC(name, ...) static const char* copit_##name (__VA_ARGS__)
    #endif
    #define COPIT_CHAR(name) unsigned char copit_##name
    #define COPIT_GETFUNC(name) copit_##name
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
    COPIT_CHAR(gray) = 90;
    COPIT_CHAR(lightblue) = 94;
    COPIT_CHAR(lightgreen) = 92;
    COPIT_CHAR(lightaqua) = 96;
    COPIT_CHAR(lightred) = 91;
    COPIT_CHAR(lightpurple) = 95;
    COPIT_CHAR(lightyellow) = 93;
    COPIT_CHAR(lightwhite) = 97;
#endif

COPIT_FUNC(init) {
    #ifdef _WIN32
        wterm = GetStdHandle(STD_OUTPUT_HANDLE);
    #else
        tcgetattr(STDIN_FILENO, &lterm);

        struct termios newTerm;
        tcgetattr(STDIN_FILENO, &newTerm);
        newTerm.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newTerm);
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
            SetConsoleTextAttribute(wterm, (colors & 0xF0) | c);
        }
        return "";
    #else
        static char buf[8];
        sprintf(buf, "\33[%im", (int) c);
        return buf;
    #endif
}

COPIT_FUNC(bg, unsigned char c) {
    #ifdef _WIN32
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        if(GetConsoleScreenBufferInfo(wterm, &csbi)) {
            WORD colors = csbi.wAttributes;
            SetConsoleTextAttribute(wterm, (colors & 0x0F) | (c << 4));
        }
        return "";
    #else
        c += 10;

        static char buf[16];
        sprintf(buf, "\33[%im", (int) c);
        return buf;
    #endif
}

COPIT_FUNC(setcur, unsigned short x, unsigned short y) {
    #ifdef _WIN32
        COORD coord{(short) x, (short) y};
        SetConsoleCursorPosition(wterm, coord);
        return "";
    #else
        static char buf[16];
        sprintf(buf, "\33[%i;%iH", y, x);
        return buf;
    #endif
}

/**
 * On Linux, make sure the input stream is empty before calling this function.
 */
COPIT_FUNC(getcur, unsigned short* x, unsigned short* y) {
    #ifdef _WIN32
        CONSOLE_SCREEN_BUFFER_INFO conscrbufinfo;
        GetConsoleScreenBufferInfo(wterm, &conscrbufinfo);
        COORD coord = conscrbufinfo.dwCursorPosition;
        *x = coord.X;
        *y = coord.Y;
    #else
        printf("\33[6n");
        scanf("\33[%hu;%huR", y, x);
    #endif
    return "";
}

COPIT_FUNC(getsize, unsigned short* w, unsigned short* h) {
    #ifdef _WIN32
        CONSOLE_SCREEN_BUFFER_INFO conscrbufinfo;
        GetConsoleScreenBufferInfo(wterm, &conscrbufinfo);
        *w = conscrbufinfo.srWindow.Right - conscrbufinfo.srWindow.Left + 1;
        *h = conscrbufinfo.srWindow.Bottom - conscrbufinfo.srWindow.Top + 1;
    #else
        // setcur values are clamped to the edge of the console.
        // we use this to our advantage, so we pick a non-arbitrary large number.
        unsigned short x, y;
        COPIT_GETFUNC(getcur)(&x, &y);
        printf("%s", COPIT_GETFUNC(setcur)((unsigned short) 0x464F5247, (unsigned short) 0x4956452E));
        COPIT_GETFUNC(getcur)(w, h);
        printf("%s", COPIT_GETFUNC(setcur)(x, y));
    #endif
    return "";
}

COPIT_FUNC(deinit) {
    #ifdef _WIN32
    #else
        tcsetattr(STDIN_FILENO, TCSANOW, &lterm);
    #endif
    return "";
}

#ifdef __cplusplus
    }
#endif

#undef COPIT_FUNC
#undef COPIT_CHAR
#undef COPIT_GETFUNC

#endif // COPIT_H_INCLUDED
