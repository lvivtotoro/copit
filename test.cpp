#include<stdio.h>

#include"copit.h"

int main() {
    printf("10 things. %s%s11", copit::line_return(), copit::fg(copit::red));
    return 0;
}
