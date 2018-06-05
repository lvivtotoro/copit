#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#include"../copit.h"

#define INVALID_ARG_1 1
#define INVALID_ARG_2 2
#define NO_PARAMETERS 10

unsigned char str2color(char* s) {
    if(!strcmp(s, "black")) return copit_black;
    else if(!strcmp(s, "blue")) return copit_blue;
    else if(!strcmp(s, "green")) return copit_green;
    else if(!strcmp(s, "aqua")) return copit_aqua;
    else if(!strcmp(s, "red")) return copit_red;
    else if(!strcmp(s, "purple")) return copit_purple;
    else if(!strcmp(s, "yellow")) return copit_yellow;
    else if(!strcmp(s, "white")) return copit_white;
    else if(!strcmp(s, "gray")) return copit_gray;
    else if(!strcmp(s, "lightblue")) return copit_lightblue;
    else if(!strcmp(s, "lightgreen")) return copit_lightgreen;
    else if(!strcmp(s, "lightaqua")) return copit_lightaqua;
    else if(!strcmp(s, "lightred")) return copit_lightred;
    else if(!strcmp(s, "lightpurple")) return copit_lightpurple;
    else if(!strcmp(s, "lightyellow")) return copit_lightyellow;
    else if(!strcmp(s, "lightwhite")) return copit_lightwhite;
    else return -1;
}

int errVal = 0;

int main(int argc, char** argv) {
    copit_init();

    if(argc == 1) {
        puts("No arguments specified.");
        errVal = NO_PARAMETERS;
        goto error;
    }

    if(!strcmp(argv[1], "fg")) {
        if(argc == 2) {
            puts("No argument for parameter color.");
            errVal = INVALID_ARG_1;
            goto error;
        }
        fputs(copit_fg(str2color(argv[2])), stdout);
    } else if(!strcmp(argv[1], "bg")) {
        if(argc == 2) {
            puts("No argument for parameter color.");
            errVal = INVALID_ARG_1;
            goto error;
        }
        fputs(copit_bg(str2color(argv[2])), stdout);
    } else if(!strcmp(argv[1], "n"))
        fputs(copit_line_return(), stdout);
    else if(!strcmp(argv[1], "cur")) {
        if(argc == 2) {
            unsigned short x, y;
            copit_getcur(&x, &y);
            printf("%hu\n%hu", x, y);
        } else {
            unsigned short x, y;
            char* end;
            x = strtol(argv[2], &end, 0);
            if(argv[2] == end) {
                printf("Invalid cur parameter x: %s\n", argv[2]);
                errVal = INVALID_ARG_1;
                goto error;
            }
            y = strtol(argv[3], &end, 0);
            if(argv[3] == end) {
                printf("Invalid cur parameter y: %s\n", argv[3]);
                errVal = INVALID_ARG_2;
                goto error;
            }
            fputs(copit_setcur(x, y), stdout);
        }
    } else if(!strcmp(argv[1], "size")) {
        unsigned short w, h;
        copit_getsize(&w, &h);
        printf("%hu\n%hu", w, h);
    } else {
        printf("Unknown parameter %s.\n", argv[1]);
        errVal = 1;
        goto error;
    }

    error:
        copit_deinit();
        return errVal;
}
