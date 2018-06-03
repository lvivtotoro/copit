#include<stdio.h>

#include"copit.h"

int main() {
    printf("10 things. %s%s11", copit_line_return(), copit_fg(copit_lightred));
    return 0;
}
