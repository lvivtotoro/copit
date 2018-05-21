#include<stdio.h>

#include"copit.h"

int main() {
    copit::init();
    printf("10 things. %s%s11", copit::line_return(), copit::bg(copit::aqua));
    return 0;
}
