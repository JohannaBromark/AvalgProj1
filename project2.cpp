//
// Created by Isabelle Hallman on 2017-11-22.
//

#include <iostream>

unsigned long long gcd(unsigned long long x, unsigned long long y) {
    //Finds greatest common divisor
    if (x < y) {
        return gcd(y, x);
    }
    return (y == 0 ? x : gcd(y, x % y));
}

unsigned long long gFunction(unsigned long long x, unsigned long long number) {
    return (x*x + 1) % number;
}

unsigned long long pollardsRho(unsigned long long number, int ) {
    unsigned long long factor = 1, x = 2, y = 2;
    while (factor == 1) {
        x = gFunction(x, number);
        y = gFunction(gFunction(y, number), number);
        factor = gcd((unsigned long long) std::abs( (long long) (x - y) ), number);
    }
    if (factor == number) {
        return 0;
    }
    else {
        return factor;
    }
}

bool millerRabin(unsigned long long number, int k) {

}

int main() {

}