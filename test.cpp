#include<stdio.h>
#include<iostream>

#include"copit.h"

int main() {
    copit::init();

    unsigned short x, y;
    copit::getsize(&x, &y);
    std::cout << x << " " << y;
    fflush(stdout);

    return 0;
}
